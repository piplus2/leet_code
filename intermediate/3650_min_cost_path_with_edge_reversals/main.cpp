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
        // state = (best_cost, node_id)
        using State = pair<long long, int>;
        long long INF = 1e18;
        priority_queue<State, vector<State>, greater<State>> pq;

        vector<long long> dist(n, INF);
        dist[0] = 0;

        // make adj and rev_adj
        vector<vector<pair<int, int>>> adj(n);
        vector<vector<pair<int, int>>> rev_adj(n);
        for (auto const &edge : edges)
        {
            adj[edge[0]].push_back(make_pair(edge[1], edge[2]));
            rev_adj[edge[1]].push_back(make_pair(edge[0], edge[2]));
        }

        vector<char> switched(n, 0);
        State start = {0, 0}; // start from 0
        pq.push(start);

        while (!pq.empty())
        {
            State uState = pq.top();
            pq.pop();

            long long cost = uState.first;
            int u = uState.second;

            if (cost > dist[u])
                continue;

            for (auto const &[v, w] : adj[u])
            {
                int new_cost = cost + w;
                if (new_cost < dist[v])
                {
                    dist[v] = new_cost;
                    pq.push({new_cost, v});
                }
            }

            if (!switched[u])
            {
                for (auto const &[v, w] : rev_adj[u])
                {
                    int new_cost = cost + 2LL * w;
                    if (new_cost < dist[v])
                    {
                        dist[v] = new_cost;
                        pq.push({new_cost, v});
                    }
                }
                switched[u] = 1;
            }
        }

        if (dist[n - 1] == INF)
            return -1;

        return dist[n - 1];
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