# C++ 手撕代码速查

面试时建议默认说：我用 C++17，核心数据结构选 STL，复杂度按均摊或最坏情况说明。

## 常用头文件

```cpp
#include <bits/stdc++.h>
using namespace std;
```

正式工程不建议这么写，但 LeetCode / 手撕可以快速起手。

## vector

```cpp
vector<int> nums;
nums.push_back(x);
nums.pop_back();
nums.size();
sort(nums.begin(), nums.end());
reverse(nums.begin(), nums.end());
```

注意：

- `nums.size()` 是 `size_t`，和 `int` 比较时可写 `(int)nums.size()`。
- 二维数组：`vector<vector<int>> grid(m, vector<int>(n, 0));`

## unordered_map / unordered_set

```cpp
unordered_map<int, int> mp;
mp[x]++;
if (mp.count(x)) {}

unordered_set<int> st(nums.begin(), nums.end());
if (st.count(x)) {}
```

常见题：

- Two Sum
- Subarray Sum Equals K
- Longest Consecutive Sequence

## 双指针

```cpp
int left = 0, right = nums.size() - 1;
while (left < right) {
    int sum = nums[left] + nums[right];
    if (sum == target) {
        ...
    } else if (sum < target) {
        ++left;
    } else {
        --right;
    }
}
```

常见题：

- 3Sum
- Container With Most Water

## 滑动窗口

```cpp
int left = 0;
for (int right = 0; right < (int)s.size(); ++right) {
    add(s[right]);
    while (windowInvalid()) {
        remove(s[left]);
        ++left;
    }
    updateAnswer();
}
```

常见题：

- Longest Substring Without Repeating Characters
- Minimum Window Substring

## 前缀和

```cpp
unordered_map<int, int> cnt;
cnt[0] = 1;
int prefix = 0, ans = 0;
for (int x : nums) {
    prefix += x;
    if (cnt.count(prefix - k)) ans += cnt[prefix - k];
    ++cnt[prefix];
}
```

常见题：

- Subarray Sum Equals K

## stack / 单调栈

```cpp
stack<int> st; // 存下标
for (int i = 0; i < (int)nums.size(); ++i) {
    while (!st.empty() && nums[st.top()] < nums[i]) {
        int j = st.top();
        st.pop();
        ans[j] = i - j;
    }
    st.push(i);
}
```

常见题：

- Daily Temperatures
- Largest Rectangle in Histogram

## queue / BFS

```cpp
queue<pair<int, int>> q;
q.push({r, c});
while (!q.empty()) {
    int size = q.size();
    while (size--) {
        auto [x, y] = q.front();
        q.pop();
        ...
    }
}
```

常见题：

- Binary Tree Level Order Traversal
- Rotting Oranges

## priority_queue

默认大根堆：

```cpp
priority_queue<int> maxHeap;
```

小根堆：

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;
```

Top K 模板：

```cpp
priority_queue<int, vector<int>, greater<int>> heap;
for (int x : nums) {
    heap.push(x);
    if ((int)heap.size() > k) heap.pop();
}
return heap.top();
```

## 二分

```cpp
int left = 0, right = nums.size() - 1;
while (left <= right) {
    int mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target)
        left = mid + 1;
    else
        right = mid - 1;
}
return -1;
```

## 链表

LeetCode 默认结构：

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

反转链表：

```cpp
ListNode *prev = nullptr;
ListNode *cur = head;
while (cur) {
    ListNode *nxt = cur->next;
    cur->next = prev;
    prev = cur;
    cur = nxt;
}
return prev;
```

删除节点常用 dummy：

```cpp
ListNode dummy(0, head);
ListNode *slow = &dummy;
```

## 二叉树递归

```cpp
int maxDepth(TreeNode *root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```

DFS 写 lambda：

```cpp
function<int(TreeNode*)> dfs = [&](TreeNode *node) -> int {
    if (!node) return 0;
    int left = dfs(node->left);
    int right = dfs(node->right);
    return 1 + max(left, right);
};
```

## 回溯

```cpp
vector<vector<int>> ans;
vector<int> path;

function<void(int)> dfs = [&](int start) {
    ans.push_back(path);
    for (int i = start; i < (int)nums.size(); ++i) {
        path.push_back(nums[i]);
        dfs(i + 1);
        path.pop_back();
    }
};
dfs(0);
```

## DP 面试表达

答题顺序固定：

1. `dp[i]` 表示什么。
2. 状态转移方程。
3. 初始化。
4. 遍历顺序。
5. 时间和空间复杂度。

例：零钱兑换

```cpp
vector<int> dp(amount + 1, amount + 1);
dp[0] = 0;
for (int x = 1; x <= amount; ++x) {
    for (int coin : coins) {
        if (coin <= x) dp[x] = min(dp[x], dp[x - coin] + 1);
    }
}
return dp[amount] > amount ? -1 : dp[amount];
```

## C++ 面试高频坑

- `unordered_map[key]` 会插入默认值；只判断存在时用 `count`。
- `vector<int> dp(n)` 初始化为 0。
- `INT_MAX + 1` 会溢出，DP 里常用 `amount + 1` 当无穷。
- 链表删除头节点时用 dummy。
- 二分用 `mid = left + (right - left) / 2`。
- 树节点值可能到 `INT_MIN/INT_MAX`，BST 上下界用 `long long`。
- `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>` 是按 pair 字典序的小根堆。

