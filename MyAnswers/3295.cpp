//
// Created by june0 on 2024-03-13.
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
    explicit Bipartite(const graph<T> &g) : _g(g), sz((int) g.size()), pairV(sz, -1), pairU(sz, -1), visited(sz, false) {}

    /**
     * Finds the largest matching
     * @return Maximum number of matched nodes
     */
    int maxBPM() {
        fill(pairU.begin(), pairU.end(), -1);
        fill(pairV.begin(), pairV.end(), -1);
        int result = 0;

        for (int u = 0; u < sz; u++) {
            std::fill(visited.begin(), visited.end(), false);
            result += dfs(u);
        }

        return result;
    }
};

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        graph<int> g(2 * n);
        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            g[u].emplace_back(v + n, 1);
        }
        Bipartite<int> b(g);
        cout << b.maxBPM() << endl;
    }

    return 0;
}