//
// Created by june0 on 2024-01-19.
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

namespace Utils
{
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
        void _fft_convolution(std::vector<base> &_a,
                              std::vector<base> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            int len = 1;
            while (len < n + m) len <<= 1;

            _a.resize(len);
            _fft(_a, false);
            _b.resize(len);
            _fft(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fft(_a, true);
        }
    } // namespace FFT

} // namespace Utils

using namespace Utils::FFT;
using cpx = complex<double>;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<cpx> a(n, 0), b(n, 0);
    vector<int> sq(n);
    vector<ll> c(n, 0); /// Fxxk multi-set
    for (ll i = 1; i < n; i++){
        a[(i * i) % n] += 1;
        b[(i * i) % n] += 1;
        c[(2 * i * i) % n]++;
        sq[i] = (i * i) % n;
    }
    _fft_convolution(a, b);
    vector<ll> res(n, 0);
    for (int i = 0; i < n + n - 1; i++)
        res[i % n] += std::round(a[i].real());

    ull ans = 0, rep = 0;
    for (int i = 1; i < n; i++) {
        ans += res[sq[i]];
        rep += c[sq[i]];
    }
    cout << (ans - rep) / 2 + rep;
    return 0;
}