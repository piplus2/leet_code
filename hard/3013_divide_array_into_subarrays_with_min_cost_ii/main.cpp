/*
You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.

The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.

Return the minimum possible sum of the cost of these subarrays.
*/

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution
{
private:
    void add(int x, multiset<int> &set1, multiset<int> &set2, long long &cost, int L)
    {
        if (L <= 0)
            return;

        if (set1.size() < L)
        {
            set1.insert(x);
            cost += x;
        }
        else if (x < *set1.rbegin())
        {
            set1.insert(x);
            cost += x;
            auto it = prev(set1.end());
            cost -= *it;
            set2.insert(*it);
            set1.erase(it);
        }
        else
        {
            set2.insert(x);
        }
    }

    void
    remove(int x, multiset<int> &set1, multiset<int> &set2, long long &cost, int L)
    {
        if (L <= 0)
            return;

        auto it = set1.find(x);
        if (it != set1.end())
        {
            cost -= x;
            set1.erase(it);
            if (!set2.empty())
            {
                auto it2 = set2.begin();
                cost += *it2;
                set1.insert(*it2);
                set2.erase(it2);
            }
        }
        else
        {
            auto it2 = set2.find(x);
            if (it2 != set2.end())
                set2.erase(it2);
        }
    }

public:
    long long minimumCost(vector<int> &nums, int k, int dist)
    {
        int n = nums.size();
        int m = k - 1;
        long long cost_0 = nums[0];

        multiset<int> left_set, right_set;
        long long curr_sum = 0;

        int window_size = min(n - 1, dist + 1);
        vector<int> window(nums.begin() + 1, nums.begin() + 1 + window_size);
        nth_element(window.begin(), window.begin() + m, window.end());
        for (int i = 0; i < window.size(); ++i)
        {
            if (i < m)
            {
                left_set.insert(window[i]);
                curr_sum += window[i];
            }
            else
            {
                right_set.insert(window[i]);
            }
        }

        long long min_total_cost = (long long)cost_0 + curr_sum;

        for (int i = 1, k = dist + 2; k < n; ++k, ++i)
        {
            remove(nums[i], left_set, right_set, curr_sum, m);
            add(nums[k], left_set, right_set, curr_sum, m);
            min_total_cost = min(min_total_cost, (long long)nums[0] + curr_sum);
        }

        return min_total_cost;
    }
};