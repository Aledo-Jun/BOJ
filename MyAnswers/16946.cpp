//
// Created by june0 on 2024-02-14.
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
matrix<int> board, idx_matrix;
matrix<bool> visited;
vector<int> cnt_map;

void init(){
    cin >> n >> m;
    board.resize(n, vector<int>(m));
    for (auto& r : board)
        for (auto& c : r) {
            char a; cin >> a;
            c = a - '0';
        }
    idx_matrix.resize(n, vector<int>(m, 0));
    visited.resize(n, vector<bool>(m, false));
    cnt_map.resize(n * m);
}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int num_clusters = 0;
void count_cells(int x, int y){
    num_clusters++;
    int cnt = 0;
    queue<pair<int, int>> q;
    q.emplace(x, y);
    visited[x][y] = true;
    idx_matrix[x][y] = num_clusters;

    while (!q.empty()){
        auto [cx, cy] = q.front(); q.pop();
        cnt++;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && board[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.emplace(nx, ny);
                idx_matrix[nx][ny] = num_clusters;
            }
        }
    }
    cnt_map[num_clusters] = cnt;
}

int32_t main() {
    fastIO;
    init();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 0 && idx_matrix[i][j] == 0) {
                count_cells(i, j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 0) {
                cout << 0;
                continue;
            }
            int cnt = 1;
            set<int> included;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int idx = idx_matrix[nx][ny];
                    if (!included.count(idx)) {
                        cnt += cnt_map[idx];
                        included.insert(idx);
                    }
                }
            }
            cout << cnt % 10;
        }
        cout << endl;
    }

    return 0;
}