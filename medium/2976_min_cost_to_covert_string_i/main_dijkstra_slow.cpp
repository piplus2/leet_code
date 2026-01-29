#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Graph
{
    unordered_map<char, vector<pair<char, int>>> edges;
    unordered_set<char> nodes;
};

class Solution
{
private:
    Graph graphConvert(const vector<char> &o, const vector<char> &c, const vector<int> &d)
    {
        int n = o.size();
        unordered_set<char> nodes;
        unordered_map<char, vector<pair<char, int>>> edges;
        for (int i = 0; i < n; ++i)
        {
            edges[o[i]].push_back(make_pair(c[i], d[i]));
            nodes.insert(o[i]);
            nodes.insert(c[i]);
        }

        return {edges, nodes};
    }

    long long minCostConvertChar(Graph &graph, char start, char end)
    {
        // do Dijkstra's on the bipartite graph

        int cost = 0;

        priority_queue<pair<long long, char>, vector<pair<long long, char>>, greater<pair<long long, char>>> pq;
        unordered_map<char, long long> dist;
        for (const auto &node : graph.nodes)
            dist[node] = 1e18;
        dist[start] = 0LL;

        pq.push(make_pair(0, start));
        while (!pq.empty())
        {

            auto [currCost, currChar] = pq.top();
            pq.pop();

            if (currChar == end)
            {
                break;
            }

            if (currCost > dist[currChar])
                continue;

            for (const auto &[neighChar, neighCost] : graph.edges[currChar])
            {
                long long testDist = dist[currChar] + (long long)neighCost;
                if (dist[neighChar] > testDist)
                {
                    dist[neighChar] = testDist;
                    pq.push(make_pair(dist[neighChar], neighChar));
                }
            }
        }

        if (dist.find(end) == dist.end())
            return 1e18;
        return dist[end];
    }

public:
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {
        int m = source.length();
        long long totCost = 0;

        // make the conversion graph
        Graph g = graphConvert(original, changed, cost);

        for (int i = 0; i < m; ++i)
        {
            if (source[i] == target[i])
            {
                continue;
            }
            long long minCost = minCostConvertChar(g, source[i], target[i]);
            if (minCost >= 1e18)
                return -1;

            totCost += minCost;
        }
        return totCost;
    }
};