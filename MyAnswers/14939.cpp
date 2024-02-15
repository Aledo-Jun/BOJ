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

matrix<int> origin(10, vector<int>(10)), grid;

const int dx[]{1, -1, 0, 0};
const int dy[]{0, 0, 1, -1};

void init(){
    for (auto& r : origin)
        for (auto& c : r) {
            char a; cin >> a;
            c = a == 'O';
        }
}

void click(int x, int y){
    grid[x][y] ^= 1;
    for (int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx > 9 || ny < 0 || ny > 9) continue;
        grid[nx][ny] ^= 1;
    }
}

int32_t main() {
    fastIO;
    init();
    int ans = INT_MAX;
    for (int bit = 0; bit < 1 << 10; bit++){
        int cnt = 0;
        grid = origin;
        for (int i = 0; i < 10; i++){
            if (bit & 1 << i){
                click(0, i);
                cnt++;
            }
        }
        for (int x = 1; x < 10; x++){
            for (int y = 0; y < 10; y++){
                if (grid[x - 1][y]){
                    click(x, y);
                    cnt++;
                }
            }
        }
        bool flag = true;
        for (int i = 0; i < 10; i++)
            if (grid[9][i]) flag = false;
        if (flag) ans = min(ans, cnt);
    }

    cout << (ans == INT_MAX ? -1 : ans);

    return 0;
}