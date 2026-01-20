/*
Given an integer x, return true if x is a palindrome, and false otherwise.
*/


#include <iostream>

using namespace std;

class Solution {
public:

    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }

        if (x < 0) {
            // negative int are not palidrome
            return false;
        }

        int reversed_x = 0;
        int y = x;
        while (y > 0) {
            reversed_x = reversed_x * 10 + y % 10;
            y = (int)y / 10;
        }

        cout << reversed_x << endl;

        return x == reversed_x;
    }
};


int main() {
    int val = 1221;
    Solution sol;
    bool is_pal = sol.isPalindrome(val);
    cout << is_pal << endl;
}