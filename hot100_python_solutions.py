from __future__ import annotations

from collections import Counter, defaultdict, deque, OrderedDict
from dataclasses import dataclass
from heapq import heappush, heappushpop, nlargest
from typing import Dict, List, Optional


@dataclass
class ListNode:
    val: int = 0
    next: Optional["ListNode"] = None


@dataclass
class TreeNode:
    val: int = 0
    left: Optional["TreeNode"] = None
    right: Optional["TreeNode"] = None


class LRUCache:
    """LeetCode 146. Python 面试可先写 OrderedDict，再说明双向链表版本。"""

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache: OrderedDict[int, int] = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache.move_to_end(key)
        self.cache[key] = value
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)


class TrieNode:
    def __init__(self):
        self.children: Dict[str, "TrieNode"] = {}
        self.is_word = False


class Trie:
    """LeetCode 208."""

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node = self.root
        for ch in word:
            node = node.children.setdefault(ch, TrieNode())
        node.is_word = True

    def search(self, word: str) -> bool:
        node = self._find(word)
        return bool(node and node.is_word)

    def startsWith(self, prefix: str) -> bool:
        return self._find(prefix) is not None

    def _find(self, text: str) -> Optional[TrieNode]:
        node = self.root
        for ch in text:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node


class Hot100Solutions:
    # 数组 / 哈希

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        seen = {}
        for i, x in enumerate(nums):
            if target - x in seen:
                return [seen[target - x], i]
            seen[x] = i
        return []

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)
        for s in strs:
            groups[tuple(sorted(s))].append(s)
        return list(groups.values())

    def longestConsecutive(self, nums: List[int]) -> int:
        values = set(nums)
        ans = 0
        for x in values:
            if x - 1 not in values:
                y = x
                while y in values:
                    y += 1
                ans = max(ans, y - x)
        return ans

    def moveZeroes(self, nums: List[int]) -> None:
        slow = 0
        for fast, x in enumerate(nums):
            if x != 0:
                nums[slow], nums[fast] = nums[fast], nums[slow]
                slow += 1

    def maxArea(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        ans = 0
        while left < right:
            ans = max(ans, (right - left) * min(height[left], height[right]))
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        return ans

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        ans = []
        n = len(nums)
        for i in range(n - 2):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            if nums[i] > 0:
                break
            left, right = i + 1, n - 1
            while left < right:
                total = nums[i] + nums[left] + nums[right]
                if total == 0:
                    ans.append([nums[i], nums[left], nums[right]])
                    left += 1
                    right -= 1
                    while left < right and nums[left] == nums[left - 1]:
                        left += 1
                    while left < right and nums[right] == nums[right + 1]:
                        right -= 1
                elif total < 0:
                    left += 1
                else:
                    right -= 1
        return ans

    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [1] * n
        prefix = 1
        for i in range(n):
            ans[i] = prefix
            prefix *= nums[i]
        suffix = 1
        for i in range(n - 1, -1, -1):
            ans[i] *= suffix
            suffix *= nums[i]
        return ans

    # 滑动窗口 / 前缀和

    def lengthOfLongestSubstring(self, s: str) -> int:
        last = {}
        left = 0
        ans = 0
        for right, ch in enumerate(s):
            if ch in last and last[ch] >= left:
                left = last[ch] + 1
            last[ch] = right
            ans = max(ans, right - left + 1)
        return ans

    def findAnagrams(self, s: str, p: str) -> List[int]:
        need = Counter(p)
        window = Counter()
        ans = []
        left = 0
        for right, ch in enumerate(s):
            window[ch] += 1
            if right - left + 1 > len(p):
                old = s[left]
                window[old] -= 1
                if window[old] == 0:
                    del window[old]
                left += 1
            if window == need:
                ans.append(left)
        return ans

    def subarraySum(self, nums: List[int], k: int) -> int:
        prefix_count = defaultdict(int)
        prefix_count[0] = 1
        prefix = 0
        ans = 0
        for x in nums:
            prefix += x
            ans += prefix_count[prefix - k]
            prefix_count[prefix] += 1
        return ans

    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        q = deque()
        ans = []
        for i, x in enumerate(nums):
            while q and nums[q[-1]] <= x:
                q.pop()
            q.append(i)
            if q[0] <= i - k:
                q.popleft()
            if i >= k - 1:
                ans.append(nums[q[0]])
        return ans

    def minWindow(self, s: str, t: str) -> str:
        if not t:
            return ""
        need = Counter(t)
        missing = len(t)
        left = 0
        best_start = 0
        best_len = float("inf")
        for right, ch in enumerate(s):
            if need[ch] > 0:
                missing -= 1
            need[ch] -= 1
            while missing == 0:
                if right - left + 1 < best_len:
                    best_start = left
                    best_len = right - left + 1
                old = s[left]
                need[old] += 1
                if need[old] > 0:
                    missing += 1
                left += 1
        return "" if best_len == float("inf") else s[best_start : best_start + best_len]

    # 栈 / 单调栈

    def isValid(self, s: str) -> bool:
        pairs = {")": "(", "]": "[", "}": "{"}
        stack = []
        for ch in s:
            if ch in pairs.values():
                stack.append(ch)
            elif not stack or stack.pop() != pairs[ch]:
                return False
        return not stack

    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        ans = [0] * len(temperatures)
        stack = []
        for i, t in enumerate(temperatures):
            while stack and temperatures[stack[-1]] < t:
                j = stack.pop()
                ans[j] = i - j
            stack.append(i)
        return ans

    def largestRectangleArea(self, heights: List[int]) -> int:
        stack = []
        ans = 0
        for i, h in enumerate(heights + [0]):
            while stack and heights[stack[-1]] > h:
                height = heights[stack.pop()]
                left = stack[-1] if stack else -1
                ans = max(ans, height * (i - left - 1))
            stack.append(i)
        return ans

    def decodeString(self, s: str) -> str:
        stack = []
        curr = ""
        num = 0
        for ch in s:
            if ch.isdigit():
                num = num * 10 + int(ch)
            elif ch == "[":
                stack.append((curr, num))
                curr = ""
                num = 0
            elif ch == "]":
                prev, repeat = stack.pop()
                curr = prev + curr * repeat
            else:
                curr += ch
        return curr

    # 二分 / 堆

    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                return mid
            if nums[left] <= nums[mid]:
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1

    def findMin(self, nums: List[int]) -> int:
        left, right = 0, len(nums) - 1
        while left < right:
            mid = (left + right) // 2
            if nums[mid] > nums[right]:
                left = mid + 1
            else:
                right = mid
        return nums[left]

    def findKthLargest(self, nums: List[int], k: int) -> int:
        heap = []
        for x in nums:
            if len(heap) < k:
                heappush(heap, x)
            elif x > heap[0]:
                heappushpop(heap, x)
        return heap[0]

    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        return [x for x, _ in nlargest(k, Counter(nums).items(), key=lambda item: item[1])]

    # 链表

    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev = None
        curr = head
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        return prev

    def mergeTwoLists(
        self, list1: Optional[ListNode], list2: Optional[ListNode]
    ) -> Optional[ListNode]:
        dummy = ListNode()
        tail = dummy
        while list1 and list2:
            if list1.val <= list2.val:
                tail.next = list1
                list1 = list1.next
            else:
                tail.next = list2
                list2 = list2.next
            tail = tail.next
        tail.next = list1 or list2
        return dummy.next

    def hasCycle(self, head: Optional[ListNode]) -> bool:
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow is fast:
                return True
        return False

    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow is fast:
                break
        else:
            return None
        p = head
        while p is not slow:
            p = p.next
            slow = slow.next
        return p

    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        fast = slow = dummy
        for _ in range(n):
            fast = fast.next
        while fast.next:
            fast = fast.next
            slow = slow.next
        slow.next = slow.next.next
        return dummy.next

    # 二叉树

    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        ans = []

        def dfs(node: Optional[TreeNode]) -> None:
            if not node:
                return
            dfs(node.left)
            ans.append(node.val)
            dfs(node.right)

        dfs(root)
        return ans

    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        ans = []
        q = deque([root])
        while q:
            level = []
            for _ in range(len(q)):
                node = q.popleft()
                level.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ans.append(level)
        return ans

    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))

    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None
        root.left, root.right = self.invertTree(root.right), self.invertTree(root.left)
        return root

    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def depth(node: Optional[TreeNode]) -> int:
            nonlocal ans
            if not node:
                return 0
            left = depth(node.left)
            right = depth(node.right)
            ans = max(ans, left + right)
            return 1 + max(left, right)

        depth(root)
        return ans

    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(node: Optional[TreeNode], low: float, high: float) -> bool:
            if not node:
                return True
            if not low < node.val < high:
                return False
            return dfs(node.left, low, node.val) and dfs(node.right, node.val, high)

        return dfs(root, float("-inf"), float("inf"))

    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        stack = []
        node = root
        while stack or node:
            while node:
                stack.append(node)
                node = node.left
            node = stack.pop()
            k -= 1
            if k == 0:
                return node.val
            node = node.right
        raise ValueError("k is larger than tree size")

    def lowestCommonAncestor(
        self, root: TreeNode, p: TreeNode, q: TreeNode
    ) -> Optional[TreeNode]:
        if not root or root is p or root is q:
            return root
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if left and right:
            return root
        return left or right

    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        ans = []
        q = deque([root])
        while q:
            for i in range(len(q)):
                node = q.popleft()
                if i == 0:
                    ans.append(node.val)
                if node.right:
                    q.append(node.right)
                if node.left:
                    q.append(node.left)
        return ans

    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        ans = float("-inf")

        def gain(node: Optional[TreeNode]) -> int:
            nonlocal ans
            if not node:
                return 0
            left = max(gain(node.left), 0)
            right = max(gain(node.right), 0)
            ans = max(ans, node.val + left + right)
            return node.val + max(left, right)

        gain(root)
        return int(ans)

    # 图 / BFS / DFS

    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid or not grid[0]:
            return 0
        rows, cols = len(grid), len(grid[0])
        ans = 0

        def dfs(r: int, c: int) -> None:
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != "1":
                return
            grid[r][c] = "0"
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "1":
                    ans += 1
                    dfs(r, c)
        return ans

    def orangesRotting(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        q = deque()
        fresh = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    q.append((r, c))
                elif grid[r][c] == 1:
                    fresh += 1
        minutes = 0
        dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
        while q and fresh:
            for _ in range(len(q)):
                r, c = q.popleft()
                for dr, dc in dirs:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2
                        fresh -= 1
                        q.append((nr, nc))
            minutes += 1
        return minutes if fresh == 0 else -1

    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        graph = [[] for _ in range(numCourses)]
        indegree = [0] * numCourses
        for course, pre in prerequisites:
            graph[pre].append(course)
            indegree[course] += 1
        q = deque(i for i, d in enumerate(indegree) if d == 0)
        seen = 0
        while q:
            node = q.popleft()
            seen += 1
            for nxt in graph[node]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    q.append(nxt)
        return seen == numCourses

    # 回溯

    def permute(self, nums: List[int]) -> List[List[int]]:
        ans = []
        used = [False] * len(nums)
        path = []

        def backtrack() -> None:
            if len(path) == len(nums):
                ans.append(path[:])
                return
            for i, x in enumerate(nums):
                if used[i]:
                    continue
                used[i] = True
                path.append(x)
                backtrack()
                path.pop()
                used[i] = False

        backtrack()
        return ans

    def subsets(self, nums: List[int]) -> List[List[int]]:
        ans = []
        path = []

        def backtrack(start: int) -> None:
            ans.append(path[:])
            for i in range(start, len(nums)):
                path.append(nums[i])
                backtrack(i + 1)
                path.pop()

        backtrack(0)
        return ans

    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()
        ans = []
        path = []

        def backtrack(start: int, remain: int) -> None:
            if remain == 0:
                ans.append(path[:])
                return
            for i in range(start, len(candidates)):
                x = candidates[i]
                if x > remain:
                    break
                path.append(x)
                backtrack(i, remain - x)
                path.pop()

        backtrack(0, target)
        return ans

    # 动态规划 / 贪心

    def climbStairs(self, n: int) -> int:
        a, b = 1, 1
        for _ in range(n):
            a, b = b, a + b
        return a

    def rob(self, nums: List[int]) -> int:
        prev2 = prev1 = 0
        for x in nums:
            prev2, prev1 = prev1, max(prev1, prev2 + x)
        return prev1

    def coinChange(self, coins: List[int], amount: int) -> int:
        inf = amount + 1
        dp = [0] + [inf] * amount
        for x in range(1, amount + 1):
            for coin in coins:
                if coin <= x:
                    dp[x] = min(dp[x], dp[x - coin] + 1)
        return -1 if dp[amount] == inf else dp[amount]

    def lengthOfLIS(self, nums: List[int]) -> int:
        import bisect

        tails = []
        for x in nums:
            i = bisect.bisect_left(tails, x)
            if i == len(tails):
                tails.append(x)
            else:
                tails[i] = x
        return len(tails)

    def maxSubArray(self, nums: List[int]) -> int:
        best = curr = nums[0]
        for x in nums[1:]:
            curr = max(x, curr + x)
            best = max(best, curr)
        return best

    def canJump(self, nums: List[int]) -> bool:
        farthest = 0
        for i, step in enumerate(nums):
            if i > farthest:
                return False
            farthest = max(farthest, i + step)
        return True

    def jump(self, nums: List[int]) -> int:
        jumps = 0
        curr_end = 0
        farthest = 0
        for i in range(len(nums) - 1):
            farthest = max(farthest, i + nums[i])
            if i == curr_end:
                jumps += 1
                curr_end = farthest
        return jumps

    def uniquePaths(self, m: int, n: int) -> int:
        dp = [1] * n
        for _ in range(1, m):
            for c in range(1, n):
                dp[c] += dp[c - 1]
        return dp[-1]

    def minPathSum(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        dp = [float("inf")] * cols
        dp[0] = 0
        for r in range(rows):
            for c in range(cols):
                if c == 0:
                    dp[c] += grid[r][c]
                else:
                    dp[c] = min(dp[c], dp[c - 1]) + grid[r][c]
        return int(dp[-1])

    def longestPalindrome(self, s: str) -> str:
        if not s:
            return ""
        best_l = best_r = 0

        def expand(left: int, right: int) -> None:
            nonlocal best_l, best_r
            while left >= 0 and right < len(s) and s[left] == s[right]:
                left -= 1
                right += 1
            left += 1
            right -= 1
            if right - left > best_r - best_l:
                best_l, best_r = left, right

        for i in range(len(s)):
            expand(i, i)
            expand(i, i + 1)
        return s[best_l : best_r + 1]

    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        dp = [False] * (len(s) + 1)
        dp[0] = True
        for i in range(1, len(s) + 1):
            for j in range(i):
                if dp[j] and s[j:i] in words:
                    dp[i] = True
                    break
        return dp[-1]

    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        cols = len(text2)
        dp = [0] * (cols + 1)
        for ch1 in text1:
            prev = 0
            for j, ch2 in enumerate(text2, 1):
                tmp = dp[j]
                if ch1 == ch2:
                    dp[j] = prev + 1
                else:
                    dp[j] = max(dp[j], dp[j - 1])
                prev = tmp
        return dp[-1]

    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        dp = list(range(n + 1))
        for i in range(1, m + 1):
            prev = dp[0]
            dp[0] = i
            for j in range(1, n + 1):
                tmp = dp[j]
                if word1[i - 1] == word2[j - 1]:
                    dp[j] = prev
                else:
                    dp[j] = 1 + min(prev, dp[j], dp[j - 1])
                prev = tmp
        return dp[-1]

    # 区间 / 矩阵

    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        ans = []
        for start, end in intervals:
            if not ans or start > ans[-1][1]:
                ans.append([start, end])
            else:
                ans[-1][1] = max(ans[-1][1], end)
        return ans

    def rotate(self, matrix: List[List[int]]) -> None:
        n = len(matrix)
        for r in range(n):
            for c in range(r + 1, n):
                matrix[r][c], matrix[c][r] = matrix[c][r], matrix[r][c]
        for row in matrix:
            row.reverse()


def _list_to_linked(values: List[int]) -> Optional[ListNode]:
    dummy = ListNode()
    tail = dummy
    for x in values:
        tail.next = ListNode(x)
        tail = tail.next
    return dummy.next


def _linked_to_list(head: Optional[ListNode]) -> List[int]:
    ans = []
    while head:
        ans.append(head.val)
        head = head.next
    return ans


def _run_smoke_tests() -> None:
    s = Hot100Solutions()

    assert s.twoSum([2, 7, 11, 15], 9) == [0, 1]
    assert sorted(s.groupAnagrams(["eat", "tea", "tan", "ate", "nat", "bat"])) == sorted(
        [["eat", "tea", "ate"], ["tan", "nat"], ["bat"]]
    )
    assert s.longestConsecutive([100, 4, 200, 1, 3, 2]) == 4
    nums = [0, 1, 0, 3, 12]
    s.moveZeroes(nums)
    assert nums == [1, 3, 12, 0, 0]
    assert s.maxArea([1, 8, 6, 2, 5, 4, 8, 3, 7]) == 49
    assert s.threeSum([-1, 0, 1, 2, -1, -4]) == [[-1, -1, 2], [-1, 0, 1]]
    assert s.productExceptSelf([1, 2, 3, 4]) == [24, 12, 8, 6]

    assert s.lengthOfLongestSubstring("abcabcbb") == 3
    assert s.findAnagrams("cbaebabacd", "abc") == [0, 6]
    assert s.subarraySum([1, 1, 1], 2) == 2
    assert s.maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3) == [3, 3, 5, 5, 6, 7]
    assert s.minWindow("ADOBECODEBANC", "ABC") == "BANC"

    assert s.isValid("()[]{}")
    assert not s.isValid("(]")
    assert s.dailyTemperatures([73, 74, 75, 71, 69, 72, 76, 73]) == [
        1,
        1,
        4,
        2,
        1,
        1,
        0,
        0,
    ]
    assert s.largestRectangleArea([2, 1, 5, 6, 2, 3]) == 10
    assert s.decodeString("3[a2[c]]") == "accaccacc"

    assert s.search([4, 5, 6, 7, 0, 1, 2], 0) == 4
    assert s.findMin([3, 4, 5, 1, 2]) == 1
    assert s.findKthLargest([3, 2, 1, 5, 6, 4], 2) == 5
    assert sorted(s.topKFrequent([1, 1, 1, 2, 2, 3], 2)) == [1, 2]

    assert _linked_to_list(s.reverseList(_list_to_linked([1, 2, 3]))) == [3, 2, 1]
    assert _linked_to_list(
        s.mergeTwoLists(_list_to_linked([1, 2, 4]), _list_to_linked([1, 3, 4]))
    ) == [1, 1, 2, 3, 4, 4]
    assert _linked_to_list(s.removeNthFromEnd(_list_to_linked([1, 2, 3, 4, 5]), 2)) == [
        1,
        2,
        3,
        5,
    ]

    root = TreeNode(2, TreeNode(1), TreeNode(3))
    assert s.inorderTraversal(root) == [1, 2, 3]
    assert s.levelOrder(root) == [[2], [1, 3]]
    assert s.maxDepth(root) == 2
    assert s.isValidBST(root)
    assert s.kthSmallest(root, 2) == 2

    grid = [list("11110"), list("11010"), list("11000"), list("00000")]
    assert s.numIslands(grid) == 1
    assert s.orangesRotting([[2, 1, 1], [1, 1, 0], [0, 1, 1]]) == 4
    assert s.canFinish(2, [[1, 0]])

    assert sorted(s.permute([1, 2])) == [[1, 2], [2, 1]]
    assert sorted(s.subsets([1, 2])) == [[], [1], [1, 2], [2]]
    assert s.combinationSum([2, 3, 6, 7], 7) == [[2, 2, 3], [7]]

    assert s.climbStairs(3) == 3
    assert s.rob([1, 2, 3, 1]) == 4
    assert s.coinChange([1, 2, 5], 11) == 3
    assert s.lengthOfLIS([10, 9, 2, 5, 3, 7, 101, 18]) == 4
    assert s.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]) == 6
    assert s.canJump([2, 3, 1, 1, 4])
    assert s.jump([2, 3, 1, 1, 4]) == 2
    assert s.uniquePaths(3, 7) == 28
    assert s.minPathSum([[1, 3, 1], [1, 5, 1], [4, 2, 1]]) == 7
    assert s.longestPalindrome("babad") in {"bab", "aba"}
    assert s.wordBreak("leetcode", ["leet", "code"])
    assert s.longestCommonSubsequence("abcde", "ace") == 3
    assert s.minDistance("horse", "ros") == 3
    assert s.merge([[1, 3], [2, 6], [8, 10], [15, 18]]) == [[1, 6], [8, 10], [15, 18]]
    matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    s.rotate(matrix)
    assert matrix == [[7, 4, 1], [8, 5, 2], [9, 6, 3]]


if __name__ == "__main__":
    _run_smoke_tests()
    print("All smoke tests passed.")

