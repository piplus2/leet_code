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
        int minDiff = 1e9;
        int t = (int)target;
        for (char c : letters)
        {
            minDiff = ((int)c > t) ? min((int)c - t, minDiff) : minDiff;
        }
        return minDiff == 1e9 ? letters[0] : (char)(minDiff + t);
    }
};