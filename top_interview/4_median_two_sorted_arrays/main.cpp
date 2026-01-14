/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).
*/

#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;


class Solution {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
        {
            size_t n = nums1.size();
            size_t m = nums2.size();

            if (n > m) return findMedianSortedArrays(nums2, nums1);

            // take the index i from the shortest vector
            // the corresponding index in the other vector
            // is j = (n + m + 1) / 2 - i
            // the condition for the median is that given:
            // A_L = A[i-1], A_R = A[i], B_L = B[j-1], B_R = B[j]
            // A_L <= B_R and B_L <= A_R
            // (the median cuts both arrays consistently)

            int low = 0;
            int high = n;

            while (low <= high) {
                // binary search
                int partA = (low + high) / 2;
                int partB = (n + m + 1) / 2 - partA;

                int ALeft = (partA == 0) ? INT_MIN : nums1[partA - 1];
                int ARight = (partA == n) ? INT_MAX : nums1[partA];
                int BLeft = (partB == 0) ? INT_MIN : nums2[partB - 1];
                int BRight = (partB == m)  ? INT_MAX : nums2[partB];

                if ((ALeft <= BRight) && (BLeft <= ARight)) {
                    // found it
                    if ((m + n) % 2 == 0) {
                        return (max(ALeft, BLeft) + min(ARight, BRight)) / 2.0;
                    } else {
                        return max(ALeft, BLeft);
                    }
                } else if (ALeft > BRight) {
                    high = partA - 1;  // cut too high, look at left
                } else {
                    low = partA + 1;  // cut too low, look at right
                }
            }
            return 0.0;
        }
};


int main()
{
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2};
    Solution sol;
    double median = sol.findMedianSortedArrays(nums1, nums2);
    cout << median << endl;
}