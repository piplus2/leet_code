/*
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.
*/

#include <vector>
#include <algorithm>
#include <ios>
#include <iostream>

using namespace std;

struct FastIO
{
    FastIO()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
    }
};

FastIO startup;

class Solution
{
public:
    int longestOnes(vector<int> &nums, int k)
    {
        int n = nums.size();
        int max_len = 0;
        int left = 0;
        int seen_zeros = 0;

        for (int right = 0; right < n; ++right)
        {
            if (nums[right] == 0)
                seen_zeros++;

            while (seen_zeros > k)
            {
                if (nums[left] == 0)
                {
                    seen_zeros--;
                }
                left++;
            }
            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};