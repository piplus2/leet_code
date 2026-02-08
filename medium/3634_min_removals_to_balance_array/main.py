# You are given an integer array nums and an integer k.

# An array is considered balanced if the value of its maximum element is at most k times the minimum element.

# You may remove any number of elements from nums​​​​​​​ without making it empty.

# Return the minimum number of elements to remove so that the remaining array is balanced.

# Note: An array of size 1 is considered balanced as its maximum and minimum are equal, and the condition always holds true.

from typing import List

class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        # We want that max(nums) <= k * min(nums)
        if len(nums) == 1:
            return 0
        
        nums=sorted(nums)

        i = 0
        j = 0
        while j < len(nums):
            # Update right
            if nums[j] <= k * nums[i]:
                j += 1
            else:
                i+=1
                j+=1

        return len(nums) - (j-i)
    