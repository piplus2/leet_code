class Solution:
    def convert(self, s: str, numRows: int) -> str:
        
        n = len(s)
        ans = ""
        max_delta = 2 * numRows - 2

        for row in range(numRows):
            curr_i = row
            ans += s[curr_i]
            delta_1 = max_delta - 2 * row
            delta_2 = max_delta - delta_1
            while curr_i < n:
                if delta_1 > 0:
                    curr_i += delta_1
                    if curr_i > n-1:
                        break
                    ans += s[curr_i]
                if delta_2 > 0:
                    curr_i += delta_2
                    if curr_i > n-1:
                        break
                    ans += s[curr_i]
            
        return ans
    


a = "PAYPALISHIRING"
sol = Solution()
print(sol.convert(a, 4))