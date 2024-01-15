//
// Created by june0 on 2024-01-15.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define int ll
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

namespace NTT {
    constexpr int MOD = 998'244'353;
    constexpr int ROOT = 3;

    inline int pow_mod(int a, int p){
        long long res = 1LL;
        while (p > 0){
            if (p & 1) (res *= a) %= MOD;
            (a *= a) %= MOD;
            p >>= 1;
        }
        return (int) res;
    }

    vector<int> get_roots(int n, bool _is_inv){
        int x = pow_mod(ROOT, (MOD - 1) / n);
        if (_is_inv) x = pow_mod(x, MOD - 2);

        vector<int> root(n >> 1, 1);
        for (int i = 1; i < (n >> 1); i++){
            root[i] = (root[i - 1] * x) % MOD;
        }
        return root;
    }

    void _ntt(std::vector<int> &_v, bool _is_inv){
        int n = (int) _v.size();
        // bit-reversal
        for (int i = 1, j = 0; i < n; i++){
            int _bit = n >> 1;
            while (!((j ^= _bit) & _bit)) _bit >>= 1;
            if (i < j) std::swap(_v[i], _v[j]);
        }

        auto roots = get_roots(n, _is_inv);
        for (int i = 2; i <= n; i <<= 1){
            int x = n / i;
            for (int j = 0; j < n; j += i){
                for (int k = 0; k < (i >> 1); k++){
                    int tmp = (_v[(i >> 1) + j + k] * roots[x * k]) % MOD;
                    _v[(i >> 1) + j + k] = (_v[j + k] - tmp + MOD) % MOD;
                    (_v[j + k] += tmp) %= MOD;
                }
            }
        }
        if (_is_inv){
            int n_inv = pow_mod(n, MOD - 2);
            for (auto& z : _v) (z *= n_inv) %= MOD;
        }
    }

    template<typename T,
            std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    void ntt(std::vector<T> &_v){
        _ntt(_v, false);
    }

    template<typename T,
            std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    void inv_ntt(std::vector<T> &_v){
        _ntt(_v, true);
    }

    std::vector<int> _naive_convolution(const std::vector<int> &_a,
                                        const std::vector<int> &_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        std::vector<int> res(n + m - 1);
        if (n < m){
            for (int j = 0; j < m; j++){
                for (int i = 0; i < n; i++){
                    (res[i + j] += (1LL * _a[i] * _b[j]) % MOD) %= MOD;
                }
            }
        } else {
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    (res[i + j] += (1LL * _a[i] * _b[j]) % MOD) %= MOD;
                }
            }
        }
        return res;
    }

    std::vector<int> _ntt_convolution(std::vector<int> &_a,
                                      std::vector<int> &_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        int len = 1;
        while (len < (n + m)) len <<= 1;

        _a.resize(len);
        _ntt(_a, false);
        _b.resize(len);
        _ntt(_b, false);

        for (int i = 0; i < len; i++)
            (_a[i] *= _b[i]) %= MOD;

        _ntt(_a, true);
        return _a;
    }

    std::vector<int> _convolution(std::vector<int> &&_a,
                                  std::vector<int> &&_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _ntt_convolution(_a, _b);
    }

    std::vector<int> _convolution(std::vector<int> &_a,
                                  std::vector<int> &_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _ntt_convolution(_a, _b);
    }

    template<typename T,
            std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    std::vector<T> convolution(const std::vector<T> &a,
                               const std::vector<T> &b){
        int n = (int) a.size();
        int m = (int) b.size();
        if (n == 0 || m == 0) return {};

        std::vector<int> _a(a.begin(), a.end()), _b(b.begin(), b.end());
        auto conv = _convolution(std::move(_a), std::move(_b));

        std::vector<T> res(n + m - 1);
        for (int i = 0; i < n + m - 1; i++)
            res[i] = conv[i];

        return res;
    }
}
using namespace NTT;

vector<int> multiply(const vector<int> &a, const vector<int> &b){
    auto res = convolution(a, b);
    for (int i = 0; i < res.size(); i++){
        if (res[i] > 9) {
            if (i + 1 == res.size()) res.emplace_back(0);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    return res;
}

vector<int> sToVec(const string& n){
    int l = n.length();
    vector<int> res(l);
    for (int i = 0; i < l; i++)
        res[l - 1 - i] = n[i] - '0';
    return res;
}

int32_t main() {
    fastIO;
    string a, b;
    cin >> a >> b;

    auto A = sToVec(a), B = sToVec(b);
    auto ans = multiply(A, B);
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i];
    return 0;
}