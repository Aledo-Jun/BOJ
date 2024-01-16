//
// Created by june0 on 2024-01-13.
//
// ref) https://restudycafe.tistory.com/563
//      https://tistory.joonhyung.xyz/6
//      https://www.acmicpc.net/source/share/da09a901e36d4f1b820d88128e09c1db
//

#ifndef BOJ_FFT_HPP
#define BOJ_FFT_HPP
#include <complex>
#include <vector>
using namespace std;

namespace FFT {
    using base = std::complex<long double>;
    const long double PI = M_PI;

    void _fft(std::vector<base> &_v, bool _is_inv){
        int n = (int) _v.size();
        for (int i = 1, j = 0; i < n; i++){
            int _bit = n >> 1;
            // while (j >= _bit){
            //     j -= _bit;
            //     _bit /= 2;
            // }
            while (!((j ^= _bit) & _bit)) _bit >>= 1;
            if (i < j) std::swap(_v[i], _v[j]);
        }
        for (int i = 1; i < n; i <<= 1){
            long double x = _is_inv ? PI / i : -PI / i;
            base w = {cos(x), sin(x)};
            for (int j = 0; j < n; j += i << 1){
                base z = {1, 0};
                for (int k = 0; k < i; k++){
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
        if (_is_inv){
            for (auto& z : _v) z /= n;
        }
    }

    void fft(std::vector<base> &_v){
        _fft(_v, false);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    vector<base> fft(std::vector<T> &v){
        std::vector<base> _v(v.begin(), v.end());
        _fft(_v, false);
        return _v;
    }

    void inv_fft(std::vector<base> &_v){
        _fft(_v, true);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    vector<base> inv_fft(std::vector<T> &v){
        std::vector<base> _v(v.begin(), v.end());
        _fft(_v, true);
        return _v;
    }

    std::vector<base> _naive_convolution(const std::vector<base> &_a,
                                         const std::vector<base> &_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        std::vector<base> res(n + m - 1);
        if (n < m){
            for (int j = 0; j < m; j++){
                for (int i = 0; i < n; i++){
                    res[i + j] += _a[i] * _b[j];
                }
            }
        } else {
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    res[i + j] += _a[i] * _b[j];
                }
            }
        }
        return res;
    }

    std::vector<base> _fft_convolution(std::vector<base> &_a,
                                       std::vector<base> &_b){
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
        return _a;
    }

    std::vector<base> _convolution(std::vector<base> &&_a,
                                   std::vector<base> &&_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    std::vector<base> _convolution(std::vector<base> &_a,
                                   std::vector<base> &_b){
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    std::vector<T> convolution(const std::vector<T> &a,
                               const std::vector<T> &b){
        int n = (int) a.size();
        int m = (int) b.size();
        if (n == 0 || m == 0) return {};

        std::vector<base> _a(a.begin(), a.end()), _b(b.begin(), b.end());
        auto conv = _convolution(std::move(_a), std::move(_b));

        std::vector<T> res(n + m - 1);
        if (is_floating_point_v<T>) {
            for (int i = 0; i < n + m - 1; i++)
                res[i] = conv[i].real();
        } else {
            for (int i = 0; i < n + m - 1; i++)
                res[i] = std::round(conv[i].real());
        }

        return res;
    }
} // namespace FFT


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
    void ntt(std::vector<T> &v){
        _ntt(v, false);
    }

    template<typename T,
            std::enable_if_t<!std::is_floating_point_v<T>>* = nullptr,
            std::enable_if_t<std::is_integral_v<T>>* = nullptr>
    void inv_ntt(std::vector<T> &v){
        _ntt(v, true);
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
} // namespace NTT

#endif //BOJ_FFT_HPP