/*
The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.

For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:

Each element of nums is in exactly one pair, and
The maximum pair sum is minimized.
Return the minimized maximum pair sum after optimally pairing up the elements.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minPairSum(vector<int> &nums)
    {
        // use count sort
        int n = nums.size();
        if (n == 2)
            return nums[0] + nums[1];

        vector<int> carr(*max_element(nums.begin(), nums.end()) + 1, 0);
        for (const auto &n : nums)
        {
            carr[n]++;
        }

        int m = carr.size();
        int max_sum = 0;
        int low = 0;
        int hi = m - 1;
        while (low < m && hi >= 0 && low != hi)
        {
            if (carr[low] == 0)
            {
                low++;
                continue;
            }
            if (carr[hi] == 0)
            {
                hi--;
                continue;
            }

            max_sum = max(max_sum, low + hi);

            if (carr[low] < carr[hi])
            {
                carr[hi] -= carr[low];
                carr[low] = 0;
                low++;
            }
            else if (carr[low] > carr[hi])
            {
                carr[low] -= carr[hi];
                carr[hi] = 0;
                hi--;
            }
            else
            {
                carr[low] = 0;
                carr[hi] = 0;
                low++;
                hi--;
            }
        }
        if (low == hi)
        {
            max_sum = max(max_sum, 2 * low);
        }
        return max_sum;
    }
};

int main()
{
    vector<int> nums = {4, 1, 5, 1, 2, 5, 1, 5, 5, 4};
    Solution sol;
    int min_sum = sol.minPairSum(nums);

    return 0;
}