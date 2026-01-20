#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans(nums.size(), -1);
        for (size_t i = 0; i < nums.size(); ++i) {
            int x = nums[i];
            // If it's even, there's no solution
            if (x % 2 == 0) {
                ans[i] = -1;
                continue;
            }
            // Find the most significant bit of the 1's block.
            int subtr = 1;
            while (x > 0 && (x & 1) == 1) {
                subtr <<= 1;
                x >>=1;
            }
            subtr >>= 1;
            ans[i] = nums[i] - subtr;
        }
        return ans;
    }
};


int main() {
    vector<int> nums;

    string line;
    getline(cin, line);
    istringstream iss(line);
    string x;
    while (getline(iss, x, ','))
    {
        nums.push_back(stoi(x));
    }

    Solution sol;
}