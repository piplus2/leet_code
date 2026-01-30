/*
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].

You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:

The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

class Solution
{
public:
    long long minimumCost(string source, string target, vector<string> &original, vector<string> &changed, vector<int> &cost)
    {
        unordered_map<string, int> stringToId;
        int idCount = 0;
        auto getID = [&](string &s)
        {
            if (stringToId.find(s) == stringToId.end())
            {
                stringToId[s] = idCount++;
            }
            return stringToId[s];
        };

        for (int i = 0; i < original.size(); ++i)
        {
            getID(original[i]);
            getID(changed[i]);
        }
        int M = idCount;

        vector<vector<long long>> FWdist(M, vector<long long>(M, 1e18));
        for (int i = 0; i < M; ++i)
            FWdist[i][i] = 0;

        for (int k = 0; k < original.size(); ++k)
        {
            int u = stringToId[original[k]];
            int v = stringToId[changed[k]];
            FWdist[u][v] = min(FWdist[u][v], (long long)cost[k]);
        }

        for (int k = 0; k < M; ++k)
        {
            for (int i = 0; i < M; ++i)
            {
                for (int j = 0; j < M; ++j)
                {
                    if (FWdist[i][k] != 1e18 && FWdist[k][j] != 1e18)
                        FWdist[i][j] = min(FWdist[i][j], FWdist[i][k] + FWdist[k][j]);
                }
            }
        }

        int n = source.size();

        set<int> Lset;
        for (const auto &o : original)
            Lset.insert(o.size());
        vector<int> L(Lset.begin(), Lset.end());

        vector<long long> dp(n + 1, 1e18);
        dp[0] = 0;

        for (int i = 0; i < n; ++i)
        {
            if (dp[i] == 1e18)
                continue;

            if (source[i] == target[i])
                dp[i + 1] = min(dp[i + 1], dp[i]);

            for (int len : L)
            {
                if (i + len <= n)
                {
                    string subS = source.substr(i, len);
                    string subT = target.substr(i, len);

                    if (stringToId.find(subS) != stringToId.end())
                    {
                        if (stringToId.find(subT) != stringToId.end())
                        {
                            long long currCost = FWdist[stringToId[subS]][stringToId[subT]];
                            if (currCost < 1e18)
                                dp[i + len] = min(dp[i + len], dp[i] + currCost);
                        }
                    }
                }
            }
        }

        return (dp[n] >= 1e18) ? -1 : dp[n];
    }
};