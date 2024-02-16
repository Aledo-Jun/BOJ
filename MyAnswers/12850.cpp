//
// Created by june0 on 2024-02-16.
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

// Matrix size
const int SIZE = 8;

// Matrix multiplication operation
template<typename T,
        typename std::enable_if_t<is_arithmetic_v<T>> * = nullptr>
void multiply(matrix<T> &A, matrix<T> &B, int MOD) {
    matrix<T> temp(SIZE, vector<T>(SIZE));

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                temp[i][j] = (temp[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = temp[i][j];
        }
    }
}

// Matrix exponentiation
template<typename T,
        typename std::enable_if_t<is_arithmetic_v<T>> * = nullptr>
void matrixPow(matrix<T> &A, int n, int MOD) {
    matrix<T> result(SIZE, vector<T>(SIZE, 0));
    for (int i = 0; i < SIZE; i++)
        result[i][i] = 1; // Identity matrix

    while (n > 0) {
        if (n & 1) {
            multiply(result, A, MOD);
        }

        multiply(A, A, MOD);
        n >>= 1;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = result[i][j];
        }
    }
}

int32_t main() {
    fastIO;
    int d;
    cin >> d;
    matrix<ll> base = { {0, 1, 1, 0, 0, 0, 0, 0},
                        {1, 0, 1, 1, 0, 0, 0, 0},
                        {1, 1, 0, 1, 1, 0, 0, 0},
                        {0, 1, 1, 0, 1, 1, 0, 0},
                        {0, 0, 1, 1, 0, 1, 0, 1},
                        {0, 0, 0, 1, 1, 0, 1, 0},
                        {0, 0, 0, 0, 0, 1, 0, 1},
                        {0, 0, 0, 0, 1, 0, 1, 0} };

    matrixPow(base, d, 1'000'000'007);

    cout << base[0][0];

    return 0;
}