# LeetCode 热题手撕代码准备

面向 AI Agent / AI 应用研发工程师实习面试，算法部分按 LeetCode Hot 100 / 高频面试题型准备。目标不是背答案，而是把题型识别、代码模板、边界测试、复杂度表达练到稳定。

默认语言：C++17。

核心文件：

- `hot100_cpp_solutions.cpp`：C++ 高频题解和本地 smoke tests。
- `cpp_pattern_cheatsheet.md`：C++ 手撕代码模板速查。
- `mock_interview_drills.md`：模拟面试题和追问。
- `hot100_python_solutions.py`：之前生成的 Python 版本，保留作对照，不作为主练习语言。

## 面试手撕标准流程

1. 复述题意：确认输入、输出、是否有重复、是否有序、数据范围。
2. 说暴力解：快速给出 baseline，方便引出优化。
3. 抓题型：哈希、双指针、滑窗、栈、堆、二分、DFS/BFS、DP。
4. 写核心不变量：例如窗口内无重复、单调栈从栈底到栈顶递减。
5. 写代码：先主逻辑，后处理边界。
6. 自测：空输入、单元素、重复值、极端值。
7. 复杂度：时间、空间都要说清楚。

## 4 周冲刺路线

### 第 1 周：数组、哈希、双指针、滑动窗口

必须熟练：

- 1 Two Sum
- 49 Group Anagrams
- 128 Longest Consecutive Sequence
- 283 Move Zeroes
- 11 Container With Most Water
- 15 3Sum
- 42 Trapping Rain Water
- 3 Longest Substring Without Repeating Characters
- 438 Find All Anagrams in a String
- 560 Subarray Sum Equals K
- 239 Sliding Window Maximum
- 76 Minimum Window Substring

手撕重点：

- 哈希表查补数
- 集合去重
- 左右指针移动条件
- 窗口何时扩张、何时收缩
- 前缀和 + 哈希计数

### 第 2 周：链表、栈、二分、堆

必须熟练：

- 20 Valid Parentheses
- 155 Min Stack
- 394 Decode String
- 739 Daily Temperatures
- 84 Largest Rectangle in Histogram
- 206 Reverse Linked List
- 21 Merge Two Sorted Lists
- 141 Linked List Cycle
- 142 Linked List Cycle II
- 19 Remove Nth Node From End of List
- 24 Swap Nodes in Pairs
- 25 Reverse Nodes in k-Group
- 146 LRU Cache
- 215 Kth Largest Element in an Array
- 347 Top K Frequent Elements
- 33 Search in Rotated Sorted Array
- 34 Find First and Last Position of Element in Sorted Array
- 153 Find Minimum in Rotated Sorted Array

手撕重点：

- dummy head
- 快慢指针
- 链表反转三指针
- 单调栈
- 堆维护 top-k
- 二分的闭区间写法

### 第 3 周：树、图、回溯

必须熟练：

- 94 Binary Tree Inorder Traversal
- 102 Binary Tree Level Order Traversal
- 104 Maximum Depth of Binary Tree
- 226 Invert Binary Tree
- 543 Diameter of Binary Tree
- 98 Validate Binary Search Tree
- 230 Kth Smallest Element in a BST
- 236 Lowest Common Ancestor of a Binary Tree
- 199 Binary Tree Right Side View
- 105 Construct Binary Tree from Preorder and Inorder Traversal
- 124 Binary Tree Maximum Path Sum
- 200 Number of Islands
- 994 Rotting Oranges
- 207 Course Schedule
- 208 Implement Trie
- 46 Permutations
- 78 Subsets
- 39 Combination Sum
- 17 Letter Combinations of a Phone Number

手撕重点：

- 递归返回值定义
- DFS visited 标记
- BFS 队列层序
- 拓扑排序入度
- 回溯 path / used / startIndex

### 第 4 周：动态规划、贪心、综合模拟

必须熟练：

- 70 Climbing Stairs
- 198 House Robber
- 322 Coin Change
- 300 Longest Increasing Subsequence
- 53 Maximum Subarray
- 55 Jump Game
- 45 Jump Game II
- 62 Unique Paths
- 64 Minimum Path Sum
- 5 Longest Palindromic Substring
- 1143 Longest Common Subsequence
- 139 Word Break
- 72 Edit Distance
- 121 Best Time to Buy and Sell Stock
- 152 Maximum Product Subarray
- 56 Merge Intervals
- 31 Next Permutation
- 48 Rotate Image
- 238 Product of Array Except Self

手撕重点：

- dp[i] 的含义
- 状态转移
- 初始化
- 遍历顺序
- 空间压缩
- 贪心局部最优如何推出全局最优

## 每天练习节奏

- 20 分钟：手写 1 道新题，不看答案。
- 10 分钟：对照题解修正边界。
- 10 分钟：口述思路和复杂度。
- 10 分钟：复写昨天错题。

## 面试前 3 天只练这些

如果时间很紧，优先手撕：

- Two Sum
- 3Sum
- Longest Substring Without Repeating Characters
- Subarray Sum Equals K
- Sliding Window Maximum
- Valid Parentheses
- Daily Temperatures
- Reverse Linked List
- Remove Nth Node From End of List
- LRU Cache
- Binary Tree Level Order Traversal
- Validate Binary Search Tree
- Lowest Common Ancestor
- Number of Islands
- Course Schedule
- Coin Change
- Longest Increasing Subsequence
- Maximum Subarray
- Merge Intervals
- Product of Array Except Self

## 资料说明

- `hot100_cpp_solutions.cpp`：高频题 C++17 可运行答案。
- `cpp_pattern_cheatsheet.md`：C++ STL 和题型模板。
- `hot100_python_solutions.py`：Python 对照版本。
- `mock_interview_drills.md`：模拟面试题单和追问方式。
