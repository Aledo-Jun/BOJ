//
// Created by june0 on 2024-03-09.
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

int N, M;
graph<int> g;
vector<int> pairU, pairV;
vector<bool> visited;

void init(){
    cin >> N >> M;
    g.resize(N);
    for (int i = 0; i < N; i++){
        int n; cin >> n;
        for (int j = 0; j < n; j++){
            int x; cin >> x;
            g[i].emplace_back(x - 1, 1);
        }
    }
    pairU.resize(N);
    pairV.resize(M);
    visited.resize(N);
}

bool dfs(int u) {
    visited[u] = true;
    for (const auto& [v, w]: g[u]){
        if (pairV[v] == -1 || !visited[pairV[v]] && dfs(pairV[v])){
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }
    return false;
}

int maxBPM(int U, int V) {
    fill(pairU.begin(), pairU.end(), -1);
    fill(pairV.begin(), pairV.end(), -1);

    int result = 0;

    for (int u = 0; u < U; u++){
        fill(visited.begin(), visited.end(), false);
        result += dfs(u);
    }

    return result;
}

int32_t main() {
    fastIO;
    init();

    int ans = maxBPM(N, M);
    cout << ans;

    return 0;
}