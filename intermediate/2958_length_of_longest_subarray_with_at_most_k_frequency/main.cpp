#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {

        if (nums.size() == 1) return nums.size();
        if (k >= nums.size()) return nums.size();
        
        unordered_map<int, int> freq;
        
        // using sliding window
        int n = nums.size();
        int curr_max_freq = 0;
        int left = 0;  // first element of the window
        int max_len = 0;

        for (int right = 0; right < n; ++right) {
            freq[nums[right]]++;  // we are seeing this number
            if (freq[nums[right]] > curr_max_freq) {
                curr_max_freq = freq[nums[right]];
            }

            if (curr_max_freq > k) {
                max_len = max(max_len, right - left);
            }


            while (curr_max_freq > k) {
                if (curr_max_freq == freq[nums[left]]) {
                    curr_max_freq--;
                }
                freq[nums[left]]--;

                // here we contract left until we go down with the current_max_freq
                left++;
            }

            // if (curr_max_freq > k) {
            //     max_len = max(max_len, right - left);
            //     freq[nums[left]]--;
            //     curr_max_freq--;
            //     left = right+1;
            // }

        }

        return max(max_len, n - left);

    }
};


int main()
{
    vector<int> nums;
    int k;

    string str_nums, str_k;
    cin >> str_nums;
    cin >> str_k;

    stringstream ss(str_nums);

    k = stoi(str_k);

    string c;
    char del = ',';

    while (getline(ss, c, del)) {
        nums.push_back(stoi(c));
    }

    Solution sol;
    int max_len = sol.maxSubarrayLength(nums, k);
    cout << max_len << endl;
}