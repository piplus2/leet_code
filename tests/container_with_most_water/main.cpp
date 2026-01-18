/*
A set of vertical bars with given height positioned in discrete x is represented by
an array. Each pair of bars together with the x-axis forms a container.
Find the pair of bars that correspond to the largest area.
Notice that water will fill up to the lowest bar of the pair.
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int largestContainerArea(vector<int> bars)
{
    int n = bars.size();
    int max_area = 0;
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
        int curr_area = (right - left) * min(bars[left], bars[right]);
        if (curr_area > max_area)
            max_area = curr_area;
        if (bars[left] < bars[right])
            left++;
        else
            right--;
    }
    return max_area;
}


int main() {
    
    vector<int> bars;

    string line;
    getline(cin, line);
    istringstream iss(line);
    string x;
    while (getline(iss, x, ','))
    {
        bars.push_back(stoi(x));
    }

    int maxArea = largestContainerArea(bars);

    cout << maxArea << endl;
}