/*
A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.

Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.
*/

#include <vector>

using namespace std;

class Solution
{
public:
    int largestMagicSquare(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> rowSum(m + 1, vector<int>(n + 2, 0));
        vector<vector<int>> colSum(m + 1, vector<int>(n + 2, 0));
        vector<vector<int>> diag1(m + 1, vector<int>(n + 2, 0));
        vector<vector<int>> diag2(m + 1, vector<int>(n + 2, 0));

        for (int r = 0; r < m; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                int curr = grid[r][c];
                int R = r + 1;
                int C = c + 1;

                rowSum[R][C] = rowSum[R][C - 1] + curr;
                colSum[R][C] = colSum[R - 1][C] + curr;
                diag1[R][C] = diag1[R - 1][C - 1] + curr;
                diag2[R][C] = diag2[R - 1][C + 1] + curr;
            }
        }

        int k = min(m, n);
        bool isMagic;
        while (k > 1)
        {
            // (i, j) top-left corner of the square
            for (int i = 0; i <= m - k; ++i)
            {
                int R = i + 1;
                for (int j = 0; j <= n - k; ++j)
                {
                    isMagic = true;

                    int C = j + 1;
                    int targetSum = rowSum[R][C + k - 1] - rowSum[R][C - 1];
                    // check the square of side k is magic
                    for (int r = 0; r < k; ++r)
                    {
                        int currSum = rowSum[R + r][C + k - 1] - rowSum[R + r][C - 1];
                        if (currSum != targetSum)
                        {
                            isMagic = false;
                            break;
                        }
                    }
                    if (isMagic)
                    {
                        for (int c = 0; c < k; ++c)
                        {
                            int currSum = colSum[R + k - 1][C + c] - colSum[R - 1][C + c];
                            if (currSum != targetSum)
                            {
                                isMagic = false;
                                break;
                            }
                        }
                    }

                    // check diagonals
                    if (isMagic)
                    {
                        int currSum = diag1[R + k - 1][C + k - 1] - diag1[R - 1][C - 1];
                        if (currSum != targetSum)
                            isMagic = false;
                    }

                    if (isMagic)
                    {
                        int currSum = diag2[R + k - 1][C] - diag2[R - 1][C + k];
                        if (currSum != targetSum)
                            isMagic = false;
                    }

                    if (isMagic)
                        return k;
                }
            }
            k--;
        }
        return 1;
    }
};