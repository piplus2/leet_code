class Solution:
    def int2bits(self, n: int) -> str:
        ans = ""
        while n > 0:
            rem = n % 2
            n = n // 2
            ans += str(rem)
        return ans[::-1]

    def hasAlternatingBits(self, n: int) -> bool:
        bits = self.int2bits(n)
        curr = bits[0]
        for i in range(1, len(bits)):
            if bits[i] == curr:
                return False
            curr = bits[i]
        return True