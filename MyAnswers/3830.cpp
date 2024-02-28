//
// Created by june0 on 2024-02-28.
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

namespace DisjointSet {

    class WeightedDisjointSet {
    private:
        const int def_sz = 1001;
        vector<pair<int,int>> parent;
        vector<int> rank;
    public:
        WeightedDisjointSet() {
            parent.assign(def_sz, {0,0});
            rank.assign(def_sz, 0);
        }

        explicit WeightedDisjointSet(int sz) {
            parent.assign(sz, {0,0});
            for (int i = 0; i < sz; i++)
                parent[i] = {i, 0};
            rank.assign(sz, 0);
        }

        // find the root of x
        pair<int,int> find(int x, int w) {
            if (x != parent[x].first) {
                auto [p, pw] = find(parent[x].first, parent[x].second + w);
                parent[x] = {p, pw - w};
            }
            return {parent[x].first, parent[x].second + w};
        }

        // Union By Rank,
        // i.e. the parent relation could be relational(not specified).
        void uni(int x, int y, int w) {
            auto [rootx, wx] = find(x, 0);
            auto [rooty, wy] = find(y, 0);

            if (rootx != rooty) {
                if (rank[rootx] < rank[rooty]) {
                    parent[rootx] = {rooty, wy - wx - w};
                }
                else if (rank[rootx] > rank[rooty])
                    parent[rooty] = {rootx, wx - wy + w};
                else {
                    parent[rooty] = {rootx, wx - wy + w};
                    rank[rootx]++;
                }
            }
        }
    }; // class DisjointSet
} // namespace DisjointSet

int32_t main() {
    fastIO;
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        DisjointSet::WeightedDisjointSet ds(n + 1);

        for (int i = 0; i < m; i++){
            char cmd; cin >> cmd;
            if (cmd == '!'){
                int u, v, w;
                cin >> u >> v >> w;
                ds.uni(u, v, w);
            } else {
                int a, b;
                cin >> a >> b;

                auto [roota, wa] = ds.find(a, 0);
                auto [rootb, wb] = ds.find(b, 0);
                if (roota == rootb) {
                    cout << wb - wa << endl;
                } else {
                    cout << "UNKNOWN" << endl;
                }
            }
        }
    }
    return 0;
}