from typing import List


def prefix_sum_matrix(grid):
    n = len(grid)
    m = len(grid[0])

    prefix = [[0] * m for _ in range(n)]

    for i in range(n):
        for j in range(m):
            prefix[i][j] = grid[i][j]

            if i > 0:
                prefix[i][j] += prefix[i - 1][j]

            if j > 0:
                prefix[i][j] += prefix[i][j - 1]

            if i > 0 and j > 0:
                prefix[i][j] -= prefix[i - 1][j - 1]
    return prefix


class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:

        n = len(grid)
        m = len(grid[0])

        prefix_mat = prefix_sum_matrix(grid)

        min_r = {}
        max_r = {}
        min_c = {}
        max_c = {}
        for i in range(n):
            for j in range(m):
                value = grid[i][j]
                if value not in min_r:
                    min_r[value] = i
                max_r[value] = i

                if value not in min_c:
                    min_c[value] = j
                else:
                    if j < min_c[value]:
                        min_c[value] = j
                if value not in max_c:
                    max_c[value] = j
                else:
                    if j > max_c[value]:
                        max_c[value] = j

        for row_cut in range(n - 1):
            s_up = prefix_mat[row_cut][-1]
            s_down = prefix_mat[-1][-1] - s_up
            diff_val = abs(s_up - s_down)
            if diff_val == 0:
                return True

            if diff_val not in min_r:
                continue

            if s_up > s_down:
                if row_cut == 0 or m == 1:
                    if diff_val == grid[0][0] or diff_val == grid[row_cut][m - 1]:
                        return True
                else:
                    if min_r[diff_val] <= row_cut:
                        return True
            else:
                if row_cut == n - 2 or m == 1:
                    if diff_val == grid[row_cut + 1][0] or diff_val == grid[n - 1][m - 1]:
                        return True
                else:
                    if max_r[diff_val] > row_cut:
                        return True

        for col_cut in range(m - 1):
            s_left = prefix_mat[-1][col_cut]
            s_right = prefix_mat[-1][-1] - s_left
            diff_val = abs(s_left - s_right)
            if diff_val == 0:
                return True

            if diff_val not in min_c:
                continue

            if s_left > s_right:
                if col_cut == 0 or n == 1:
                    if diff_val == grid[0][0] or diff_val == grid[n - 1][col_cut]:
                        return True
                else:
                    if min_c[diff_val] <= col_cut:
                        return True
            else:
                if col_cut == m - 2 or n == 1:
                    if diff_val == grid[0][col_cut + 1] or diff_val == grid[n - 1][m - 1]:
                        return True
                else:
                    if max_c[diff_val] > col_cut:
                        return True

        return False


if __name__ == "__main__":

    grid = [[100000], [86218], [100000]]
    sol = Solution()
    print(sol.canPartitionGrid(grid))
