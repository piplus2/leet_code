import math
from typing import List


class Solution:
    def constructProductMatrix(self, grid: List[List[int]]) -> List[List[int]]:

        # construct the product matrix with all elements
        n = len(grid)
        m = len(grid[0])

        grid_vals = [val for row in grid for val in row]
        length = n * m
        prod_mat = [1] * length

        current_prod = 1
        for i in range(length):
            prod_mat[i] = current_prod
            current_prod = (current_prod * grid_vals[i]) % 12345

        current_prod = 1
        for i in range(length - 1, -1, -1):
            prod_mat[i] = (prod_mat[i] * current_prod) % 12345
            current_prod = (current_prod * grid_vals[i]) % 12345

        return [prod_mat[i * m : (i + 1) * m] for i in range(n)]


if __name__ == "__main__":
    grid = [
        [8, 18],
        [24, 20],
        [9, 5],
        [26, 26],
        [19, 19],
        [20, 1],
        [20, 23],
        [15, 19],
        [24, 14],
        [12, 15],
        [22, 3],
        [22, 11],
        [9, 25],
    ]

    sol = Solution()
    print(sol.constructProductMatrix(grid))
