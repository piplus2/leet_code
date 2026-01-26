/*
Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements.

Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows

a, b are from arr
a < b
b - a equals to the minimum absolute difference of any two elements in arr
*/

#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

class Solution
{
public:
    vector<vector<int>> minimumAbsDifference(vector<int> &arr)
    {
        int n = arr.size();

        sort(arr.begin(), arr.end());

        vector<vector<int>> ans;
        int minDiff = INT_MAX;

        for (size_t i = 0; i < n - 1; ++i)
        {
            int curr = arr[i + 1] - arr[i];
            if (curr < minDiff)
            {
                minDiff = curr;
                ans.clear();
                ans.push_back({arr[i], arr[i + 1]});
            }
            else if (curr == minDiff)
            {
                ans.push_back({arr[i], arr[i + 1]});
            }
        }
        return ans;
    }
};