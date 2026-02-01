/*
You are given an array of integers nums of length n.

The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

You need to divide nums into 3 disjoint contiguous subarrays.

Return the minimum possible sum of the cost of these subarrays.
*/

#include <vector>

using namespace std;

class Solution
{
public:
    int minimumCost(vector<int> &nums)
    {

        int n = nums.size();

        int cost1 = nums[0];
        int minCost = 1e9;

        for (int i = 1; i < n - 1; ++i)
        {
            int cost2 = nums[i];
            for (int j = i + 1; j < n; ++j)
            {
                int cost3 = nums[j];
                minCost = min(minCost, cost1 + cost2 + cost3);
            }
        }
        return minCost;
    }
};