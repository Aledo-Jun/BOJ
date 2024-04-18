//
// Created by june0 on 2024-04-18.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

//#
//# Grid로 생각
//# (-10, A)에서 시작, x 방향으로 조금씩 움직이면서 현재 위치 기준으로 주변 cell 값을
//# 계산해 column 별로 dp를 관리
//# y -> more densely?
//#
const int X_MIN = -10, X_MAX = 10;
const int Y_MIN = -20, Y_MAX = 20; // 섬이 -10~10이니 -20~20 밖으로는 안 나갈 듯?
const double X_STEP_SIZE = 0.1;
const double Y_STEP_SIZE = 0.005;
const int N_COL = int((X_MAX - X_MIN) / X_STEP_SIZE); // -> 200
const int N_ROW = int((Y_MAX - Y_MIN) / Y_STEP_SIZE); // -> 8000
const int N_NEIGHBORS = 32; // 현재 위치 기준 위 아래로 N_NEIGHBORS 칸 만큼만 고려
const double eps = 1e-10;
const double INF = 1e100;

// return the radiation per unit-time at the 'pos' of the grid
double radiation(const vector<double>& islands, const pair<double,double>& pos) {
    double res = 0;
    for (const auto& island : islands) {
        double dist_squared = std::pow(pos.first, 2) + std::pow(pos.second - island, 2);
        if (dist_squared < eps) return INF;
        res += 1 / dist_squared;
    }
    return res;
}

// calculate the amount of radiation we got while traveling from start to end
double calc(const vector<double>& islands, const pair<int,int>& start, const pair<int,int>& end) {
    int dx = end.first - start.first;
    int dy = end.second - start.second;
    double ds = std::pow(X_STEP_SIZE * dx, 2) + std::pow(Y_STEP_SIZE * dy, 2);
    // NOTE: 1 is for the nature environment radiation
    return (1 + radiation(islands, {X_MIN + X_STEP_SIZE * start.first, Y_MIN + Y_STEP_SIZE * start.second})) * std::sqrt(ds);
}

double solve() {
    int n;
    double a, b;
    cin >> n >> a >> b;
    vector<double> islands(n);
    for (auto& e : islands) cin >> e;

    vector<double> curr_col(N_ROW + 1, INF);
    int a_idx = int((a - Y_MIN) / Y_STEP_SIZE);
    int b_idx = int((b - Y_MIN) / Y_STEP_SIZE);
    curr_col[a_idx] = 0;

    for (int i = 1; i <= N_COL; i++) {
        vector<double> next_col(N_ROW + 1, INF);
        for (int j = 0; j <= N_ROW; j++) {
            for (int k = max(0, j - N_NEIGHBORS); k <= min(j + N_NEIGHBORS, N_ROW); k++) {
                next_col[j] = min(next_col[j], curr_col[k] + calc(islands, {i - 1, k}, {i, j}));
            }
        }
        curr_col = next_col;
    }
    return curr_col[b_idx];
}

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": " << solve() << endl;
    }

    return 0;
}