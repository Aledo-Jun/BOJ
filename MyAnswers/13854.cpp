//
// Created by june0 on 2024-06-17.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

namespace FFT {
    using base = std::complex<double>;
    const double PI = M_PI;

    void _fft(std::vector<base> &_v, bool _is_inv) {
        int n = (int) _v.size();
        for (int i = 1, j = 0; i < n; i++) {
            int _bit = n >> 1;
            // while (j >= _bit){
            //     j -= _bit;
            //     _bit /= 2;
            // }
            while (!((j ^= _bit) & _bit)) _bit >>= 1;
            if (i < j) std::swap(_v[i], _v[j]);
        }
        for (int i = 1; i < n; i <<= 1) {
            double x = _is_inv ? PI / i : -PI / i;
            base w = {cos(x), sin(x)};
            for (int j = 0; j < n; j += i << 1) {
                base z = {1, 0};
                for (int k = 0; k < i; k++) {
                    // base even = _v[j + k];
                    // base odd  = _v[i + j + k];
                    // _v[j + k] = even + z * odd;
                    // _v[i + j + k] = even - z * odd;

                    base tmp = _v[i + j + k] * z;
                    _v[i + j + k] = _v[j + k] - tmp;
                    _v[j + k] += tmp;

                    z *= w;
                }
            }
        }
        if (_is_inv) {
            for (auto &z: _v) z /= n;
        }
    }

    void fft(std::vector<base> &_v) {
        _fft(_v, false);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    vector<base> fft(std::vector<T> &v) {
        std::vector<base> _v(v.begin(), v.end());
        _fft(_v, false);
        return _v;
    }

    void inv_fft(std::vector<base> &_v) {
        _fft(_v, true);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    vector<base> inv_fft(std::vector<T> &v) {
        std::vector<base> _v(v.begin(), v.end());
        _fft(_v, true);
        return _v;
    }

    std::vector<base> _naive_convolution(const std::vector<base> &_a,
                                         const std::vector<base> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        std::vector<base> res(n + m - 1);
        if (n < m) {
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++) {
                    res[i + j] += _a[i] * _b[j];
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    res[i + j] += _a[i] * _b[j];
                }
            }
        }
        return res;
    }

    std::vector<base> _fft_convolution(std::vector<base> &_a,
                                       std::vector<base> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        int l = 32 - __builtin_clz(n + m), len = 1 << l;

        _a.resize(len);
        _fft(_a, false);
        _b.resize(len);
        _fft(_b, false);

        for (int i = 0; i < len; i++)
            _a[i] *= _b[i];

        _fft(_a, true);
        return _a;
    }

    std::vector<base> _less_fft_convolution(std::vector<base> &_a,
                                            std::vector<base> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        int l = 32 - __builtin_clz(n + m), len = 1 << l;

        _a.resize(len); _b.resize(len);
        for (int i = 0; i < m; i++) _a[i].imag(_b[i].real());
        _fft(_a, false);

        for (auto& x : _a) x *= x;

        for (int i = 0; i < len; i++) _b[i] = _a[i] - std::conj(_a[-i & len - 1]);

        _fft(_b, true);
        for (int i = 0; i < len; i++) _a[i].real(_b[i].imag() / 4);

        return _a;
    }

    std::vector<base> _convolution(std::vector<base> &&_a,
                                   std::vector<base> &&_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    std::vector<base> _convolution2(std::vector<base> &&_a,
                                    std::vector<base> &&_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        if (std::min(n, m) <= 150) return _fft_convolution(_a, _b);
        return _less_fft_convolution(_a, _b);
    }

    std::vector<base> convolution(std::vector<base> &_a,
                                  std::vector<base> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    template<typename T,
            std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    std::vector<T> convolution(const std::vector<T> &a,
                               const std::vector<T> &b) {
        int n = (int) a.size();
        int m = (int) b.size();
        if (n == 0 || m == 0) return {};

        std::vector<base> _a(a.begin(), a.end()), _b(b.begin(), b.end());
        auto conv = _convolution2(std::move(_a), std::move(_b));

        std::vector<T> res(n + m - 1);
        if (is_floating_point_v<T>) {
            for (int i = 0; i < n + m - 1; i++)
                res[i] = (T)conv[i].real();
        } else {
            for (int i = 0; i < n + m - 1; i++)
                res[i] = (T)std::round(conv[i].real());
        }

        return res;
    }
} // namespace FFT
using namespace FFT;

/**
 * Implementation of Eratosthenes' sieve
 * @param n
 * @return vector of primes that is less or equal than @p n
 */
std::vector<int> prime_sieve(int n) {
    std::vector<bool> is_prime = std::vector<bool>(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    std::vector<int> sieve;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i])
            sieve.push_back(i);
    }
    return sieve;
}

/**
  * @brief Centroid Tree implementation
  */
class CentroidTree {
    int n, root;
    int MAX_BIT;
    graph<int> g;
    vector<int> sz,    // size of the subtree
    depth, // depth of the node
    dist,  // distance from the initial root
    tree,  // centroid tree(tree[i] = parent of i at the centroid tree)
    S, T, E;  // Euler Tour
    vector<vector<int>> parent;

    int dfs(int u, int p) {
        sz[u] = 1;
        for (const auto& [v, w]: g[u]) {
            if (v == p) continue;
            sz[u] += dfs(v, u);
        }
        return sz[u];
    }

    int get_centroid(int u) {
        for (const auto& [v, w]: g[u]) {
            if (sz[u] >> 1 < sz[v] && sz[v] < sz[u]) {
                sz[u] -= sz[v];
                sz[v] += sz[u];
                return get_centroid(v);
            }
        }
        return u;
    }

    vector<ll> cnt; // cnt[i] = # of paths with length of i
    vector<ll> sub; // sub[i] = # of nodes that are i away from the u(centroid)
    vector<ll> acc; // acc[i] = accumulated sum of sub
    int max_depth;  // max depth of the subtree
    void solve(int u) {
        u = get_centroid(u);
        acc.assign(1, 1);
        acc.reserve(sz[u] + 1);
        for (const auto& [v, _]: g[u]) {
            if (sz[v] > sz[u]) continue;
            sub.clear();
            sub.resize(sz[v] + 1);
            max_depth = 0;

            update_sub(v, 1);

            auto mul = convolution(sub, acc);
            for (int i = 1; i < mul.size(); i++) cnt[i] += mul[i];

            if (acc.size() <= max_depth) acc.resize(max_depth + 1);
            for (int i = 0; i <= max_depth; i++) acc[i] += sub[i];
        }

        for (const auto& [v, _]: g[u]) if (sz[v] < sz[u]) solve(v);
    }

    void update_sub(int u, int d) {
        max_depth = max(max_depth, d);
        sub[d]++;
        for (const auto& [v, _]: g[u]) {
            if (sz[v] > sz[u]) continue;
            update_sub(v, d + 1);
        }
    }

public:
    explicit
    CentroidTree(const graph<int>& g, int root = 1) : g(g), n((int)g.size()), root(root) {
        sz.resize(n, 0);

        dfs(root, -1);

        cnt.resize(n, 0);
        sub.reserve(n);
    }

    lld query() {
        solve(1);
        auto primes = prime_sieve(n - 1);
        lld ans = 0;
        for (const auto& p : primes) ans += cnt[p];
        return ans / (ll(n - 1) * (n - 2) / 2);
    }

}; // class CentroidTree

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }

    CentroidTree solver(g);

    cout << fixed << setprecision(10);
    cout << solver.query() << endl;

    return 0;
}