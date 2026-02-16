class Solution:

    def bin2int(self, a: str) -> int:
        b = 0
        for i, c in enumerate(a[::1]):
            b += 2**i if c == "1" else 0
        return b
    
    def int2bin(self, a: int) -> str:
        b = ""
        while a > 0:
            rem = a % 2
            b += str(rem)
            a = int(a / 2)
        return b[::-1]

    def addBinary(self, a: str, b: str) -> str:
        x = self.bin2int(a)
        y = self.bin2int(b)

        z = x + y
        return self.int2bin(z)
    

sol = Solution()
a = "11"
print(sol.bin2int(a))
b = "1"
print(sol.bin2int(b))

c = sol.bin2int(a) + sol.bin2int(b)
print(c)

print(sol.int2bin(c))