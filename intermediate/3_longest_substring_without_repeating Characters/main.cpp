/*
Given a string s, find the length of the longest substring without duplicate characters.
*/

#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int seen[256];
        for (int i = 0; i < 256; ++i) seen[i] = -1;
        
        int n = s.length();
        int left = 0;
        int max_length = 0;

        for (int right = 0; right < n; ++right)
        {
            unsigned char curr = (int)s[right];
            
            if (seen[curr] >= left)
            {
                int curr_win = right - left;
                if (curr_win > max_length) max_length = curr_win;
                left = seen[curr] + 1;
            }
            
            seen[curr] = right;
        }

        int final_win = n - left;
        if (final_win > max_length) max_length = final_win;

        return max_length;
    }
};