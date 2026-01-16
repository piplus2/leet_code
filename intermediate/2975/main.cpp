/*
There is a large (m - 1) x (n - 1) rectangular field with corners at (1, 1) and (m, n) containing some horizontal and vertical fences given in arrays hFences and vFences respectively.

Horizontal fences are from the coordinates (hFences[i], 1) to (hFences[i], n) and vertical fences are from the coordinates (1, vFences[i]) to (m, vFences[i]).

Return the maximum area of a square field that can be formed by removing some fences (possibly none) or -1 if it is impossible to make a square field.

Since the answer may be large, return it modulo 109 + 7.

Note: The field is surrounded by two horizontal fences from the coordinates (1, 1) to (1, n) and (m, 1) to (m, n) and two vertical fences from the coordinates (1, 1) to (m, 1) and (1, n) to (m, n). These fences cannot be removed.
*/

#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {

        // add borders
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        hFences.erase( unique( hFences.begin(), hFences.end() ), hFences.end() );
        vFences.erase( unique( vFences.begin(), vFences.end() ), vFences.end() );

        vector<int>* shortVec;
        vector<int>* longVec;

        if (hFences.size() > vFences.size()) {
            shortVec = &vFences;
            longVec = &hFences;
        } else {
            shortVec = &hFences;
            longVec = &vFences;
        }

        int maxPotentialDist = (*longVec).back() - (*longVec).front();

        unordered_set<int> refDists;
        for (size_t i = 0; i < (*shortVec).size(); ++i)
        {
            for (size_t j = i+1; j < (*shortVec).size(); ++j)
            {
                int dist = (*shortVec)[j] - (*shortVec)[i];
                if (dist <= maxPotentialDist)
                    refDists.insert(dist);
            }
        }

        // greed search

        // search in the other array
        int curr_max_L = 0;
        for (size_t i = 0; i < (*longVec).size(); ++i) {
            for (size_t j = (*longVec).size() - 1; j > i; --j) {
                int dist = (*longVec)[j] - (*longVec)[i];
                if (dist <= curr_max_L) {
                    // worse potential solution - just skip
                    break;
                } else if (refDists.find(dist) != refDists.end()) {
                    // found - good candidate
                    curr_max_L = dist;
                }
            }
        }

        long long mod = 1e9 + 7;
        return (curr_max_L == 0) ? -1 : (1LL * curr_max_L * curr_max_L) % mod;
    }
};