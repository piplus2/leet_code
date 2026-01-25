/*
We consider the binary sequence of ans and ans + 1, made of n binary digits.

If we have a block of 1's, and we add a 1 to the least significant
position we have:

01111...1 + 00000...1 = 10000...0 (n+1 elements)

Adding 1 to the block transforms all 1 bits to 0 with the extra bit 1.
If we do the OR of the first term and the sum we have:

10000...0 v 01111...1 = 11111...1 (n+1 elements)

a sequence of n+1 1's.

Thus the OR operation on ans and ans+1 corresponds to getting a block
of n+1 1's if we had a block of n 1's in ans.
Inverting this reasoning, we can get ans by looking at the longest block of 1's
from the least significant bit. By setting the most significant bit of this
block to 0, we perform the inverse of the operation seen above.
This corresponds to the largest value such that OR(ans, and + 1) = nums[i].
*/

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