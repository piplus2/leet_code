/*
You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith student. You are also given an integer k.

Pick the scores of any k students from the array so that the difference between the highest and the lowest of the k scores is minimized.

Return the minimum possible difference.
*/

#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minimumDifference(vector<int> &nums, int k)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1 && k == 1)
            return 0;
        if (k > n)
            return 0;

        sort(nums.begin(), nums.end());
        int min_diff = INT_MAX;
        for (size_t i = 0; i <= n - k; ++i)
        {
            int curr_diff = nums[i + k - 1] - nums[i];
            if (curr_diff < min_diff)
                min_diff = curr_diff;
        }
        return min_diff;
    }
};

int main()
{
    vector<int> nums = {9,4,1,7};

    Solution sol;
    int min_diff = sol.minimumDifference(nums, 2);

    return 0;
}