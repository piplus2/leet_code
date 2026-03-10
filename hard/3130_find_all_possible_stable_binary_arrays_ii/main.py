class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:

        MOD = 1_000_000_007

        dp = [[[0, 0] for _ in range(one + 1)] for _ in range(zero + 1)]

        for i in range(zero + 1):
            for j in range(one + 1):
                if i == 0 and j == 0:
                    continue

                if i > 0:
                    if i == 1:
                        dp[i][j][0] = 1 if j == 0 else dp[i - 1][j][1]
                    else:
                        res = dp[i - 1][j][0] + dp[i - 1][j][1]
                        if i > limit:
                            if i == limit + 1 and j == 0:
                                res -= 1
                            else:
                                # When we overflow the limit, we need to subtract
                                # the number of 
                                res -= dp[i - limit - 1][j][1]
                        dp[i][j][0] = res % MOD

                if j > 0:
                    if j == 1:
                        dp[i][j][1] = 1 if i == 0 else dp[i][j - 1][0]
                    else:
                        res = dp[i][j - 1][0] + dp[i][j - 1][1]
                        if j > limit:
                            if j == limit + 1 and i == 0:
                                res -= 1
                            else:
                                res -= dp[i][j - limit - 1][0]
                        dp[i][j][1] = res % MOD

        return (dp[zero][one][0] + dp[zero][one][1]) % MOD


if __name__ == "__main__":

    zero = 4
    one = 5
    limit = 3

    sol = Solution()
    sol.numberOfStableArrays(zero, one, limit)
