/*
You are given the two integers, n and m and two integer arrays, hBars and vBars. The grid has n + 2 horizontal and m + 2 vertical bars, creating 1 x 1 unit cells. The bars are indexed starting from 1.

You can remove some of the bars in hBars from horizontal bars and some of the bars in vBars from vertical bars. Note that other bars are fixed and cannot be removed.

Return an integer denoting the maximum area of a square-shaped hole in the grid, after removing some bars (possibly none).
*/

#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
private:
    int maxLengthConsecutive(vector<int> &bars, const int max_val)
    {
        if (bars.empty())
            return 0;

        sort(bars.begin(), bars.end());

        if (bars.size() >= max_val)
        {
            bars.erase(unique(bars.begin(), bars.end()), bars.end());
        };

        if (bars.size() == max_val)
            return max_val;

        int max_k = 1;
        int current_k = 1;

        // determine the max number of consecutive values along h
        for (size_t i = 1; i < bars.size(); ++i)
        {
            if (bars[i] == bars[i - 1] + 1)
            {
                // consecutive
                current_k++;
            }
            else if (bars[i] == bars[i - 1])
            {
                // skip duplicated
            }
            else
            {
                // new sequence
                current_k = 1;
            }
            max_k = max(max_k, current_k);
        }
        return max_k;
    }

public:
    int maximizeSquareHoleArea(int n, int m, vector<int> &hBars, vector<int> &vBars)
    {

        // determine the max number of consecutive values along h
        int kh = maxLengthConsecutive(hBars, n);
        int kv = maxLengthConsecutive(vBars, m);

        // determine the max length of square side
        int L = min(kv + 1, kh + 1);
        return L * L;
    }
};