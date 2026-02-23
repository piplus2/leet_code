"""
The solution is based on this approach:

we recursively identify all special substrings, which start with '1' and
end with '0' (to satisfy the second property), remove the shell: the first
'1' and last '0' and determine the split point (index i). The two special
substrings are then returned ordered lexicographically.

E.g.:

input: 11011000

the string cannot be split, the only special substring is the string itself,
we remove the shell:

res: 1 + 101100 + 0

and find the split (#0 = #1 and #1 >= #0 in all prefixes)

res: 101100 = 10 + 1100

sort lexicographically:

res: 110010

and join with the shell:

res: 1 + 110010 + 0 = 1110100
"""


class Solution:
    def makeLargestSpecial(self, s: str) -> str:
        if not s: return ""
        count = 0
        i = 0
        res = []
        for j, char in enumerate(s):
            count += 1 if char == '1' else -1
            if count == 0:
                sub = s[i + 1:j] # Rimuoviamo il guscio
                res.append('1' + self.makeLargestSpecial(sub) + '0')
                i = j + 1
        
        res.sort(reverse=True)
        return "".join(res)
    

def main():
    s = "11011000"
    sol = Solution()
    sorted_s = sol.makeLargestSpecial(s)
    print(sorted_s)

if __name__ == "__main__":
    main()