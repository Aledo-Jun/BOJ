//
// Created by june0 on 2024-01-28.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

matrix<int> table;
matrix<bool> visited;
int n, mn = 201, mx = -1;

void init() {
    cin >> n;
    table.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> table[i][j];
            mn = min(mn, table[i][j]);
            mx = max(mx, table[i][j]);
        }
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool bfs(int diff) {
    queue<pair<int,int>> q;

    for (int k = mn; k <= mx; k++){
        visited = matrix<bool>(n, vector<bool>(n, true));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (k <= table[i][j] && table[i][j] <= k + diff) visited[i][j] = false;
            }
        }

        q.emplace(0, 0);
        while (!q.empty()){
            auto [x, y] = q.front();
            q.pop();

            if (visited[x][y]) continue;
            visited[x][y] = true;

            if (x == n - 1 && y == n - 1) return true;

            for (int i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n) q.emplace(nx, ny);
            }
        }
    }
    return false;
}

void solve() {
    int l = 0, r = mx - mn, mid;
    while (l <= r){
        mid = (l + r) >> 1;
        if (bfs(mid)) r = mid - 1;
        else l = mid + 1;
    }
    cout << r + 1 << endl;
}

int32_t main() {
    fastIO;
    init();
    solve();

    return 0;
}