/*
You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.

The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.

Return the minimum possible sum of the cost of these subarrays.
*/

#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <ios>

using namespace std;

// Trucco per velocizzare I/O in C++
auto fast_io = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution
{
public:
    long long minimumCost(vector<int> &nums, int k, int dist)
    {
        int n = nums.size();
        int m = k - 2; // Quanti ne servono nel left_set
        long long cost_0 = nums[0];

        multiset<pair<int, int>> left_set, right_set;
        long long curr_sum = 0;

        // Inizializzazione finestra per i=1
        for (int j = 2; j <= min(n - 1, 1 + dist); ++j)
        {
            right_set.insert({nums[j], j});
        }

        // Popoliamo left_set (Squadra A)
        while (left_set.size() < m && !right_set.empty())
        {
            auto it = right_set.begin();
            curr_sum += it->first;
            left_set.insert(*it);
            right_set.erase(it);
        }

        long long min_total_cost = cost_0 + nums[1] + curr_sum;

        for (int i = 2; i <= n - k + 1; ++i)
        {
            // 1. Rimuoviamo nums[i] che diventa il nuovo perno
            pair<int, int> toRemove = {nums[i], i};
            auto itL = left_set.find(toRemove);
            if (itL != left_set.end())
            {
                curr_sum -= itL->first;
                left_set.erase(itL);
            }
            else
            {
                auto itR = right_set.find(toRemove);
                if (itR != right_set.end())
                    right_set.erase(itR);
            }

            // 2. Aggiungiamo nums[i + dist]
            if (i + dist < n)
            {
                right_set.insert({nums[i + dist], i + dist});
            }

            // 3. Bilanciamento chirurgico
            // Se left_set è rimasto vuoto o ha bisogno di elementi
            while (left_set.size() < m && !right_set.empty())
            {
                auto it = right_set.begin();
                curr_sum += it->first;
                left_set.insert(*it);
                right_set.erase(it);
            }

            // 4. Swap veloce
            if (m > 0 && !right_set.empty())
            {
                auto itL = prev(left_set.end());
                auto itR = right_set.begin();
                if (itL->first > itR->first)
                {
                    curr_sum = curr_sum - itL->first + itR->first;

                    pair<int, int> valL = *itL;
                    pair<int, int> valR = *itR;

                    left_set.erase(itL);
                    right_set.erase(itR);

                    left_set.insert(valR);
                    right_set.insert(valL);
                }
            }

            min_total_cost = min(min_total_cost, cost_0 + nums[i] + curr_sum);
        }

        return min_total_cost;
    }
};