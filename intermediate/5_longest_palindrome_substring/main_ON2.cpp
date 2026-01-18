/*
Given a string s, return the longest palindromic substring in s.
*/

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
public:
    int expandAroundCenter(string s, int left, int right)
    {
        if (right >= s.length())
            return 0;
        while (left >= 0 && right < s.length() && s[left] == s[right])
        {
            left--;
            right++;
        }
        return right - left - 1;
    }

    string longestPalindrome(string s)
    {
        if (s.length() == 1)
            return s;

        int start = 0;
        int max_len = 0;

        // expand around the current char
        for (int i = 0; i < s.length(); ++i)
        {
            int len1 = expandAroundCenter(s, i, i);
            int len2 = expandAroundCenter(s, i, i + 1);
            int len = max(len1, len2);

            if (len > max_len) {
                max_len = len;
                start = i - (len - 1) / 2;
            }
        }
        return s.substr(start, max_len);
    }
};

int main()
{
    string input;
    cin >> input;

    Solution sol;
    string out = sol.longestPalindrome(input);
    cout << out << endl;
}