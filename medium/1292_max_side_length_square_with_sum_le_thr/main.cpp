/*
Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
*/

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Solution
{
public:
    int maxSideLength(vector<vector<int>> &mat, int threshold)
    {

        int m = mat.size();
        int n = mat[0].size();
        bool isGood;

        if (m == 0 || n == 0)
            return 0;

        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                prefixSum[i][j] = mat[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }

        int max_len = 0;
        for (int i = 0; i <= m; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                if (i > max_len && j > max_len) {
                    int k = max_len + 1;
                    int currSum = prefixSum[i][j] - prefixSum[i-k][j] - prefixSum[i][j-k] + prefixSum[i-k][j-k];
                    if (currSum <= threshold)
                        max_len++;
                }
            }
        }
        
        return max_len;
    }
};

int main()
{

    // string ks;
    // cin >> ks;
    // int k = stoi(ks);

    string line;
    vector<vector<int>> mat;
    while (getline(cin, line))
    {
        istringstream iss(line);
        string x;
        vector<int> row;
        while (getline(iss, x, ','))
        {
            row.push_back(stoi(x));
        }
        mat.push_back(row);
    }

    Solution sol;
    int maxLength = sol.maxSideLength(mat, 40184);
}