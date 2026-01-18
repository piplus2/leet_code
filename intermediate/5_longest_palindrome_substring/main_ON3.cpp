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
    string longestPalindrome(string s)
    {
        if (s.length() == 1) return s;

        string longest_palindrome = "";
        int max_len = 0;
        int n = s.length();
        int end_idx;
        bool is_palindrome;

        for (int i = 0; i < n; ++i)
        {
            is_palindrome = false;
            char curr = s[i];
            for (int j = n - 1; j > i; --j)
            {
                if (curr == s[j])
                {
                    // candidate palindrome s[i + offset] = s[j]
                    is_palindrome = true;
                    // check the consecutive to see it's truly palindrome
                    for (int k = 1; k < (j - i + 1) / 2; ++k)
                    {
                        if (s[i + k] != s[j - k])
                        {
                            is_palindrome = false;
                            break;
                        }
                    }
                    // if it's truly palindrome exit
                    if (is_palindrome)
                    {
                        end_idx = j;
                        break;
                    }
                }
                else
                {
                    is_palindrome = false;
                }
            }
            if (is_palindrome)
            {
                if (end_idx - i + 1 > max_len)
                {
                    max_len = end_idx - i + 1;
                    longest_palindrome = s.substr(i, end_idx - i + 1);
                }
            }
        }

        if (max_len == 0) longest_palindrome.push_back(s[0]);
        return longest_palindrome;
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