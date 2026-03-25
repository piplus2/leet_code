from typing import List


class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:

        m = len(grid)
        if m == 0:
            return False
        n = len(grid[0])
        if n == 0:
            return False

        # If the total sum of the grid is odd, it's impossible to find a solution
        total_sum = sum(sum(row) for row in grid)
        if total_sum % 2 != 0:
            return False

        # set the target cumulative sum
        target = total_sum // 2

        # We check if we find a cut corresponding to the target cumulative sum
        # If found then return True
        current_row_sum = 0
        for row in grid:
            current_row_sum += sum(row)
            if current_row_sum == target:
                return True
            if current_row_sum > target:
                break

        current_col_sum = 0
        for col in zip(*grid):
            current_col_sum += sum(col)
            if current_col_sum == target:
                return True
            if current_col_sum > target:
                break

        return False


if __name__ == "__main__":
    grid = [[1, 4], [2, 3]]
    sol = Solution()
    print(sol.canPartitionGrid(grid=grid))
