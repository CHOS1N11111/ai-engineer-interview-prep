# LeetCode 题型模板速查

这份用于面试前快速回忆“这类题该怎么起手”。

## 哈希表

识别信号：

- 查找是否存在另一个数、字符、前缀。
- 需要 O(1) 统计频次或位置。

模板：

```python
seen = {}
for i, x in enumerate(nums):
    if target - x in seen:
        return [seen[target - x], i]
    seen[x] = i
```

常见题：

- Two Sum
- Group Anagrams
- Longest Consecutive Sequence

## 双指针

识别信号：

- 数组有序。
- 要找两数/三数关系。
- 可以从两端向中间收缩。

模板：

```python
left, right = 0, len(nums) - 1
while left < right:
    total = nums[left] + nums[right]
    if total == target:
        ...
    elif total < target:
        left += 1
    else:
        right -= 1
```

常见题：

- 3Sum
- Container With Most Water
- Trapping Rain Water

## 滑动窗口

识别信号：

- 连续子数组/子串。
- 最长、最短、包含、无重复。

模板：

```python
left = 0
for right, x in enumerate(nums):
    add(x)
    while window_invalid():
        remove(nums[left])
        left += 1
    update_answer()
```

常见题：

- Longest Substring Without Repeating Characters
- Find All Anagrams in a String
- Minimum Window Substring

## 前缀和 + 哈希

识别信号：

- 连续子数组和等于 k。
- 数组里可能有负数，滑窗不好用。

模板：

```python
count = {0: 1}
prefix = ans = 0
for x in nums:
    prefix += x
    ans += count.get(prefix - k, 0)
    count[prefix] = count.get(prefix, 0) + 1
```

常见题：

- Subarray Sum Equals K

## 单调栈

识别信号：

- 下一个更大/更小元素。
- 柱状图面积。
- 当前元素要结算之前未结算的元素。

模板：

```python
stack = []
for i, x in enumerate(nums):
    while stack and nums[stack[-1]] < x:
        j = stack.pop()
        ans[j] = i - j
    stack.append(i)
```

常见题：

- Daily Temperatures
- Largest Rectangle in Histogram

## 二分

识别信号：

- 有序数组。
- 搜索答案。
- 旋转有序数组。

模板：

```python
left, right = 0, len(nums) - 1
while left <= right:
    mid = (left + right) // 2
    if nums[mid] == target:
        return mid
    elif nums[mid] < target:
        left = mid + 1
    else:
        right = mid - 1
return -1
```

常见题：

- Search in Rotated Sorted Array
- Find Minimum in Rotated Sorted Array
- Find First and Last Position

## 链表

识别信号：

- 删除、反转、合并、倒数第 k 个。

必备技巧：

- dummy head 处理删除头节点。
- 快慢指针处理环和倒数。
- 三指针反转链表。

反转模板：

```python
prev = None
curr = head
while curr:
    nxt = curr.next
    curr.next = prev
    prev = curr
    curr = nxt
return prev
```

## BFS

识别信号：

- 最短路径。
- 层序遍历。
- 网格扩散。

模板：

```python
from collections import deque

q = deque([start])
visited = {start}
steps = 0
while q:
    for _ in range(len(q)):
        node = q.popleft()
        for nxt in neighbors(node):
            if nxt not in visited:
                visited.add(nxt)
                q.append(nxt)
    steps += 1
```

常见题：

- Binary Tree Level Order Traversal
- Rotting Oranges
- Word Ladder

## DFS

识别信号：

- 连通块。
- 树递归。
- 路径搜索。

模板：

```python
def dfs(node):
    if not node:
        return base
    left = dfs(node.left)
    right = dfs(node.right)
    return combine(node, left, right)
```

常见题：

- Number of Islands
- Maximum Depth of Binary Tree
- Diameter of Binary Tree

## 回溯

识别信号：

- 所有排列、组合、子集。
- “返回所有方案”。

模板：

```python
ans = []
path = []

def backtrack(start):
    if is_solution():
        ans.append(path[:])
        return
    for i in range(start, n):
        path.append(nums[i])
        backtrack(i + 1)
        path.pop()
```

常见题：

- Permutations
- Subsets
- Combination Sum

## 动态规划

识别信号：

- 最值、计数、可行性。
- 当前状态依赖之前状态。

答题顺序：

1. 定义 `dp[i]`。
2. 写转移方程。
3. 初始化。
4. 确定遍历顺序。
5. 说复杂度。

模板：

```python
dp = [0] * (n + 1)
dp[0] = base
for i in range(1, n + 1):
    dp[i] = transition(...)
return dp[n]
```

常见题：

- Climbing Stairs
- Coin Change
- Longest Increasing Subsequence
- Longest Common Subsequence
- Edit Distance

