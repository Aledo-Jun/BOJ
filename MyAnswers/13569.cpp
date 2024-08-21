//
// Created by june0 on 2024-08-21.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

class Dinic_LR {
private:
    struct Edge {
        int u, v, cap, lb, rev, f = 0, f0 = 0;
        bool is_back = false;
        Edge(int u, int v, int cap, int lb, int rev, bool back = false) : u(u), v(v), cap(cap), lb(lb), rev(rev), is_back(back) {}
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge &e: g[u]) {
                if (e.cap - e.f > 0 && level[e.v] == -1) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int flow) {
        if (u == t)
            return flow;

        for (; ptr[u] < g[u].size(); ptr[u]++) {
            Edge &e = g[u][ptr[u]];

            if (e.cap - e.f > 0 && level[e.v] == level[u] + 1) {
                int bottleneck = dfs(e.v, t, min(flow, e.cap - e.f));

                if (bottleneck > 0) {
                    e.f += bottleneck;
                    g[e.v][e.rev].f -= bottleneck;
                    return bottleneck;
                }
            }
        }
        return 0;
    }

public:
    explicit Dinic_LR(int n) : n(n), g(n), level(n), ptr(n) {}

    void addEdge(int u, int v, int cap, int lb = 0) {
        g[u].emplace_back(u, v, cap, lb, g[v].size());
        g[v].emplace_back(v, u, 0, 0, g[u].size() - 1, true);
    }

    void resolve_lower_bound() {
        vector<int> demand(n - 2, 0); // exclude src and sink
        for (int i = 0; i < n - 2; i++) {
            for (auto &[u, v, cap, lb, rev, f, f0, is_back]: g[i]) {
                if (lb) {
                    demand[u] += lb;
                    demand[v] -= lb;
                    cap -= lb;
                    f0 = lb;
                    lb = 0;
                }
            }
        }

        const int S = n - 2, T = n - 1; // new src and sink
        for (int i = 0; i < n - 2; i++) {
            if (demand[i] < 0) {
                addEdge(S, i, -demand[i]);
            } else if (demand[i] > 0) {
                addEdge(i, T, demand[i]);
            }
        }
    }

    int maxFlow(int s, int t) {
        int flow = 0;

        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (true) {
                int f = dfs(s, t, INT_MAX);
                if (f == 0) break;
                flow += f;
            }
        }

        return flow;
    }

    void solve(int s, int t, int R, int C) {
        maxFlow(s, t);

        matrix<int> ans(R + 1, vector<int>(C + 1));
        for (int i = 0; i < n; i++) {
            for (const auto &[u, v, cap, lb, rev, f, f0, is_back]: g[i]) {
                if (is_back || u == s || u == t || v == s || v == t) continue;
                if (R * C * 2 <= v && v < R * C * 2 + R) {
                    int r = v - R * C * 2;
                    ans[r][C] = f + f0;
                    continue;
                }
                if (R * C * 2 + R <= u && u < R * C * 2 + R + C) {
                    int c = u - R * C * 2 - R;
                    ans[R][c] = f + f0;
                    continue;
                }
                if (u >= R * C * 2 || v >= R * C * 2) continue;
                int r = (u / 2) / C;
                int c = (u / 2) % C;
                ans[r][c] = f + f0;
            }
        }

        for (int r = 0; r <= R; r++) {
            for (int c = 0; c <= C; c++) {
                if (r == R && c == C) continue;
                cout << ans[r][c] << ' ';
            }
            cout << endl;
        }
    }
};

const int INF = 1e9;

int32_t main() {
    fastIO;
    int m, n;
    cin >> m >> n;

    matrix<int> cell(m, vector<int>(n)), cell_remain(m, vector<int>(n));
    vector<int> row(m), row_remain(m), col(n), col_remain(n);
    char pnt;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cell[i][j] >> pnt >> cell_remain[i][j];
        }
        cin >> row[i] >> pnt >> row_remain[i];
    }
    for (int j = 0; j < n; j++) {
        cin >> col[j] >> pnt >> col_remain[j];
    }

    Dinic_LR solver(m * n * 2 + m + n + 4);

    const int S0 = m * n * 2 + m + n, T0 = S0 + 1;
    const int S = S0 + 2, T = T0 + 2;
    auto cell_idx = [&](int r, int c) { return n * r + c; }; // in: cell_idx * 2, out: cell_idx * 2 + 1
    auto row_idx = [&](int r) { return m * n * 2 + r; };
    auto col_idx = [&](int c) { return m * n * 2 + m + c; };

    // cell in -> out
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            solver.addEdge(cell_idx(i, j) * 2, cell_idx(i, j) * 2 + 1,
                           cell[i][j] + (cell_remain[i][j] != 0), cell[i][j]);
        }
    }
    // row sum -> each row node
    for (int i = 0; i < m; i++) {
        // src -> row sum
        solver.addEdge(S0, row_idx(i), row[i] + (row_remain[i] != 0), row[i]);
        for (int j = 0; j < n; j++) {
            solver.addEdge(row_idx(i), cell_idx(i, j) * 2, INF, 0);
        }
    }
    // each col node -> col sum
    for (int j = 0; j < n; j++) {
        // col sum -> sink
        solver.addEdge(col_idx(j), T0, col[j] + (col_remain[j] != 0), col[j]);
        for (int i = 0; i < m; i++) {
            solver.addEdge(cell_idx(i, j) * 2 + 1, col_idx(j), INF, 0);
        }
    }
    solver.addEdge(T0, S0, INF, 0); // make circulation

    solver.resolve_lower_bound();

    solver.solve(S, T, m, n);

    return 0;
}