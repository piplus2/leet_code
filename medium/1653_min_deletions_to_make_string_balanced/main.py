class Solution:
    def minimumDeletions(self, s: str) -> int:
        min_del = 0
        b_left = 0

        for k in range(len(s)):
            if s[k] == 'b':
                b_left +=1
            else:
                min_del = min(min_del + 1, b_left)

        return min_del