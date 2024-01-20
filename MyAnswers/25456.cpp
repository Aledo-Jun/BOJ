//
// Created by june0 on 2024-01-20.
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
        void _naive_convolution(std::vector<base> &_a,
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
            _a = res;
        }

        void _fft_convolution(std::vector<base> &_a,
                              std::vector<base> &_b) {
            int n = (int) _a.size(), m = (int) _b.size();
            int len = 2;
            while (len < n + m) len <<= 1;

            _a.resize(len);
            _fft(_a, false);
            _b.resize(len);
            _fft(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fft(_a, true);
            _a.resize(n + m - 1);
        }
        void _convolution(std::vector<base> &&_a,
                          std::vector<base> &&_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) {
                return _naive_convolution(_a, _b);
            }
            return _fft_convolution(_a, _b);
        }

        void _convolution(std::vector<base> &_a,
                          std::vector<base> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) {
                _naive_convolution(_a, _b);
                return;
            }
            _fft_convolution(_a, _b);
        }

        template<typename T,
                std::enable_if_t<std::is_integral_v<T>> * = nullptr>
        std::vector<T> convolution(const std::vector<T> &a,
                                   const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            std::vector<base> _a(a.begin(), a.end()), _b(b.begin(), b.end());
            _convolution((_a), (_b)); // using std::move is slower somehow

            std::vector<T> res(n + m - 1);
            if (is_floating_point_v<T>) {
                for (int i = 0; i < n + m - 1; i++)
                    res[i] = _a[i].real();
            } else {
                for (int i = 0; i < n + m - 1; i++)
                    res[i] = std::round(_a[i].real());
            }

            return res;
        }
    } // namespace FFT

    namespace Math {

    } // namespace Math
} // namespace Utils

using namespace Utils::FFT;
using namespace Utils::Math;
using cpx = complex<double>;

int32_t main() {
    fastIO;
    string s, t;
    cin >> s >> t;
    int n = s.length();
    vector<int> a(n * 2), b(n);
    for (int i = 0; i < n; i++){
        a[i] = a[n + i] = s[i] - '0';
        b[n - 1 - i] = t[i] - '0';
    }
    auto res = convolution(a, b);
    cout << *max_element(res.begin(), res.end());

    return 0;
}