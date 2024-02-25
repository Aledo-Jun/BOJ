//
// Created by june0 on 2023-06-27.
//
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>
#include "DisjointSet.hpp"

using namespace std;

namespace Utils
{
namespace Graph {

    // #pragma is for an unusual bug(it seems to be) that ide warns
    // that the template function's parameters are never used when clearly they're used.
    #pragma ide diagnostic push
    #pragma ide diagnostic ignored "UnusedParameter"

    //
    // Note: Assumes that graph is 1-indexed //
    //

    template<typename T> using graph = vector<vector<pair<int, T>>>;
    template<typename T> using matrix = vector<vector<T>>;
    const size_t INF = LLONG_MAX;

    template<typename T>
    std::vector<std::size_t> dijkstra(const graph<T> &g, int start) {
        std::priority_queue<pair<std::size_t, int>, vector<pair<std::size_t, int>>, std::greater<>> pq;
        std::vector<std::size_t> dist(g.size(), INF);
        pq.emplace(0, start);
        dist[start] = 0;
        while (!pq.empty()) {
            const auto& [distance, u] = pq.top();
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

    template<typename T>
    std::vector<std::size_t> bellmanFord(const graph<T> &g, int start) {
        int n = (int) g.size() - 1;
        std::vector<std::size_t> dist(n + 1, INF);
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
    template<typename T>
    bool is_there_negative_cycle(const graph<T> &g, const std::vector<std::size_t> &dist) {
        int n = (int) g.size() - 1;
        for (int u = 1; u <= n; u++) {
            if (g[u].empty()) continue;
            for (const auto &[v, w]: g[u]) {
                if (dist[u] != INF && dist[u] + w < dist[v])
                    return true;
            }
        }
        return false;
    }

    template<typename T>
    matrix<std::size_t> floydWarshall(const graph<T> &g) {
        int n = (int) g.size() - 1;
        matrix<std::size_t> res(n + 1, std::vector<std::size_t>(n + 1, INF));
        for (int i = 1; i <= n; i++) {
            for (const auto &e: g[i]) {
                res[i][e.first] = e.second;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    res[i][j] = std::min(res[i][j], res[i][k] + res[k][j]);
                }
            }
        }
        return res;
    }

    template<typename T>
    void dfs_for_topological_order(graph<T> &g, int u, std::vector<bool> &visited, std::vector<int> &order) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &[v, w]: g[u]) {
            dfs_for_topological_order(g, v, visited, order);
        }

        order.emplace_back(u);
    }

    template<typename T>
    std::vector<int> topological_order_dfs(const graph<T> &g) {
        int n = (int) g.size() - 1;
        std::vector<bool> visited(n + 1, false);
        std::vector<int> result;

        for (int i = 1; i <= n; i++)
            dfs_for_topological_order(g, i, visited, result);

        std::reverse(result.begin(), result.end());
        return result;
    }

    template<typename T>
    std::vector<int> topological_order_degree(const graph<T> &g) {
        int n = (int) g.size() - 1;
        std::vector<int> in_degree(g.size(), 0);
        std::vector<int> result;
        std::queue<int> q;
        for (int u = 1; u <= n; u++){
            for (const auto&[v, w] : g[u])
                in_degree[v]++;
        }
        for (int u = 1; u <= n; u++){
            if (in_degree[u] == 0) q.emplace(u);
        }

        while (!q.empty()){
            int u = q.front(); q.pop();
            result.emplace_back(u);

            for (const auto&[v, w] : g[u]){
                in_degree[v]--;
                if (in_degree[v] == 0) q.emplace(v);
            }
        }

        return result;
    }

    template<typename T>
    struct Edge {
        int u, v;
        T w;

        Edge(int u, int v, T w) : u(u), v(v), w(w) {};

        bool operator<(const Edge &other) const {
            return w < other.w;
        }

        bool operator>(const Edge &other) const {
            return w > other.w;
        }
    };

    template<typename T>
    std::size_t minimumSpanningTree(const std::vector<Edge<T>> &g) {
        std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<>> minHeap(g.begin(), g.end());

        Utils::DisjointSet::DisjointSet ds(g.size() + 1);

        std::size_t res = 0;
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

    template<typename T>
    void dfs_scc(const graph<T> &g, int u, std::vector<bool> &visited, std::stack<int> &finishing) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &e: g[u]) {
            dfs_scc(g, e.first, visited, finishing);
        }
        finishing.emplace(u);
    }

    template<typename T>
    void inv_dfs_scc(const graph<T> &g, int u, std::vector<bool> &visited, std::vector<int> &curr_scc) {
        for (const auto &e: g[u]) {
            if (visited[e.first]) continue;
            visited[e.first] = true;
            inv_dfs_scc(g, e.first, visited, curr_scc);
        }
        curr_scc.emplace_back(u);
    }

 /**
  * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
  *
  * @tparam T ValueType
  * @param g The given graph
  * @param g_r The inverse of the given graph
  * @return std::vector of SCCs
  */
    template<typename T>
    matrix<int> scc(const graph<T> &g, const graph<T> &g_r) {
        std::vector<bool> visited(g.size(), false);
        std::stack<int> finishing_time;
        for (int i = 1; i < g.size(); i++) {
            if (visited[i]) continue;
            dfs_scc(g, i, visited, finishing_time);
        }

        visited.assign(g.size(), false);
        matrix<int> res;
        std::vector<int> curr_scc;
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


    template<typename T>
    int dfs_articulation_points(const graph<T>& g, int u, bool is_root, vector<int>& mark, int& cnt, set<int>& res) {
        mark[u] = cnt++;
        int ret = mark[u];

        int child = 0;
        for (const auto &[v, w]: g[u]) {
            if (mark[v] == 0) {
                child++;
                int lowest = dfs_articulation_points(g, v, false, mark, cnt, res);
                if (!is_root && lowest >= mark[u]) {
                    res.emplace(u);
                }
                ret = min(ret, lowest);
            } else {
                ret = min(ret, mark[v]);
            }
        }

        if (is_root && child >= 2)
            res.emplace(u);

        return ret;
    }

    /**
     * Find articulation points(a.k.a. cut-vertices) of the given graph.
     * @param g The graph (assumed to be 1-indexed)
     * @return std::set of the articulation points
     */
    template<typename T>
    std::set<int> articulation_points(const graph<T>& g){
        int n = (int) g.size() - 1;
        std::set<int> res;
        vector<int> mark(n + 1, 0);
        int cnt = 1;

        for (int i = 1; i <= n; i++){
            if (mark[i] == 0) dfs_articulation_points(g, i, true, mark, cnt, res);
        }

        return res;
    }

    template<typename T>
    int dfs_articulation_bridges(const graph<T>& g, int u, int p, vector<int>& mark, int& cnt, set<pair<int,int>>& res) {
        mark[u] = cnt++;
        int ret = mark[u];

        for (const auto &[v, w]: g[u]) {
            if (v == p) continue;
            if (mark[v] == 0) {
                int lowest = dfs_articulation_bridges(g, v, u, mark, cnt, res);
                if (lowest > mark[u]) {
                    res.emplace(min(u, v), max(u, v));
                }
                ret = min(ret, lowest);
            } else {
                ret = min(ret, mark[v]);
            }
        }

        return ret;
    }

    /**
     * Find articulation bridges(a.k.a. cut-edges) of the given graph.
     * @param g The graph (assumed to be 1-indexed)
     * @return std::set of the articulation bridges
     */
    template<typename T>
    std::set<pair<int,int>> articulation_bridges(const graph<T>& g) {
        int n = (int) g.size() - 1;
        std::set<pair<int, int>> res;
        vector<int> mark(n + 1, 0);
        int cnt = 1;

        for (int i = 1; i <= n; i++) {
            if (mark[i] == 0) dfs_articulation_bridges(g, i, 0, mark, cnt, res);
        }

        return res;
    }

#pragma ide diagnostic pop
} // namespace Graph
} // namespace Utils