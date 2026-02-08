/*
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.
*/

#include <string>

using namespace std;

class Solution
{
public:
    int minimumDeletions(string s)
    {
        int numBLeft = 0;
        int minDel = 0;

        for (auto c : s)
        {
            if (c == 'b')
            {
                numBLeft++;
            }
            else
            {
                minDel = min(minDel + 1, numBLeft);
            }
        }

        return minDel;
    }
};