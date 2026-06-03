# 手撕代码模拟面试 C++ 版

使用方式：每轮随机抽 2 道。第一道 20 分钟，第二道 25 分钟。写完必须口述思路、边界情况、时间复杂度和空间复杂度。

## 通用结构

链表和二叉树题默认使用 LeetCode 的结构：

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
```

## Round 1：哈希 + 滑动窗口

### 题目 A：1 Two Sum

要求：返回两个数下标，不能重复使用同一个元素。

核心代码：

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < (int)nums.size(); ++i) {
        int need = target - nums[i];
        if (seen.count(need)) return {seen[need], i};
        seen[nums[i]] = i;
    }
    return {};
}
```

复杂度：时间 O(n)，空间 O(n)。

追问：

- 为什么哈希表是一遍扫描？
- 如果数组有重复值怎么办？
- 如果要求返回所有组合怎么办？

### 题目 B：3 Longest Substring Without Repeating Characters

要求：返回无重复字符最长子串长度。

核心代码：

```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> last(256, -1);
    int left = 0, ans = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char ch = s[right];
        if (last[ch] >= left) left = last[ch] + 1;
        last[ch] = right;
        ans = max(ans, right - left + 1);
    }
    return ans;
}
```

复杂度：时间 O(n)，空间 O(1)，如果字符集不固定则空间 O(k)。

追问：

- `left` 为什么只能右移，不能回退？
- 哈希表存字符出现次数和最后位置，两种写法有什么区别？
- 如果字符集很大怎么办？

## Round 2：双指针 + 前缀和

### 题目 A：15 3Sum

要求：返回所有不重复三元组，和为 0。

核心代码：

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        if (nums[i] > 0) break;

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                ans.push_back({nums[i], nums[left], nums[right]});
                ++left;
                --right;
                while (left < right && nums[left] == nums[left - 1]) ++left;
                while (left < right && nums[right] == nums[right + 1]) --right;
            } else if (sum < 0) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return ans;
}
```

复杂度：时间 O(n^2)，空间 O(log n) 或 O(1)，取决于排序实现。

追问：

- 为什么必须排序？
- 如何去重？
- 时间复杂度为什么是 O(n^2)？

### 题目 B：560 Subarray Sum Equals K

要求：统计和为 k 的连续子数组数量。

核心代码：

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    cnt[0] = 1;
    int prefix = 0, ans = 0;

    for (int x : nums) {
        prefix += x;
        if (cnt.count(prefix - k)) ans += cnt[prefix - k];
        ++cnt[prefix];
    }
    return ans;
}
```

复杂度：时间 O(n)，空间 O(n)。

追问：

- 为什么滑动窗口不适合含负数数组？
- `cnt[prefix - k]` 代表什么？
- 初始值 `cnt[0] = 1` 有什么意义？

## Round 3：栈 + 堆

### 题目 A：739 Daily Temperatures

要求：每一天要等几天才有更高温度。

核心代码：

```cpp
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> ans(temperatures.size(), 0);
    stack<int> st;

    for (int i = 0; i < (int)temperatures.size(); ++i) {
        while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
            int j = st.top();
            st.pop();
            ans[j] = i - j;
        }
        st.push(i);
    }
    return ans;
}
```

复杂度：时间 O(n)，空间 O(n)。

追问：

- 栈里存下标还是温度？
- 单调栈维护递增还是递减？
- 每个元素为什么最多入栈出栈一次？

### 题目 B：215 Kth Largest Element in an Array

要求：找第 k 大元素。

核心代码：小根堆维护当前最大的 k 个数。

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int x : nums) {
        heap.push(x);
        if ((int)heap.size() > k) heap.pop();
    }
    return heap.top();
}
```

复杂度：时间 O(n log k)，空间 O(k)。

追问：

- 堆解法和快排选择解法复杂度分别是什么？
- C++ 小根堆如何维护第 k 大？
- 如果数据流持续到来怎么办？

## Round 4：链表

### 题目 A：206 Reverse Linked List

要求：反转单链表。

核心代码：

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;

    while (cur) {
        ListNode* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
```

复杂度：时间 O(n)，空间 O(1)。

追问：

- 三个指针分别表示什么？
- 递归写法如何实现？
- 如何避免断链？

### 题目 B：19 Remove Nth Node From End of List

要求：删除倒数第 n 个节点。

核心代码：

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    for (int i = 0; i < n; ++i) fast = fast->next;

    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    slow->next = slow->next->next;
    return dummy.next;
}
```

复杂度：时间 O(n)，空间 O(1)。

追问：

- 为什么需要 dummy？
- 快指针先走几步？
- 删除头节点时会发生什么？

## Round 5：树

### 题目 A：102 Binary Tree Level Order Traversal

要求：层序遍历二叉树。

核心代码：

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};

    vector<vector<int>> ans;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        while (size--) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        ans.push_back(level);
    }
    return ans;
}
```

复杂度：时间 O(n)，空间 O(n)。

追问：

- 如何区分每一层？
- DFS 能不能做层序结果？
- 空树怎么处理？

### 题目 B：98 Validate Binary Search Tree

要求：判断是否为合法 BST。

核心代码：上下界递归，比“只比较左右孩子”更稳。

```cpp
bool isValidBST(TreeNode* root) {
    function<bool(TreeNode*, long long, long long)> dfs =
        [&](TreeNode* node, long long low, long long high) -> bool {
            if (!node) return true;
            if (!(low < node->val && node->val < high)) return false;
            return dfs(node->left, low, node->val) &&
                   dfs(node->right, node->val, high);
        };

    return dfs(root, LLONG_MIN, LLONG_MAX);
}
```

复杂度：时间 O(n)，空间 O(h)，h 为树高。

追问：

- 只比较左右孩子为什么不够？
- 中序遍历法和上下界法有什么区别？
- 重复值是否允许？

## Round 6：图

### 题目 A：200 Number of Islands

要求：统计网格中岛屿数量。

核心代码：DFS 原地沉岛。

```cpp
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int rows = grid.size(), cols = grid[0].size();
    int ans = 0;

    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') {
            return;
        }
        grid[r][c] = '0';
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '1') {
                ++ans;
                dfs(r, c);
            }
        }
    }
    return ans;
}
```

复杂度：时间 O(mn)，空间 O(mn)，最坏情况下递归栈会到 O(mn)。

追问：

- DFS 和 BFS 都怎么写？
- visited 数组和原地改 grid 哪个更好？
- 递归深度很大怎么办？

### 题目 B：207 Course Schedule

要求：判断课程依赖是否能完成。

核心代码：BFS 拓扑排序。

```cpp
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& e : prerequisites) {
        int course = e[0], pre = e[1];
        graph[pre].push_back(course);
        ++indegree[course];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    int seen = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++seen;

        for (int nxt : graph[cur]) {
            if (--indegree[nxt] == 0) q.push(nxt);
        }
    }

    return seen == numCourses;
}
```

复杂度：时间 O(V + E)，空间 O(V + E)。

追问：

- 入度为 0 的节点代表什么？
- 为什么 BFS 处理数量等于课程数就无环？
- DFS 三色标记如何做？

## Round 7：动态规划

### 题目 A：322 Coin Change

要求：最少硬币数凑成 amount。

核心代码：

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int x = 1; x <= amount; ++x) {
        for (int coin : coins) {
            if (coin <= x) {
                dp[x] = min(dp[x], dp[x - coin] + 1);
            }
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}
```

复杂度：时间 O(amount * n)，空间 O(amount)。

追问：

- `dp[x]` 表示什么？
- 初始化为什么用 `amount + 1`？
- 为什么这是完全背包？

### 题目 B：300 Longest Increasing Subsequence

要求：最长严格递增子序列长度。

核心代码：O(n log n) 贪心 + 二分。

```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;

    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }

    return tails.size();
}
```

复杂度：时间 O(n log n)，空间 O(n)。

追问：

- O(n^2) DP 怎么写？
- O(n log n) 的 `tails` 数组含义是什么？
- 为什么 `lower_bound` 对应严格递增？

## Round 8：综合

### 题目 A：146 LRU Cache

要求：O(1) 实现 get/put。

核心代码：`list` 维护最近使用顺序，`unordered_map` 存 key 到链表节点迭代器。

```cpp
class LRUCache {
private:
    int cap;
    list<pair<int, int>> items; // front 是最近使用
    unordered_map<int, list<pair<int, int>>::iterator> pos;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (!pos.count(key)) return -1;
        items.splice(items.begin(), items, pos[key]);
        return pos[key]->second;
    }

    void put(int key, int value) {
        if (pos.count(key)) {
            pos[key]->second = value;
            items.splice(items.begin(), items, pos[key]);
            return;
        }

        items.push_front({key, value});
        pos[key] = items.begin();

        if ((int)items.size() > cap) {
            int oldKey = items.back().first;
            pos.erase(oldKey);
            items.pop_back();
        }
    }
};
```

复杂度：`get` O(1)，`put` O(1)，空间 O(capacity)。

追问：

- 为什么只用 map 不够？
- 双向链表维护什么顺序？
- put 已存在 key 时怎么处理？

### 题目 B：76 Minimum Window Substring

要求：找到覆盖目标串的最短子串。

核心代码：

```cpp
string minWindow(string s, string t) {
    vector<int> need(128, 0);
    for (char ch : t) ++need[ch];

    int missing = t.size();
    int left = 0, bestStart = 0, bestLen = INT_MAX;

    for (int right = 0; right < (int)s.size(); ++right) {
        if (need[s[right]] > 0) --missing;
        --need[s[right]];

        while (missing == 0) {
            if (right - left + 1 < bestLen) {
                bestStart = left;
                bestLen = right - left + 1;
            }

            ++need[s[left]];
            if (need[s[left]] > 0) ++missing;
            ++left;
        }
    }

    return bestLen == INT_MAX ? "" : s.substr(bestStart, bestLen);
}
```

复杂度：时间 O(|s| + |t|)，空间 O(1)，如果字符集不固定则空间 O(k)。

追问：

- `formed` 或 `missing` 如何定义？
- 窗口什么时候收缩？
- 如果不存在答案返回什么？

