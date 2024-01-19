//
// Created by june0 on 2023-06-27.
//
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
#include "DisjointSet.hpp"

using namespace std;

namespace Utils
{
namespace Graph
{
    template<typename T> using graph = vector<vector<pair<int, T>>>;
    template<typename T> using matrix = vector<vector<T>>;
    const int INF = INT_MAX;

    vector<int> dijkstra(const graph<int> &g, int start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(g.size(), INF);
        pq.emplace(0, start);
        dist[start] = 0;
        while (!pq.empty()) {
            int distance = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (distance > dist[u]) continue;

            for (const auto &[v, w]: g[u]) {
                if (distance + w < dist[v]) {
                    dist[v] = distance + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }

    vector<int> bellmanFord(const graph<int> &g, int start) {
        int n = g.size() - 1;
        vector<int> dist(n + 1, INF);
        dist[start] = 0;

        for (int i = 1; i < n; i++) {
            for (int u = 1; u <= n; u++) {
                for (const auto &[v, w]: g[u]) {
                    if (dist[u] != INF && dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }
            }
        }
        return dist;
    }

/**
 * Verify whether the graph has a negative cycle or not when called <i>after</i> calling bellmanFord
 */
    bool is_there_negative_cycle(const graph<int> &g, const vector<int> &dist) {
        int n = g.size() - 1;
        for (int u = 1; u <= n; u++) {
            if (g[u].empty()) continue;
            for (const auto &[v, w]: g[u]) {
                if (dist[u] != INF && dist[u] + w < dist[v])
                    return true;
            }
        }
        return false;
    }

    matrix<int> floydWarshall(const graph<int> &g) {
        int n = g.size() - 1;
        matrix<int> res(n + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 1; i <= n; i++) {
            for (const auto &e: g[i]) {
                res[i][e.first] = e.second;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    res[i][j] = min(res[i][j], res[i][k] + res[k][j]);
                }
            }
        }
        return res;
    }

    void dfs_for_topological_order(graph<int> &g, int u, vector<bool> &visited, vector<int> &order) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &[v, w]: g[u]) {
            dfs_for_topological_order(g, v, visited, order);
        }

        order.emplace_back(u);
    }

    vector<int> topological_order(graph<int> &g) {
        int n = g.size() - 1;
        vector<bool> visited(n + 1, false);
        vector<int> result;

        for (int i = 1; i <= n; i++)
            dfs_for_topological_order(g, i, visited, result);

        std::reverse(result.begin(), result.end());
        return result;
    }

    using namespace Utils::DisjointSet;

    struct Edge {
        int u, v, w;

        Edge(int u, int v, int w) : u(u), v(v), w(w) {};

        bool operator<(const Edge &other) const {
            return w < other.w;
        }

        bool operator>(const Edge &other) const {
            return w > other.w;
        }
    };

    int minimumSpanningTree(const vector<Edge> &g) {
        priority_queue<Edge, vector<Edge>, greater<>> minHeap;

        for (int i = 0; i < g.size(); i++)
            minHeap.emplace(g[i]);

        disjointSet ds(g.size() + 1);

        int res = 0;
        while (!minHeap.empty()) {
            auto e = minHeap.top();
            minHeap.pop();
            if (ds.find(e.u) != ds.find(e.v)) {
                ds.uni(e.u, e.v);
                res += e.w;
            }
        }
        return res;
    }

    void dfs_scc(graph<int> &g, int u, vector<bool> &visited, stack<int> &finishing) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &e: g[u]) {
            dfs_scc(g, e.first, visited, finishing);
        }
        finishing.emplace(u);
    }

    void inv_dfs_scc(graph<int> &g, int u, vector<bool> &visited, vector<int> &curr_scc) {
        for (const auto &e: g[u]) {
            if (visited[e.first]) continue;
            visited[e.first] = true;
            inv_dfs_scc(g, e.first, visited, curr_scc);
        }
        curr_scc.emplace_back(u);
    }

/**
 * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
 */
    matrix<int> scc(graph<int> &g, graph<int> &g_r) {
        vector<bool> visited(g.size(), false);
        stack<int> finishing_time;
        for (int i = 1; i < g.size(); i++) {
            if (visited[i]) continue;
            dfs_scc(g, i, visited, finishing_time);
        }

        visited.assign(g.size(), false);
        matrix<int> res;
        vector<int> curr_scc;
        while (!finishing_time.empty()) {
            int u = finishing_time.top();
            finishing_time.pop();
            if (visited[u]) continue;
            visited[u] = true;
            inv_dfs_scc(g_r, u, visited, curr_scc);
            res.emplace_back(curr_scc);
            curr_scc.clear();
        }

        return res;
    }

} // namespace Graph
} // namespace Utils
