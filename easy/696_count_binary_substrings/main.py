class Solution:
    def countBinarySubstrings(self, s: str) -> int:
        ans = 0
        prev_group_len = 0
        curr_group_len = 1
        
        for i in range(1, len(s)):
            if s[i] == s[i-1]:
                curr_group_len += 1
            else:
                ans += min(prev_group_len, curr_group_len)
                prev_group_len = curr_group_len
                curr_group_len = 1
        
        ans += min(prev_group_len, curr_group_len)
        
        return ans

s = "1010001"
sol = Solution()
sol.countBinarySubstrings(s)