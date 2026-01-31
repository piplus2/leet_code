/*
You are given an array of characters letters that is sorted in non-decreasing order, and a character target. There are at least two different characters in letters.

Return the smallest character in letters that is lexicographically greater than target. If such a character does not exist, return the first character in letters.
*/

#include <vector>

using namespace std;

class Solution
{
public:
    char nextGreatestLetter(vector<char> &letters, char target)
    {
        int n = letters.size();
        int L = 0;
        int R = n - 1;
        int t = (int)target;
        int res = letters[0];

        while (L <= R)
        {
            int m = L + (int)((R - L) / 2);
            int c = (int)letters[m];
            if (c > t)
            {
                res = letters[m];
                R = m - 1;
            }
            else
            {
                L = m + 1;
            }
        }
        return res;
    }
};