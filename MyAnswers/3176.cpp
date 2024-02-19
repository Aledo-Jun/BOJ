//
// Created by june0 on 2024-02-19.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

namespace Utils
{
    namespace Tree {
        class LCA {
        private:
            int MAX_BIT; // Adjust this based on your maximum number of nodes

            std::vector<int> depth; // Depth of each node
            std::vector<std::vector<int>> parent; // Binary Lifting table
            graph<int> adj; // Adjacency list of the tree, Assume that nodes are 1-indexed

            std::vector<std::vector<int>> mx, mn;
        public:
            LCA(const graph<int>& adj) : adj(adj) {
                int sz = (int) adj.size();
                MAX_BIT = ceil(log2(sz));
                depth.resize(sz);
                parent.resize(sz, vector<int>(MAX_BIT, 0));
                mn.resize(sz, vector<int>(MAX_BIT, INT_MAX));
                mx.resize(sz, vector<int>(MAX_BIT, -1));
                make_tree(1, 0, 0, 0);
            }

            void make_tree(int u, int p, int d, int w) {
                depth[u] = d;
                parent[u][0] = p;
                mx[u][0] = w;
                mn[u][0] = w;
                for (int i = 1; i < MAX_BIT; i++) {
                    parent[u][i] = parent[parent[u][i - 1]][i - 1];
                    mx[u][i] = max(mx[u][i - 1], mx[parent[u][i - 1]][i - 1]);
                    mn[u][i] = min(mn[u][i - 1], mn[parent[u][i - 1]][i - 1]);
                }
                for (const auto& [v, ww]: adj[u]) {
                    if (v != p) {
                        make_tree(v, u, d + 1, ww);
                    }
                }
            }

            void lca(int u, int v) {
                int shortest = INT_MAX, longest = -1;
                if (depth[u] < depth[v]) swap(u, v);
                for (int i = MAX_BIT - 1; i >= 0; i--) {
                    if (depth[u] - (1 << i) >= depth[v]) {
                        shortest = min(shortest, mn[u][i]);
                        longest = max(longest, mx[u][i]);
                        u = parent[u][i];
                    }
                }
                if (u == v) {
                    cout << shortest << ' ' << longest << endl;
                    return;
                }
                for (int i = MAX_BIT - 1; i >= 0; i--) {
                    if (parent[u][i] != parent[v][i]) {
                        shortest = min({shortest, mn[u][i], mn[v][i]});
                        longest = max({longest, mx[u][i], mx[v][i]});
                        u = parent[u][i];
                        v = parent[v][i];
                    }
                }
                shortest = min({shortest, mn[u][0], mn[v][0]});
                longest = max({longest, mx[u][0], mx[v][0]});
                cout << shortest << ' ' << longest << endl;
            }

        };
    }
} // namespace Utils

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    Utils::Tree::LCA lca(g);

    int q; cin >> q;
    while (q--){
        int a, b;
        cin >> a >> b;
        lca.lca(a, b);
    }

    return 0;
}