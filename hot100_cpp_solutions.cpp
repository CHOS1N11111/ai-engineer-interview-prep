#include <algorithm>
#include <cassert>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

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

class LRUCache {
private:
    int cap;
    list<pair<int, int>> items;
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

class Trie {
private:
    struct Node {
        bool isWord = false;
        unordered_map<char, Node *> children;
    };

    Node *root;

    Node *findNode(const string &s) {
        Node *cur = root;
        for (char ch : s) {
            if (!cur->children.count(ch)) return nullptr;
            cur = cur->children[ch];
        }
        return cur;
    }

public:
    Trie() : root(new Node()) {}

    void insert(string word) {
        Node *cur = root;
        for (char ch : word) {
            if (!cur->children.count(ch)) cur->children[ch] = new Node();
            cur = cur->children[ch];
        }
        cur->isWord = true;
    }

    bool search(string word) {
        Node *node = findNode(word);
        return node && node->isWord;
    }

    bool startsWith(string prefix) {
        return findNode(prefix) != nullptr;
    }
};

class Solution {
public:
    // 数组 / 哈希

    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int need = target - nums[i];
            if (seen.count(need)) return {seen[need], i};
            seen[nums[i]] = i;
        }
        return {};
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<string, vector<string>> groups;
        for (string s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            groups[key].push_back(s);
        }
        vector<vector<string>> ans;
        for (auto &kv : groups) ans.push_back(kv.second);
        return ans;
    }

    int longestConsecutive(vector<int> &nums) {
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (int x : st) {
            if (!st.count(x - 1)) {
                int y = x;
                while (st.count(y)) ++y;
                ans = max(ans, y - x);
            }
        }
        return ans;
    }

    void moveZeroes(vector<int> &nums) {
        int slow = 0;
        for (int fast = 0; fast < (int)nums.size(); ++fast) {
            if (nums[fast] != 0) swap(nums[slow++], nums[fast]);
        }
    }

    int maxArea(vector<int> &height) {
        int left = 0, right = (int)height.size() - 1;
        int ans = 0;
        while (left < right) {
            ans = max(ans, (right - left) * min(height[left], height[right]));
            if (height[left] < height[right])
                ++left;
            else
                --right;
        }
        return ans;
    }

    vector<vector<int>> threeSum(vector<int> &nums) {
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

    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        int prefix = 1;
        for (int i = 0; i < n; ++i) {
            ans[i] = prefix;
            prefix *= nums[i];
        }
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= suffix;
            suffix *= nums[i];
        }
        return ans;
    }

    // 滑动窗口 / 前缀和

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

    vector<int> findAnagrams(string s, string p) {
        vector<int> ans;
        if (s.size() < p.size()) return ans;
        vector<int> need(26, 0), window(26, 0);
        for (char ch : p) ++need[ch - 'a'];
        int left = 0;
        for (int right = 0; right < (int)s.size(); ++right) {
            ++window[s[right] - 'a'];
            if (right - left + 1 > (int)p.size()) {
                --window[s[left] - 'a'];
                ++left;
            }
            if (window == need) ans.push_back(left);
        }
        return ans;
    }

    int subarraySum(vector<int> &nums, int k) {
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

    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < (int)nums.size(); ++i) {
            while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
            dq.push_back(i);
            if (dq.front() <= i - k) dq.pop_front();
            if (i >= k - 1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }

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

    // 栈 / 单调栈

    bool isValid(string s) {
        unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        stack<char> st;
        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            } else {
                if (st.empty() || st.top() != pairs[ch]) return false;
                st.pop();
            }
        }
        return st.empty();
    }

    vector<int> dailyTemperatures(vector<int> &temperatures) {
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

    int largestRectangleArea(vector<int> &heights) {
        vector<int> h = heights;
        h.push_back(0);
        stack<int> st;
        int ans = 0;
        for (int i = 0; i < (int)h.size(); ++i) {
            while (!st.empty() && h[st.top()] > h[i]) {
                int height = h[st.top()];
                st.pop();
                int left = st.empty() ? -1 : st.top();
                ans = max(ans, height * (i - left - 1));
            }
            st.push(i);
        }
        return ans;
    }

    string decodeString(string s) {
        stack<pair<string, int>> st;
        string cur;
        int num = 0;
        for (char ch : s) {
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if (ch == '[') {
                st.push({cur, num});
                cur.clear();
                num = 0;
            } else if (ch == ']') {
                auto [prev, repeat] = st.top();
                st.pop();
                string tmp;
                while (repeat--) tmp += cur;
                cur = prev + tmp;
            } else {
                cur += ch;
            }
        }
        return cur;
    }

    // 二分 / 堆

    int search(vector<int> &nums, int target) {
        int left = 0, right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return -1;
    }

    int findMin(vector<int> &nums) {
        int left = 0, right = (int)nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;
            else
                right = mid;
        }
        return nums[left];
    }

    int findKthLargest(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int x : nums) {
            heap.push(x);
            if ((int)heap.size() > k) heap.pop();
        }
        return heap.top();
    }

    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> freq;
        for (int x : nums) ++freq[x];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        for (auto &[num, count] : freq) {
            heap.push({count, num});
            if ((int)heap.size() > k) heap.pop();
        }
        vector<int> ans;
        while (!heap.empty()) {
            ans.push_back(heap.top().second);
            heap.pop();
        }
        return ans;
    }

    // 链表

    ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (cur) {
            ListNode *nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
    }

    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        ListNode dummy;
        ListNode *tail = &dummy;
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        tail->next = list1 ? list1 : list2;
        return dummy.next;
    }

    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode *p = head;
                while (p != slow) {
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return nullptr;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode dummy(0, head);
        ListNode *fast = &dummy;
        ListNode *slow = &dummy;
        for (int i = 0; i < n; ++i) fast = fast->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummy.next;
    }

    // 二叉树

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ans;
        function<void(TreeNode *)> dfs = [&](TreeNode *node) {
            if (!node) return;
            dfs(node->left);
            ans.push_back(node->val);
            dfs(node->right);
        };
        dfs(root);
        return ans;
    }

    vector<vector<int>> levelOrder(TreeNode *root) {
        if (!root) return {};
        vector<vector<int>> ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            while (size--) {
                TreeNode *node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ans.push_back(level);
        }
        return ans;
    }

    int maxDepth(TreeNode *root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    TreeNode *invertTree(TreeNode *root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }

    int diameterOfBinaryTree(TreeNode *root) {
        int ans = 0;
        function<int(TreeNode *)> depth = [&](TreeNode *node) -> int {
            if (!node) return 0;
            int left = depth(node->left);
            int right = depth(node->right);
            ans = max(ans, left + right);
            return 1 + max(left, right);
        };
        depth(root);
        return ans;
    }

    bool isValidBST(TreeNode *root) {
        function<bool(TreeNode *, long long, long long)> dfs =
            [&](TreeNode *node, long long low, long long high) -> bool {
            if (!node) return true;
            if (!(low < node->val && node->val < high)) return false;
            return dfs(node->left, low, node->val) &&
                   dfs(node->right, node->val, high);
        };
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }

    int kthSmallest(TreeNode *root, int k) {
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top();
            st.pop();
            if (--k == 0) return cur->val;
            cur = cur->right;
        }
        return -1;
    }

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right) return root;
        return left ? left : right;
    }

    vector<int> rightSideView(TreeNode *root) {
        if (!root) return {};
        vector<int> ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                if (i == size - 1) ans.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ans;
    }

    int maxPathSum(TreeNode *root) {
        int ans = INT_MIN;
        function<int(TreeNode *)> gain = [&](TreeNode *node) -> int {
            if (!node) return 0;
            int left = max(0, gain(node->left));
            int right = max(0, gain(node->right));
            ans = max(ans, node->val + left + right);
            return node->val + max(left, right);
        };
        gain(root);
        return ans;
    }

    // 图 / BFS / DFS

    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int rows = grid.size(), cols = grid[0].size();
        int ans = 0;
        function<void(int, int)> dfs = [&](int r, int c) {
            if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
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

    int orangesRotting(vector<vector<int>> &grid) {
        int rows = grid.size(), cols = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2)
                    q.push({r, c});
                else if (grid[r][c] == 1)
                    ++fresh;
            }
        }
        int minutes = 0;
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty() && fresh > 0) {
            int size = q.size();
            while (size--) {
                auto [r, c] = q.front();
                q.pop();
                for (auto [dr, dc] : dirs) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        --fresh;
                        q.push({nr, nc});
                    }
                }
            }
            ++minutes;
        }
        return fresh == 0 ? minutes : -1;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        for (auto &e : prerequisites) {
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

    // 回溯

    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        function<void()> dfs = [&]() {
            if (path.size() == nums.size()) {
                ans.push_back(path);
                return;
            }
            for (int i = 0; i < (int)nums.size(); ++i) {
                if (used[i]) continue;
                used[i] = true;
                path.push_back(nums[i]);
                dfs();
                path.pop_back();
                used[i] = false;
            }
        };
        dfs();
        return ans;
    }

    vector<vector<int>> subsets(vector<int> &nums) {
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
        return ans;
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> path;
        function<void(int, int)> dfs = [&](int start, int remain) {
            if (remain == 0) {
                ans.push_back(path);
                return;
            }
            for (int i = start; i < (int)candidates.size(); ++i) {
                if (candidates[i] > remain) break;
                path.push_back(candidates[i]);
                dfs(i, remain - candidates[i]);
                path.pop_back();
            }
        };
        dfs(0, target);
        return ans;
    }

    // 动态规划 / 贪心

    int climbStairs(int n) {
        int a = 1, b = 1;
        for (int i = 0; i < n; ++i) {
            int c = a + b;
            a = b;
            b = c;
        }
        return a;
    }

    int rob(vector<int> &nums) {
        int prev2 = 0, prev1 = 0;
        for (int x : nums) {
            int cur = max(prev1, prev2 + x);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }

    int coinChange(vector<int> &coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int x = 1; x <= amount; ++x) {
            for (int coin : coins) {
                if (coin <= x) dp[x] = min(dp[x], dp[x - coin] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }

    int lengthOfLIS(vector<int> &nums) {
        vector<int> tails;
        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end())
                tails.push_back(x);
            else
                *it = x;
        }
        return tails.size();
    }

    int maxSubArray(vector<int> &nums) {
        int best = nums[0], cur = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            cur = max(nums[i], cur + nums[i]);
            best = max(best, cur);
        }
        return best;
    }

    bool canJump(vector<int> &nums) {
        int farthest = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i > farthest) return false;
            farthest = max(farthest, i + nums[i]);
        }
        return true;
    }

    int jump(vector<int> &nums) {
        int jumps = 0, curEnd = 0, farthest = 0;
        for (int i = 0; i < (int)nums.size() - 1; ++i) {
            farthest = max(farthest, i + nums[i]);
            if (i == curEnd) {
                ++jumps;
                curEnd = farthest;
            }
        }
        return jumps;
    }

    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) dp[c] += dp[c - 1];
        }
        return dp[n - 1];
    }

    int minPathSum(vector<vector<int>> &grid) {
        int rows = grid.size(), cols = grid[0].size();
        vector<int> dp(cols, INT_MAX);
        dp[0] = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (c == 0)
                    dp[c] += grid[r][c];
                else
                    dp[c] = min(dp[c], dp[c - 1]) + grid[r][c];
            }
        }
        return dp[cols - 1];
    }

    string longestPalindrome(string s) {
        int bestL = 0, bestR = 0;
        auto expand = [&](int left, int right) {
            while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
                --left;
                ++right;
            }
            ++left;
            --right;
            if (right - left > bestR - bestL) {
                bestL = left;
                bestR = right;
            }
        };
        for (int i = 0; i < (int)s.size(); ++i) {
            expand(i, i);
            expand(i, i + 1);
        }
        return s.substr(bestL, bestR - bestL + 1);
    }

    bool wordBreak(string s, vector<string> &wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= (int)s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && words.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }

    int longestCommonSubsequence(string text1, string text2) {
        int n = text2.size();
        vector<int> dp(n + 1, 0);
        for (char a : text1) {
            int prev = 0;
            for (int j = 1; j <= n; ++j) {
                int tmp = dp[j];
                if (a == text2[j - 1])
                    dp[j] = prev + 1;
                else
                    dp[j] = max(dp[j], dp[j - 1]);
                prev = tmp;
            }
        }
        return dp[n];
    }

    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n + 1);
        for (int j = 0; j <= n; ++j) dp[j] = j;
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0];
            dp[0] = i;
            for (int j = 1; j <= n; ++j) {
                int tmp = dp[j];
                if (word1[i - 1] == word2[j - 1])
                    dp[j] = prev;
                else
                    dp[j] = 1 + min({prev, dp[j], dp[j - 1]});
                prev = tmp;
            }
        }
        return dp[n];
    }

    // 区间 / 矩阵

    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        for (auto &itv : intervals) {
            if (ans.empty() || itv[0] > ans.back()[1])
                ans.push_back(itv);
            else
                ans.back()[1] = max(ans.back()[1], itv[1]);
        }
        return ans;
    }

    void rotate(vector<vector<int>> &matrix) {
        int n = matrix.size();
        for (int r = 0; r < n; ++r) {
            for (int c = r + 1; c < n; ++c) swap(matrix[r][c], matrix[c][r]);
        }
        for (auto &row : matrix) reverse(row.begin(), row.end());
    }
};

static ListNode *buildList(const vector<int> &values) {
    ListNode dummy;
    ListNode *tail = &dummy;
    for (int x : values) {
        tail->next = new ListNode(x);
        tail = tail->next;
    }
    return dummy.next;
}

static vector<int> listToVector(ListNode *head) {
    vector<int> ans;
    while (head) {
        ans.push_back(head->val);
        head = head->next;
    }
    return ans;
}

static void runSmokeTests() {
    Solution s;

    vector<int> a1 = {2, 7, 11, 15};
    vector<int> expectedTwoSum = {0, 1};
    assert(s.twoSum(a1, 9) == expectedTwoSum);

    vector<int> a2 = {100, 4, 200, 1, 3, 2};
    assert(s.longestConsecutive(a2) == 4);

    vector<int> a3 = {0, 1, 0, 3, 12};
    s.moveZeroes(a3);
    vector<int> expectedMoveZeroes = {1, 3, 12, 0, 0};
    assert(a3 == expectedMoveZeroes);

    vector<int> a4 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    assert(s.maxArea(a4) == 49);

    vector<int> a5 = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> expectedThreeSum = {{-1, -1, 2}, {-1, 0, 1}};
    assert(s.threeSum(a5) == expectedThreeSum);

    vector<int> a6 = {1, 2, 3, 4};
    vector<int> expectedProduct = {24, 12, 8, 6};
    assert(s.productExceptSelf(a6) == expectedProduct);

    assert(s.lengthOfLongestSubstring("abcabcbb") == 3);
    vector<int> expectedAnagrams = {0, 6};
    assert(s.findAnagrams("cbaebabacd", "abc") == expectedAnagrams);

    vector<int> a7 = {1, 1, 1};
    assert(s.subarraySum(a7, 2) == 2);

    vector<int> a8 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> expectedWindow = {3, 3, 5, 5, 6, 7};
    assert(s.maxSlidingWindow(a8, 3) == expectedWindow);
    assert(s.minWindow("ADOBECODEBANC", "ABC") == "BANC");

    assert(s.isValid("()[]{}"));
    assert(!s.isValid("(]"));

    vector<int> a9 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> expectedTemperatures = {1, 1, 4, 2, 1, 1, 0, 0};
    assert(s.dailyTemperatures(a9) == expectedTemperatures);

    vector<int> a10 = {2, 1, 5, 6, 2, 3};
    assert(s.largestRectangleArea(a10) == 10);
    assert(s.decodeString("3[a2[c]]") == "accaccacc");

    vector<int> a11 = {4, 5, 6, 7, 0, 1, 2};
    assert(s.search(a11, 0) == 4);

    vector<int> a12 = {3, 4, 5, 1, 2};
    assert(s.findMin(a12) == 1);

    vector<int> a13 = {3, 2, 1, 5, 6, 4};
    assert(s.findKthLargest(a13, 2) == 5);

    vector<int> a14 = {1, 1, 1, 2, 2, 3};
    vector<int> top = s.topKFrequent(a14, 2);
    sort(top.begin(), top.end());
    vector<int> expectedTopK = {1, 2};
    assert(top == expectedTopK);

    vector<int> expectedReverse = {3, 2, 1};
    assert(listToVector(s.reverseList(buildList({1, 2, 3}))) == expectedReverse);
    vector<int> expectedMergeLists = {1, 1, 2, 3, 4, 4};
    assert(listToVector(s.mergeTwoLists(buildList({1, 2, 4}), buildList({1, 3, 4}))) ==
           expectedMergeLists);
    vector<int> expectedRemoveNth = {1, 2, 3, 5};
    assert(listToVector(s.removeNthFromEnd(buildList({1, 2, 3, 4, 5}), 2)) ==
           expectedRemoveNth);

    TreeNode *root = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    vector<int> expectedInorder = {1, 2, 3};
    assert(s.inorderTraversal(root) == expectedInorder);
    vector<vector<int>> expectedLevelOrder = {{2}, {1, 3}};
    assert(s.levelOrder(root) == expectedLevelOrder);
    assert(s.maxDepth(root) == 2);
    assert(s.isValidBST(root));
    assert(s.kthSmallest(root, 2) == 2);

    vector<vector<char>> grid = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}};
    assert(s.numIslands(grid) == 1);

    vector<vector<int>> oranges = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    assert(s.orangesRotting(oranges) == 4);

    vector<vector<int>> pre = {{1, 0}};
    assert(s.canFinish(2, pre));

    vector<int> p = {1, 2};
    auto perms = s.permute(p);
    sort(perms.begin(), perms.end());
    vector<vector<int>> expectedPerms = {{1, 2}, {2, 1}};
    assert(perms == expectedPerms);

    vector<int> sub = {1, 2};
    auto subsets = s.subsets(sub);
    sort(subsets.begin(), subsets.end());
    vector<vector<int>> expectedSubsets = {{}, {1}, {1, 2}, {2}};
    assert(subsets == expectedSubsets);

    vector<int> coins1 = {1, 2, 5};
    assert(s.coinChange(coins1, 11) == 3);

    vector<int> lis = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(s.lengthOfLIS(lis) == 4);

    vector<int> maxSub = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(s.maxSubArray(maxSub) == 6);

    vector<int> jump1 = {2, 3, 1, 1, 4};
    assert(s.canJump(jump1));
    assert(s.jump(jump1) == 2);

    assert(s.uniquePaths(3, 7) == 28);

    vector<vector<int>> path = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    assert(s.minPathSum(path) == 7);

    string pal = s.longestPalindrome("babad");
    assert(pal == "bab" || pal == "aba");

    vector<string> dict = {"leet", "code"};
    assert(s.wordBreak("leetcode", dict));
    assert(s.longestCommonSubsequence("abcde", "ace") == 3);
    assert(s.minDistance("horse", "ros") == 3);

    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> expectedIntervals = {{1, 6}, {8, 10}, {15, 18}};
    assert(s.merge(intervals) == expectedIntervals);

    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    s.rotate(matrix);
    vector<vector<int>> expectedMatrix = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
    assert(matrix == expectedMatrix);

    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    assert(cache.get(1) == 1);
    cache.put(3, 3);
    assert(cache.get(2) == -1);

    Trie trie;
    trie.insert("apple");
    assert(trie.search("apple"));
    assert(!trie.search("app"));
    assert(trie.startsWith("app"));
}

int main() {
    runSmokeTests();
    cout << "All C++ smoke tests passed." << endl;
    return 0;
}
