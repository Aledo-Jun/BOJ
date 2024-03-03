//
// Created by june0 on 2024-03-03.
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

//
/// "Premature optimization is the root of all evil." -- Donald Knuth
//
vector<int> ants;
int MAX_BIT, n;
std::vector<int> depth; // Depth of each node
std::vector<std::vector<int>> parent; // Binary Lifting table
graph<int> adj; // Adjacency list of the tree, Assume that nodes are 1-indexed

void make_tree(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int i = 1; i < MAX_BIT; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (const auto& [v, w]: adj[u]) {
        if (v != p) {
            make_tree(v, u, d + w);
        }
    }
}

void init(){
    cin >> n;
    adj.resize(n + 1);
    ants.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> ants[i];
    for (int i = 0; i < n - 1; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    MAX_BIT = std::ceil(std::log2(n + 1));
    depth.resize(n + 1);
    parent.resize(n + 1, vector<int>(MAX_BIT));
    make_tree(1, 1, 0);
}

int32_t main() {
    fastIO;
    init();

    for (int i = 1; i <= n; i++){
        int curr = i;
        for (int j = MAX_BIT - 1; j >= 0 && curr != 1; j--){
            if (depth[curr] - depth[parent[curr][j]] <= ants[i]){
                ants[i] -= depth[curr] - depth[parent[curr][j]];
                curr = parent[curr][j];
            }
        }
        cout << curr << endl;
    }

    return 0;
}