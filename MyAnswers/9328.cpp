//
// Created by june0 on 2024-02-12.
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

int n, m, ans;
vector<bool> keys; // since keys are alphabet(which can be at most 26 of them) using set is not proper.
matrix<char> table;

int isAlpha(int a){
    if ('A' <= a && a <= 'Z') return 1;
    if ('a' <= a && a <= 'z') return 2;
    return 0;
}

void init(){
    ans = 0;
    cin >> n >> m;
    table = vector(n + 2, vector<char>(m + 2, '.'));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> table[i][j];
        }
    }
    string s;
    cin >> s;
    keys = vector<bool>(26, false);
    if (s != "0")
        for (const auto& c : s) keys[c - 'a'] = true;
}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool bfs(){
    bool changed = false;
    matrix<bool> visited(n + 2, vector<bool>(m + 2, false));
    visited[0][0] = true;
    queue<pair<int,int>> q;
    q.emplace(0, 0);

    while (!q.empty()){
        const auto& [cx, cy] = q.front(); q.pop();
        for (int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx > n + 1 || ny < 0 || ny > m + 1 || table[nx][ny] == '*' || visited[nx][ny]) continue;
            if (table[nx][ny] == '.'){
                q.emplace(nx, ny);
                visited[nx][ny] = true;
            }
            else if (table[nx][ny] == '$'){
                ans++;
                table[nx][ny] = '.';
                q.emplace(nx, ny);
                visited[nx][ny] = true;
                changed = true;
            }
            else if (isAlpha(table[nx][ny]) == 2){ // lower case alphabet -> key
                keys[table[nx][ny] - 'a'] = true;
                table[nx][ny] = '.';
                q.emplace(nx, ny);
                visited[nx][ny] = true;
                changed = true;
            }
            else if (isAlpha(table[nx][ny]) == 1 && keys[table[nx][ny] - 'A']){ // upper case alphabet -> door
                table[nx][ny] = '.';
                q.emplace(nx, ny);
                visited[nx][ny] = true;
                changed = true;
            }
        }
    }
    return changed;
}

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--){
        init();
        while (true) {
            if (!bfs()) break;
        }
        cout << ans << endl;
    }

    return 0;
}