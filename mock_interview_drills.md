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

题目描述：

给定一个整数数组 `nums` 和一个整数 `target`，请你在数组中找出两个不同位置的元素，使它们的和等于 `target`，并返回这两个元素的下标。

约定：同一个元素不能使用两次；通常题目保证恰好存在一个答案；返回下标顺序不重要。

示例：`nums = [2, 7, 11, 15], target = 9`，因为 `nums[0] + nums[1] = 9`，所以返回 `[0, 1]`。

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

追问与参考回答：

- 为什么哈希表是一遍扫描？
  因为遍历到 `nums[i]` 时，只需要判断前面是否出现过 `target - nums[i]`。哈希表能 O(1) 平均时间查找，所以不需要内层循环。
- 如果数组有重复值怎么办？
  没问题。哈希表存的是值到下标的映射。比如 `[3, 3] target = 6`，第一个 `3` 存进去，遍历到第二个 `3` 时能找到前一个下标。
- 如果要求返回所有组合怎么办？
  不能直接只存一个下标。可以先排序后双指针找所有不重复数值组合，或者哈希表存每个值出现的所有下标，再枚举组合并去重。

### 题目 B：3 Longest Substring Without Repeating Characters

题目描述：

给定一个字符串 `s`，请你找出其中不含重复字符的最长连续子串，并返回这个子串的长度。

注意：子串必须是连续的，子序列不要求连续；大小写、空格、符号都可以视为字符。

示例：`s = "abcabcbb"`，最长无重复子串可以是 `"abc"`，长度为 `3`。

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

复杂度：时间 O(n)，空间 O(1)。如果字符集不固定，则空间 O(k)。

追问与参考回答：

- `left` 为什么只能右移，不能回退？
  `left` 表示当前无重复窗口的左边界。右移是为了排除重复字符；一旦左边界右移，左边的字符已经不属于当前窗口，回退会重新引入旧冲突。
- 哈希表存字符出现次数和最后位置，两种写法有什么区别？
  存次数是通用滑窗写法，靠 `while` 收缩窗口。存最后位置更适合本题，遇到重复字符时可以一步跳到 `last[ch] + 1`。
- 如果字符集很大怎么办？
  不能用固定 `vector<int>(256)` 时，可以用 `unordered_map<char, int>` 或按编码类型换成 `unordered_map<int, int>`。

## Round 2：双指针 + 前缀和

### 题目 A：15 3Sum

题目描述：

给定一个整数数组 `nums`，请找出所有满足 `a + b + c = 0` 的三元组，并且三元组中的三个元素必须来自不同下标。

要求：结果中不能包含重复三元组。三元组内部顺序和最终答案顺序通常不重要。

示例：`nums = [-1, 0, 1, 2, -1, -4]`，返回 `[[-1, -1, 2], [-1, 0, 1]]`。

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

追问与参考回答：

- 为什么必须排序？
  排序后才能用双指针根据和的大小移动左右指针，也更容易跳过重复元素，保证结果不重复。
- 如何去重？
  固定第一个数时，如果 `nums[i] == nums[i - 1]` 就跳过。找到一个三元组后，左右指针也要跳过相同值。
- 时间复杂度为什么是 O(n^2)？
  外层枚举第一个数是 O(n)，内层双指针整体线性移动是 O(n)，所以总时间是 O(n^2)。

### 题目 B：560 Subarray Sum Equals K

题目描述：

给定一个整数数组 `nums` 和一个整数 `k`，请统计数组中和等于 `k` 的连续子数组个数。

注意：子数组必须连续；数组中可能包含负数、0 和正数，因此不能简单依赖滑动窗口的单调性。

示例：`nums = [1, 1, 1], k = 2`，满足条件的子数组有两个，所以返回 `2`。

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

追问与参考回答：

- 为什么滑动窗口不适合含负数数组？
  滑动窗口依赖“右扩和变大、左缩和变小”这种单调性。数组有负数时，扩张窗口可能让和变小，收缩窗口也可能让和变大。
- `cnt[prefix - k]` 代表什么？
  当前前缀和是 `prefix`。如果之前存在前缀和 `prefix - k`，那么从那个位置后面到当前位置的子数组和就是 k。
- 初始值 `cnt[0] = 1` 有什么意义？
  它表示空前缀。这样当从数组开头到当前位置的和正好等于 k 时，也能被统计到。

## Round 3：栈 + 堆

### 题目 A：739 Daily Temperatures

题目描述：

给定一个整数数组 `temperatures`，其中 `temperatures[i]` 表示第 `i` 天的温度。请返回一个数组 `ans`，其中 `ans[i]` 表示从第 `i` 天开始，需要等待多少天才会出现更高的温度。

如果某一天之后不会再出现更高温度，则对应位置返回 `0`。

示例：`temperatures = [73,74,75,71,69,72,76,73]`，返回 `[1,1,4,2,1,1,0,0]`。

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

追问与参考回答：

- 栈里存下标还是温度？
  存下标。因为答案需要天数差 `i - j`，同时也能通过下标访问温度。
- 单调栈维护递增还是递减？
  从栈底到栈顶是单调不增。栈里存的是还没找到更高温度的天，下一个更高温度出现时就弹出结算。
- 每个元素为什么最多入栈出栈一次？
  每个下标遍历到时只入栈一次，一旦遇到更高温度被弹出，就不会再入栈，所以总操作次数是 O(n)。

### 题目 B：215 Kth Largest Element in an Array

题目描述：

给定一个整数数组 `nums` 和整数 `k`，请返回数组中第 `k` 大的元素。

注意：这里是排序后的第 `k` 大元素，不是第 `k` 个不同元素；数组可能有重复值。

示例：`nums = [3,2,1,5,6,4], k = 2`，排序后第二大是 `5`，返回 `5`。

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

追问与参考回答：

- 堆解法和快排选择解法复杂度分别是什么？
  堆解法是 O(n log k)，空间 O(k)。快速选择平均 O(n)，最坏 O(n^2)，可以通过随机 pivot 降低最坏情况概率。
- C++ 小根堆如何维护第 k 大？
  用 `priority_queue<int, vector<int>, greater<int>>`。堆里只保留 k 个最大元素，堆顶就是这 k 个里面最小的，也就是全局第 k 大。
- 如果数据流持续到来怎么办？
  继续维护大小为 k 的小根堆。新数比堆顶大就替换堆顶，否则丢弃。任意时刻堆顶都是当前第 k 大。

## Round 4：链表

### 题目 A：206 Reverse Linked List

题目描述：

给定单链表的头节点 `head`，请将整个链表反转，并返回反转后的新头节点。

链表节点只能通过 `next` 指针访问。面试中通常要求原地反转，也就是只修改指针方向，不额外创建一条新链表。

示例：`1 -> 2 -> 3 -> 4 -> 5`，反转后为 `5 -> 4 -> 3 -> 2 -> 1`。

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

追问与参考回答：

- 三个指针分别表示什么？
  `prev` 是已经反转好的前一段头部，`cur` 是当前要处理的节点，`nxt` 临时保存原链表的下一个节点，避免改指针后断链。
- 递归写法如何实现？
  递归到链表尾部，把尾节点作为新头返回。回溯时让 `head->next->next = head`，再把 `head->next = nullptr`。

  ```cpp
  ListNode* reverseList(ListNode* head) {
      if (!head || !head->next) return head;
      ListNode* newHead = reverseList(head->next);
      head->next->next = head;
      head->next = nullptr;
      return newHead;
  }
  ```
- 如何避免断链？
  每轮必须先保存 `ListNode* nxt = cur->next`，再修改 `cur->next`。否则改完指向后就找不到原来的后续节点了。

### 题目 B：19 Remove Nth Node From End of List

题目描述：

给定单链表的头节点 `head` 和整数 `n`，请删除链表的倒数第 `n` 个节点，并返回删除后的头节点。

要求：尽量使用一趟扫描完成。需要正确处理删除头节点、链表只有一个节点等边界情况。

示例：`head = 1 -> 2 -> 3 -> 4 -> 5, n = 2`，删除节点 `4`，返回 `1 -> 2 -> 3 -> 5`。

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

追问与参考回答：

- 为什么需要 dummy？
  dummy 统一处理删除头节点的情况。比如链表长度等于 n 时，要删除原头节点，返回 `dummy.next` 就很自然。
- 快指针先走几步？
  这里从 dummy 出发，快指针先走 n 步。之后快慢一起走到 `fast->next == nullptr`，slow 正好停在待删除节点的前一个节点。
- 删除头节点时会发生什么？
  slow 仍然在 dummy，执行 `slow->next = slow->next->next`，也就是让 dummy 跳过原 head，最后返回新的 `dummy.next`。

## Round 5：树

### 题目 A：102 Binary Tree Level Order Traversal

题目描述：

给定一棵二叉树的根节点 `root`，请按照从上到下、从左到右的顺序，逐层返回节点值。

返回结果是二维数组，每个内部数组表示树的一层。

示例：二叉树 `[3,9,20,null,null,15,7]`，返回 `[[3], [9,20], [15,7]]`。

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

追问与参考回答：

- 如何区分每一层？
  每轮开始时记录当前队列长度 `size`。这个长度就是当前层节点数，只处理这 `size` 个节点，新增孩子留给下一层。
- DFS 能不能做层序结果？
  可以。DFS 时带一个 `depth` 参数，如果 `ans.size() == depth` 就新建一层，然后把当前节点放进 `ans[depth]`。
- 空树怎么处理？
  如果 `root == nullptr`，直接返回空数组 `{}`。

### 题目 B：98 Validate Binary Search Tree

题目描述：

给定一棵二叉树的根节点 `root`，请判断它是否是一棵合法的二叉搜索树。

二叉搜索树要求：任意节点的左子树所有节点值都严格小于当前节点值，右子树所有节点值都严格大于当前节点值，并且左右子树也必须是二叉搜索树。

注意：不能只比较当前节点和左右孩子；重复值在 LeetCode 98 中不被视为合法。

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

追问与参考回答：

- 只比较左右孩子为什么不够？
  BST 要求左子树所有节点都小于根，右子树所有节点都大于根。只比较直接孩子会漏掉更深层的非法节点。
- 中序遍历法和上下界法有什么区别？
  中序法利用 BST 中序严格递增；上下界法在递归中传递每个节点允许的取值范围。上下界法更直接表达 BST 的全局约束。
- 重复值是否允许？
  LeetCode 98 默认不允许重复值，所以判断条件是 `low < node->val < high`，不是 `<=`。

## Round 6：图

### 题目 A：200 Number of Islands

题目描述：

给定一个由字符 `'1'` 和 `'0'` 组成的二维网格 `grid`，其中 `'1'` 表示陆地，`'0'` 表示水。请统计网格中岛屿的数量。

岛屿由水平或垂直相邻的陆地连接而成，斜向相邻不算连接。你可以假设网格四周都被水包围。

示例：如果一整片连续的 `'1'` 被水隔开，则它们属于同一个岛屿。

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

追问与参考回答：

- DFS 和 BFS 都怎么写？
  DFS 可以递归向四个方向扩展。BFS 则把起点放入队列，每次弹出一个格子，再把上下左右的陆地加入队列。
- visited 数组和原地改 grid 哪个更好？
  原地改 grid 省空间，适合允许修改输入的场景。visited 不破坏输入，更适合后续还要使用原 grid 的场景。
- 递归深度很大怎么办？
  递归 DFS 可能栈溢出，可以改成显式栈的迭代 DFS，或者用 BFS 队列。

### 题目 B：207 Course Schedule

题目描述：

给定课程总数 `numCourses`，课程编号为 `0` 到 `numCourses - 1`，以及先修关系数组 `prerequisites`。其中 `prerequisites[i] = [a, b]` 表示学习课程 `a` 之前必须先完成课程 `b`。

请判断是否可以完成所有课程。

本质：判断有向图中是否存在环。如果存在循环依赖，就无法完成所有课程。

示例：`numCourses = 2, prerequisites = [[1,0]]`，先学 0 再学 1，可以完成，返回 `true`。

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

追问与参考回答：

- 入度为 0 的节点代表什么？
  表示这门课当前没有未完成的前置课程，可以先学。
- 为什么 BFS 处理数量等于课程数就无环？
  如果图里有环，环上的节点入度无法被全部消掉，最终无法全部入队。处理数量等于课程数说明所有节点都能按拓扑顺序移除，因此无环。
- DFS 三色标记如何做？
  `0` 表示未访问，`1` 表示正在当前递归路径中，`2` 表示已完成。DFS 遇到状态 `1` 的节点说明有环。

## Round 7：动态规划

### 题目 A：322 Coin Change

题目描述：

给定不同面额的硬币数组 `coins` 和一个总金额 `amount`，请计算凑成该金额所需的最少硬币个数。

每种硬币可以使用无限次。如果无法凑出该金额，返回 `-1`。

示例：`coins = [1,2,5], amount = 11`，可以用 `5 + 5 + 1`，最少 `3` 枚硬币，所以返回 `3`。

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

追问与参考回答：

- `dp[x]` 表示什么？
  表示凑成金额 x 所需要的最少硬币数。
- 初始化为什么用 `amount + 1`？
  最多只需要 amount 个 1 元硬币，所以 `amount + 1` 可以作为不可能达到的无穷大，同时避免 `INT_MAX + 1` 溢出。
- 为什么这是完全背包？
  每种硬币可以使用无限次。转移 `dp[x] = min(dp[x], dp[x - coin] + 1)` 中，同一个 coin 可以反复参与构造更大的金额。

### 题目 B：300 Longest Increasing Subsequence

题目描述：

给定一个整数数组 `nums`，请返回其中最长严格递增子序列的长度。

子序列不要求连续，但必须保持原数组中的相对顺序；严格递增表示后一个元素必须大于前一个元素，不能相等。

示例：`nums = [10,9,2,5,3,7,101,18]`，最长递增子序列长度为 `4`，例如 `[2,3,7,101]`。

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

追问与参考回答：

- O(n^2) DP 怎么写？
  定义 `dp[i]` 表示以 `nums[i]` 结尾的最长递增子序列长度。枚举 `j < i`，如果 `nums[j] < nums[i]`，就用 `dp[j] + 1` 更新 `dp[i]`。

  ```cpp
  int lengthOfLIS(vector<int>& nums) {
      int n = nums.size(), ans = 1;
      vector<int> dp(n, 1);
      for (int i = 0; i < n; ++i) {
          for (int j = 0; j < i; ++j) {
              if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
          }
          ans = max(ans, dp[i]);
      }
      return ans;
  }
  ```
- O(n log n) 的 `tails` 数组含义是什么？
  `tails[len - 1]` 表示长度为 len 的递增子序列的最小可能结尾。结尾越小，后面越容易接上更多数字。
- 为什么 `lower_bound` 对应严格递增？
  严格递增不允许相等元素扩展长度。遇到相等值时，`lower_bound` 会找到第一个大于等于 x 的位置并替换，不会让长度增加。

## Round 8：综合

### 题目 A：146 LRU Cache

题目描述：

请设计并实现一个 LRU Cache。缓存有固定容量 `capacity`，支持两个操作：

- `get(key)`：如果 key 存在，返回对应 value，并将该 key 标记为最近使用；如果不存在，返回 `-1`。
- `put(key, value)`：插入或更新 key-value，并将该 key 标记为最近使用。如果插入后超过容量，需要删除最久未使用的 key。

要求：`get` 和 `put` 的平均时间复杂度都为 O(1)。

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

追问与参考回答：

- 为什么只用 map 不够？
  map 能 O(1) 找到 key，但不能 O(1) 维护“最近使用顺序”。LRU 需要快速移动节点到最新位置，并快速删除最久未使用节点，所以要哈希表 + 双向链表。
- 双向链表维护什么顺序？
  这里 `front` 是最近使用，`back` 是最久未使用。每次 get 或更新 key，都把对应节点移动到 front。
- put 已存在 key 时怎么处理？
  先更新 value，然后把这个节点移动到最近使用位置。容量不变，不需要删除旧节点。

### 题目 B：76 Minimum Window Substring

题目描述：

给定两个字符串 `s` 和 `t`，请在 `s` 中找到一个最短的连续子串，使得这个子串包含 `t` 中所有字符以及对应的出现次数。

如果不存在这样的子串，返回空字符串 `""`。如果存在，题目通常保证答案唯一。

示例：`s = "ADOBECODEBANC", t = "ABC"`，最短覆盖子串是 `"BANC"`。

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

复杂度：时间 O(|s| + |t|)，空间 O(1)。如果字符集不固定，则空间 O(k)。

追问与参考回答：

- `formed` 或 `missing` 如何定义？
  `missing` 表示当前窗口还缺多少个目标字符。加入一个需要的字符时 `missing--`，移出一个必要字符时 `missing++`。
- 窗口什么时候收缩？
  当 `missing == 0` 时，说明当前窗口已经覆盖 t，可以不断移动 left 缩短窗口，同时更新最短答案。
- 如果不存在答案返回什么？
  返回空字符串。代码里用 `bestLen == INT_MAX` 判断是否从未找到合法窗口。
