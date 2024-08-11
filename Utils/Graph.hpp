//
// Created by june0 on 2023-06-27.
//
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#include "using_templates.hpp"
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

    const size_t INF = LLONG_MAX;

    template<typename T>
    std::vector<std::size_t> dijkstra(const graph<T> &g, int start) {
        std::priority_queue<pair<std::size_t, int>, vector<pair<std::size_t, int>>, std::greater<>> pq;
        std::vector<std::size_t> dist(g.size(), INF);
        pq.emplace(0, start);
        dist[start] = 0;
        while (!pq.empty()) {
            const auto [distance, u] = pq.top();
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
    int minimumSpanningTree(const std::vector<Edge<T>> &g, int sz) {
        std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<>> minHeap(g.begin(), g.end());

        Utils::DisjointSet::DisjointSet<> ds(sz + 1);

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
    void inv_dfs_scc(const graph<T> &g, int u, std::vector<bool> &visited, std::set<int> &curr_scc) {
        for (const auto &e: g[u]) {
            if (visited[e.first]) continue;
            visited[e.first] = true;
            inv_dfs_scc(g, e.first, visited, curr_scc);
        }
        curr_scc.emplace(u); // may be modified when just the index of each vertex is needed.
    }

    /**
     * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
     *
     * @tparam T ValueType
     * @param g The given graph
     * @param g_r The inverse of the given graph
     * @return std::set of SCCs
     */
    template<typename T>
    vector<set<int>> scc(const graph<T> &g, const graph<T> &g_r) {
        std::vector<bool> visited(g.size(), false);
        std::stack<int> finishing_time;
        for (int i = 1; i < g.size(); i++) {
            if (visited[i]) continue;
            dfs_scc(g, i, visited, finishing_time);
        }

        visited.assign(g.size(), false);
        vector<set<int>> res;
        std::set<int> curr_scc;
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
    vector<int> scc(const graph<T> &g, const graph<T> &g_r) {
        std::vector<bool> visited(g.size(), false);
        std::stack<int> finishing_time;

        std::function<void(int)> dfs_scc = [&](int u) {
            if (visited[u]) return;
            visited[u] = true;

            for (const auto &[v, w]: g[u]) {
                dfs_scc(v);
            }
            finishing_time.emplace(u);
        };

        for (int i = 0; i < g.size(); i++) {
            if (visited[i]) continue;
            dfs_scc(i);
        }

        visited.assign(g.size(), false);
        vector<int> res(g.size(), -1);

        std::function<void(int, int)> inv_dfs_scc = [&](int u, int idx) {
            for (const auto &[v, w]: g_r[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                inv_dfs_scc(v, idx);
            }
            res[u] = idx;
        };

        int idx = 0;
        while (!finishing_time.empty()) {
            int u = finishing_time.top();
            finishing_time.pop();
            if (visited[u]) continue;
            visited[u] = true;
            inv_dfs_scc(u, idx++);
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

    /**
     * Bipartite Matching algorithm
     * @tparam T Value type
     * @var pairU
     * @var pairV
     */
    template<typename T>
    class Bipartite {
        int sz;
        graph<T> _g;
        std::vector<int> pairU, pairV;

    private:
        std::vector<bool> visited;

        bool dfs(int u) {
            visited[u] = true;
            for (const auto &[v, w]: _g[u]) {
                if (pairV[v] == -1 || !visited[pairV[v]] && dfs(pairV[v])) {
                    pairU[u] = v;
                    pairV[v] = u;
                    return true;
                }
            }
            return false;
        }

    public:
        Bipartite(const graph<T> &g) : _g(g), sz((int) g.size()) {
            visited.resize(sz);
            pairU.resize(sz, -1);
            pairV.resize(sz, -1);
        }

        /**
         * Finds the largest matching
         * @return Maximum number of matched nodes
         */
        int maxBPM() {
            int result = 0;

            for (int u = 0; u < sz; u++) {
                std::fill(visited.begin(), visited.end(), false);
                result += dfs(u);
            }

            return result;
        }
    };

    /**
     * Dinic's algorithm to find the maximum flow of the given network graph.
     */
    class Dinic {
        int n;
        vector<vector<int>> g, flow, cap;
        vector<int> level, ptr;

        bool bfs(int s, int t) {
            fill(all(level), -1);
            level[s] = 0;
            queue<int> q;
            q.push(s);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (const auto &v: g[u]) {
                    if (level[v] == -1 && cap[u][v] - flow[u][v] > 0) {
                        level[v] = level[u] + 1;
                        q.emplace(v);
                    }
                }
            }

            return level[t] != -1;
        }

        int dfs(int u, int t, int curr_flow) {
            if (u == t)
                return curr_flow;

            for (; ptr[u] < g[u].size(); ptr[u]++) {
                auto &v = g[u][ptr[u]];

                if (cap[u][v] - flow[u][v] > 0 && level[v] == level[u] + 1) {
                    int bottleneck = dfs(v, t, min(curr_flow, cap[u][v] - flow[u][v]));

                    if (bottleneck > 0) {
                        flow[u][v] += bottleneck;
                        flow[v][u] -= bottleneck;
                        return bottleneck;
                    }
                }
            }
            return 0;
        }

    public:
        Dinic(int sz) : n(sz), g(sz), level(sz), ptr(sz),
                        flow(sz, vector<int>(sz, 0)), cap(sz, vector<int>(sz, 0)) {}

        void add_edge(int u, int v, int c, bool is_directed = true) {
            g[u].emplace_back(v);
            g[v].emplace_back(u);
            cap[u][v] += c;
            if (!is_directed) cap[v][u] += c;
        }

        int max_flow(int s, int t) {
            int res = 0;
            while (bfs(s, t)) {
                fill(all(ptr), 0);
                while(int f = dfs(s, t, INT_MAX)) res += f;
            }
            return res;
        }

        auto min_cut(int s) {
            vector<bool> visited(n, false);
            queue<int> q;
            visited[s] = true;
            q.emplace(s);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (const auto &v : g[u]) {
                    if (!visited[v] && cap[u][v] - flow[u][v] > 0) {
                        visited[v] = true;
                        q.emplace(v);
                    }
                }
            }
            return visited;
        }
    };

    class MinCostMaxFlow {
        const int INF = 1e9;

        struct Edge {
            int u, v, cap, rev, cost;

            Edge(int u, int v, int cap, int rev, int cost) : u(u), v(v), cap(cap), rev(rev), cost(cost) {}
        };

    private:
        int n;
        vector<vector<Edge>> g;
        vector<int> dist;
        vector<Edge *> prev;

        bool bellmanFord(int s, int t) {
            dist.assign(n, INF);
            queue<int> q;
            vector<bool> is_in_q(n, false);

            dist[s] = 0;
            q.emplace(s);
            is_in_q[s] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                is_in_q[u] = false;
                for (auto &e: g[u]) {
                    if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
                        dist[e.v] = dist[u] + e.cost;
                        prev[e.v] = &e;
                        if (!is_in_q[e.v]) {
                            is_in_q[e.v] = true;
                            q.emplace(e.v);
                        }
                    }
                }
            }
            return dist[t] != INF;
        }

    public:
        explicit MinCostMaxFlow(int n) : n(n), g(n), dist(n), prev(n) {}

        void addEdge(int u, int v, int cap, int cost) {
            g[u].emplace_back(u, v, cap, g[v].size(), cost);
            g[v].emplace_back(v, u, 0, g[u].size() - 1, -cost);
        }

        pair<int, int> minCostMaxFlow(int s, int t) {
            int flow = 0, cost = 0;
            while (bellmanFord(s, t)) {
                // find minimum flow
                int curr = INF;
                for (auto e = prev[t]; e; e = prev[e->u]) {
                    curr = min(curr, e->cap);
                }
                flow += curr;

                for (auto e = prev[t]; e; e = prev[e->u]) {
                    cost += curr * e->cost;

                    // reverse direction
                    e->cap -= curr;
                    g[e->v][e->rev].cap += curr;
                }
            }
            return {flow, cost};
        }
    }; // class MCMF

#pragma ide diagnostic pop
} // namespace Graph
} // namespace Utils