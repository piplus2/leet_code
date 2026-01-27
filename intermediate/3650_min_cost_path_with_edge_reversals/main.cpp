/*
You are given a directed, weighted graph with n nodes labeled from 0 to n - 1, and an array edges where edges[i] = [ui, vi, wi] represents a directed edge from node ui to node vi with cost wi.

Each node ui has a switch that can be used at most once: when you arrive at ui and have not yet used its switch, you may activate it on one of its incoming edges vi → ui reverse that edge to ui → vi and immediately traverse it.

The reversal is only valid for that single move, and using a reversed edge costs 2 * wi.

Return the minimum total cost to travel from node 0 to node n - 1. If it is not possible, return -1.
*/
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class Solution
{
public:
    int minCost(int n, vector<vector<int>> &edges)
    {
        struct Edge
        {
            int to, weight, next;
        };

        int m = edges.size();
        int edge_count = 0;
        vector<int> head(n, -1);
        vector<Edge> e(2 * m);

        auto add_edge = [&](int u, int v, int w)
        {
            e[edge_count] = {v, w, head[u]};
            head[u] = edge_count++;
        };

        // make adj and rev_adj
        for (const auto &edge : edges)
        {
            add_edge(edge[0], edge[1], edge[2]);
            add_edge(edge[1], edge[0], 2 * edge[2]);
        }

        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        vector<long long> dist(n, 1e18);
        vector<char> visited(n, 0);

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty())
        {
            auto [cost, u] = pq.top();
            pq.pop();

            for (int i = head[u]; i != -1; i = e[i].next)
            {
                int v = e[i].to;
                int w = e[i].weight;

                if (visited[v])
                    continue;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[n - 1] >= 1e18)
            return -1;

        return (int)dist[n - 1];
    }
};

int main()
{

    vector<vector<int>> edges = {
        {2, 1, 1},
        {1, 0, 1},
        {2, 0, 16}};

    Solution sol;
    int minCost = sol.minCost(3, edges);
}