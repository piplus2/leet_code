/*
You are given an integer array nums that represents a circular array. Your task is to create a new array result of the same size, following these rules:

For each index i (where 0 <= i < nums.length), perform the following independent actions:
If nums[i] > 0: Start at index i and move nums[i] steps to the right in the circular array. Set result[i] to the value of the index where you land.
If nums[i] < 0: Start at index i and move abs(nums[i]) steps to the left in the circular array. Set result[i] to the value of the index where you land.
If nums[i] == 0: Set result[i] to nums[i].
Return the new array result.

Note: Since nums is circular, moving past the last element wraps around to the beginning, and moving before the first element wraps back to the end.
*/

#include <vector>
#include <cmath>

using namespace std;

class Solution
{

private:
    void applyRule(const vector<int> &nums, vector<int> &result, int i, int n)
    {
        if (nums[i] == 0)
        {
            result[i] = nums[i];
        }
        else
        {
            int k = (nums[i] + i) % n;
            result[i] = nums[(k < 0) ? k + n : k];
        }
    }

public:
    vector<int> constructTransformedArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> result(n, 0);

        for (int i = 0; i < n; ++i)
        {
            applyRule(nums, result, i, n);
        }
        return result;
    }
};

int main()
{
    vector<int> nums = {3, -2, 1, 1};
    Solution sol;
    vector<int> result = sol.constructTransformedArray(nums);
}