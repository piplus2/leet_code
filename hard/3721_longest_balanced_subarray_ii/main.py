
from typing import List
from collections import defaultdict

class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        
        orig_n = len(nums)
        last_seen = {}

        n = 1
        while n < orig_n:
            n *= 2

        tree = [[0, 0, 0] for _ in range(2 * n)]

        def update(i, val):
            i += n
            tree[i] = [val, min(0, val), max(0, val)]
            
            i //= 2
            while i >= 1:
                l = 2*i
                r = l + 1
                new_sum = tree[l][0] + tree[r][0]
                new_min = min(tree[l][1], tree[l][0]+tree[r][1])
                new_max = max(tree[l][2], tree[l][0] + tree[r][2])
                tree[i] = [new_sum, new_min, new_max]
                i //= 2
        
        def find_leftmost(node_idx, current_sum, target):
            if node_idx >= n:
                return node_idx - n if current_sum + tree[node_idx][0] == target else None
            
            left_child = 2 * node_idx
            right_child = left_child + 1

            left_min = current_sum + tree[left_child][1]
            left_max = current_sum + tree[left_child][2]

            if left_min <= target <= left_max:
                return find_leftmost(left_child, current_sum, target)

            new_sum = current_sum + tree[left_child][0]
            return find_leftmost(right_child, new_sum, target)

        max_len = 0

        for j in range(orig_n):
            if nums[j] in last_seen:
                update(last_seen[nums[j]], 0)

            if nums[j] % 2 == 0:
                update(j, 1)
            else:
                update(j, -1)
            last_seen[nums[j]] = j

            s_tot = tree[1][0]
            if s_tot == 0:
                max_len = max(max_len, j + 1)
            else:
                i = find_leftmost(node_idx=1, current_sum=0, target=s_tot)
                if i is not None:
                    max_len = max(max_len, j - i)

        return max_len