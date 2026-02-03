/*
You are given an integer array nums of length n.

An array is trionic if there exist indices 0 < p < q < n − 1 such that:

nums[0...p] is strictly increasing,
nums[p...q] is strictly decreasing,
nums[q...n − 1] is strictly increasing.
Return true if nums is trionic, otherwise return false.
*/

#include <vector>

using namespace std;

class Solution
{
public:
    bool isTrionic(vector<int> &nums)
    {
        int n = nums.size();

        // 1st condition
        int p = 0;
        bool first = false;
        while (p < n - 2 && nums[p + 1] > nums[p])
        {
            p++;
            first = true;
        }
        if (!first)
            return first;

        // 2nd condition
        int q = p;
        bool second = false;
        while (q < n - 2 && nums[q + 1] < nums[q])
        {
            q++;
            second = true;
        }
        if (!second)
            return second;

        // 3rd condition
        bool third = false;
        // finally check that the last elements are strictly increasing
        for (int i = q; i < n - 1; ++i)
        {
            if (nums[i + 1] <= nums[i])
                return false;
            third = true;
        }
        return third;
    }
};