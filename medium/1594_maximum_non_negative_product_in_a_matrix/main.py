from typing import List


class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:

        m = len(grid)
        n = len(grid[0])

        dp_min = [1] * n
        dp_max = [1] * n
        dp_min[0] = grid[0][0]
        dp_max[0] = grid[0][0]

        for i in range(1, n):
            dp_min[i] = dp_max[i - 1] * grid[0][i]
            dp_max[i] = dp_min[i]

        for i in range(1, m):
            # j = 0
            top_m = dp_min[0] * grid[i][0]
            top_M = dp_max[0] * grid[i][0]
            if top_m < top_M:
                dp_min[0] = top_m
                dp_max[0] = top_M
            else:
                dp_min[0] = top_M
                dp_max[0] = top_m

            for j in range(1, n):
                top_m = dp_min[j] * grid[i][j]
                top_M = dp_max[j] * grid[i][j]
                left_m = dp_min[j - 1] * grid[i][j]
                left_M = dp_max[j - 1] * grid[i][j]
                dp_min[j] = min([top_m, top_M, left_m, left_M])
                dp_max[j] = max([top_m, top_M, left_m, left_M])

        return dp_max[-1] % (10 ** 9 + 7) if dp_max[-1] >= 0 else -1


if __name__ == "__main__":
    grid = [
        [2, 1, 3, 0, -3, 3, -4, 4, 0, -4],
        [-4, -3, 2, 2, 3, -3, 1, -1, 1, -2],
        [-2, 0, -4, 2, 4, -3, -4, -1, 3, 4],
        [-1, 0, 1, 0, -3, 3, -2, -3, 1, 0],
        [0, -1, -2, 0, -3, -4, 0, 3, -2, -2],
        [-4, -2, 0, -1, 0, -3, 0, 4, 0, -3],
        [-3, -4, 2, 1, 0, -4, 2, -4, -1, -3],
        [3, -2, 0, -4, 1, 0, 1, -3, -1, -1],
        [3, -4, 0, 2, 0, -2, 2, -4, -2, 4],
        [0, 4, 0, -3, -4, 3, 3, -1, -2, -2],
    ]

    sol = Solution()
    print(sol.maxProductPath(grid))
