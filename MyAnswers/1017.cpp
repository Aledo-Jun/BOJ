//
// Created by june0 on 2024-03-08.
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

const int MAX_N = 50;

int N;
vector<int> ans;
vector<int> even, odd;
vector<bool> isPrime;

void prime_sieve(int n) {
    std::vector<bool> is_prime = std::vector<bool>(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    isPrime = is_prime;
}

graph<int> g;
vector<int> pairU, pairV;
vector<bool> visited;

void init(){
    prime_sieve(2'000);
    cin >> N;
    g.resize(N);
    int First;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        if (i == 0) First = x;
        if (x & 1) odd.emplace_back(x);
        else even.emplace_back(x);
    }
    if (!(First & 1)) swap(odd, even);
    pairU.resize(N);
    pairV.resize(N);
    visited.resize(N);
}

bool dfs(int u) {
    if (visited[u]) return false;
    visited[u] = true;
    for (const auto& [v, w]: g[u]){
        if (pairV[v] == -1 || dfs(pairV[v])){
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }
    return false;
}

int maxBPM(int v) {
    fill(pairU.begin(), pairU.end(), -1);
    fill(pairV.begin(), pairV.end(), -1);

    int result = 1;
    pairU[0] = v;
    pairV[v] = 0;

    for (int u = 1; u < N / 2; u++){
        fill(visited.begin(), visited.end(), false);
        visited[0] = true;
        result += dfs(u);
    }

    return result;
}

int32_t main() {
    fastIO;
    init();
    if (odd.size() != even.size()) return cout << -1, 0;

    // Create the bipartite graph
    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            if (isPrime[odd[i] + even[j]]) {
                g[i].emplace_back(j + N / 2, 1);
            }
        }
    }

    for (const auto& [v, w]: g[0]){
        if (maxBPM(v) == N / 2) ans.emplace_back(even[v - N / 2]);
    }

    sort(ans.begin(), ans.end());
    if (ans.empty()) cout << -1;
    else for (const auto& e : ans) cout << e << ' ';

    return 0;
}