//
// Created by june0 on 2024-02-15.
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


int n, m;
matrix<int> grid, idx_grid;
matrix<bool> visited;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void init(){
    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    for (auto& r : grid)
        for (auto& c : r) {
            char a;
            cin >> a;
            if (a == 'U') c = 0;
            if (a == 'D') c = 1;
            if (a == 'L') c = 2;
            if (a == 'R') c = 3;
        }
    idx_grid.resize(n, vector<int>(m, 0));
    visited.resize(n, vector<bool>(m, false));
}

int ans = 0;
void bfs(int x, int y, int idx) {
    visited[x][y] = true;
    idx_grid[x][y] = idx;

    while (true) {
        int nx = x + dx[grid[x][y]];
        int ny = y + dy[grid[x][y]];

        if (!visited[nx][ny]) {
            visited[nx][ny] = true;
            idx_grid[nx][ny] = idx;
            x = nx, y = ny;
        } else if (idx_grid[nx][ny] == idx) {
            ans++;
            return;
        } else {
            return;
        }
    }
}

int32_t main() {
    fastIO;
    init();
    int idx = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (!visited[i][j]){
                bfs(i, j, ++idx);
            }
        }
    }
    cout << ans;

    return 0;
}