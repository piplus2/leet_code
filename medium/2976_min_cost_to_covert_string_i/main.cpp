/*
You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].

You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.

Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.

Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
*/

#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Solution
{
public:
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {

        long long dist[26][26];
        for (int i = 0; i < 26; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (i == j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = 1e18;
            }
        }

        for (size_t i = 0; i < original.size(); ++i)
            dist[original[i] - 'a'][changed[i] - 'a'] = min(dist[original[i] - 'a'][changed[i] - 'a'], (long long)cost[i]);

        for (int k = 0; k < 26; ++k)
        {
            for (int i = 0; i < 26; ++i)
            {
                for (int j = 0; j < 26; ++j)
                {
                    if (dist[i][k] != 1e18 && dist[k][j] != 1e18)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int m = source.length();
        long long totCost = 0;

        for (int i = 0; i < m; ++i)
        {
            if (source[i] == target[i])
                continue;

            long long minDist = dist[source[i] - 'a'][target[i] - 'a'];
            if (minDist >= 1e18)
                return -1;
            totCost += minDist;
        }

        return totCost;
    }
};

int main()
{

    string source = "abcd";
    string target = "abce";
    vector<char> original = {'a'};
    vector<char> changed = {'e'};
    vector<int> cost = {1000};

    Solution sol;
    int minCost = sol.minimumCost(source, target, original, changed, cost);
}