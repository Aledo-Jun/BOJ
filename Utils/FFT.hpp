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
#include "Modulo.hpp"
using namespace std;
namespace Utils
{
namespace FFT {
    using base = std::complex<long double>;
    const long double PI = M_PI;

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
            long double x = _is_inv ? PI / i : -PI / i;
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
                                   std::vector<base> &&_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    std::vector<base> _convolution(std::vector<base> &_a,
                                   std::vector<base> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _fft_convolution(_a, _b);
    }

    template<typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    std::vector<T> convolution(const std::vector<T> &a,
                               const std::vector<T> &b) {
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

#ifndef BOJ_MODULO_HPP

namespace NTT
{
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
}// namespace NTT

#else

// NTT using ModInt in Modulo.hpp
namespace NTT
{
    using namespace Math;
    using namespace Modulo;

    template<typename mint, is_modint_t<mint> * = nullptr>
    inline mint pow(mint a, int p) {
        mint res = 1;
        while (p > 0) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }

    template<typename mint,
            int ROOT = primitive_root<mint::mod()>,
            Modulo::is_modint_t<mint> * = nullptr>
    vector<mint> get_roots(int n, bool _is_inv) {
        mint x = pow<mint>(ROOT, (mint::mod() - 1) / n);
        if (_is_inv) x = pow(x, mint::mod() - 2);

        vector<mint> root(n >> 1, 1);
        for (int i = 1; i < (n >> 1); i++) {
            root[i] = root[i - 1] * x;
        }
        return root;
    }

    template<typename mint, is_modint_t<mint> * = nullptr>
    void _ntt(std::vector<mint> &_v, bool _is_inv) {
        int n = (int) _v.size();
        // bit-reversal
        for (int i = 1, j = 0; i < n; i++) {
            int _bit = n >> 1;
            while (!((j ^= _bit) & _bit)) _bit >>= 1;
            if (i < j) std::swap(_v[i], _v[j]);
        }

        static const auto roots = get_roots<mint>(n, _is_inv);
        for (int i = 2; i <= n; i <<= 1) {
            int x = n / i;
            for (int j = 0; j < n; j += i) {
                for (int k = 0; k < (i >> 1); k++) {
                    mint tmp = _v[(i >> 1) + j + k] * roots[x * k];
                    _v[(i >> 1) + j + k] = _v[j + k] - tmp;
                    _v[j + k] += tmp;
                }
            }
        }
        if (_is_inv) {
            mint n_inv = mint(n).inv();
            for (auto &z: _v) z *= n_inv;
        }
    }

    template<typename T, is_modint_t<T> * = nullptr>
    void ntt(std::vector<T> &v) {
        _ntt(v, false);
    }

    template<int MOD = 998244353,
            typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    auto ntt(std::vector<T> &v) {
        using mint = ModInt<MOD>;
        vector<mint> _v(v.begin(), v.end());
        _ntt(_v, false);
        return _v;
    }

    template<typename T, is_modint_t<T> * = nullptr>
    void inv_ntt(std::vector<T> &v) {
        _ntt(v, true);
    }

    template<int MOD = 998244353,
            typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    auto inv_ntt(std::vector<T> &v) {
        using mint = ModInt<MOD>;
        vector<mint> _v(v.begin(), v.end());
        _ntt(_v, true);
        return _v;
    }

    template<typename mint, is_modint_t<mint> * = nullptr>
    std::vector<mint> _naive_convolution(const std::vector<mint> &_a,
                                         const std::vector<mint> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        std::vector<mint> res(n + m - 1);
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

    template<typename mint, is_modint_t<mint> * = nullptr>
    std::vector<mint> _ntt_convolution(std::vector<mint> &_a,
                                       std::vector<mint> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        int len = 1;
        while (len < (n + m)) len <<= 1;

        _a.resize(len);
        _ntt(_a, false);
        _b.resize(len);
        _ntt(_b, false);

        for (int i = 0; i < len; i++)
            _a[i] *= _b[i];

        _ntt(_a, true);
        return _a;
    }

    template<typename mint, is_modint_t<mint> * = nullptr>
    std::vector<mint> _convolution(std::vector<mint> &&_a,
                                   std::vector<mint> &&_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _ntt_convolution(_a, _b);
    }

    template<typename mint, is_modint_t<mint> * = nullptr>
    std::vector<mint> _convolution(std::vector<mint> &_a,
                                   std::vector<mint> &_b) {
        int n = (int) _a.size();
        int m = (int) _b.size();
        if (n == 0 || m == 0) return {};
        if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
        return _ntt_convolution(_a, _b);
    }
    template<int MOD = 998244353,
            typename T,
            std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    std::vector<T> convolution(const std::vector<T> &a,
                               const std::vector<T> &b) {
        int n = (int) a.size();
        int m = (int) b.size();
        if (n == 0 || m == 0) return {};

        using mint = ModInt<MOD>;

        std::vector<mint> _a(a.begin(), a.end()), _b(b.begin(), b.end());
        auto conv = _convolution(std::move(_a), std::move(_b));

        std::vector<T> res(n + m - 1);
        for (int i = 0; i < n + m - 1; i++)
            res[i] = conv[i].value();

        return res;
    }

    // TODO: search for Chinese Remainder Theorem(CRT)
    std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                          const std::vector<long long>& b) {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m) return {};

        static constexpr unsigned long long MOD1 = 754974721;  // 2^24
        static constexpr unsigned long long MOD2 = 167772161;  // 2^25
        static constexpr unsigned long long MOD3 = 469762049;  // 2^26
        static constexpr unsigned long long M2M3 = MOD2 * MOD3;
        static constexpr unsigned long long M1M3 = MOD1 * MOD3;
        static constexpr unsigned long long M1M2 = MOD1 * MOD2;
        static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

        static constexpr unsigned long long i1 =
                inv_gcd(MOD2 * MOD3, MOD1).second;
        static constexpr unsigned long long i2 =
                inv_gcd(MOD1 * MOD3, MOD2).second;
        static constexpr unsigned long long i3 =
                inv_gcd(MOD1 * MOD2, MOD3).second;

        static constexpr int MAX_AB_BIT = 24;
        static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1, "MOD1 isn't enough to support an array length of 2^24.");
        static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1, "MOD2 isn't enough to support an array length of 2^24.");
        static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1, "MOD3 isn't enough to support an array length of 2^24.");
        assert(n + m - 1 <= (1 << MAX_AB_BIT));

        auto c1 = convolution<MOD1>(a, b);
        auto c2 = convolution<MOD2>(a, b);
        auto c3 = convolution<MOD3>(a, b);

        std::vector<long long> c(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            unsigned long long x = 0;
            x += (c1[i] * i1) % MOD1 * M2M3;
            x += (c2[i] * i2) % MOD2 * M1M3;
            x += (c3[i] * i3) % MOD3 * M1M2;
            // B = 2^63, -B <= x, r(real value) < B
            // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
            // r = c1[i] (mod MOD1)
            // focus on MOD1
            // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
            // r = x,
            //     x - M' + (0 or 2B),
            //     x - 2M' + (0, 2B or 4B),
            //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
            // (r - x) = 0, (0)
            //           - M' + (0 or 2B), (1)
            //           -2M' + (0 or 2B or 4B), (2)
            //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
            // we checked that
            //   ((1) mod MOD1) mod 5 = 2
            //   ((2) mod MOD1) mod 5 = 3
            //   ((3) mod MOD1) mod 5 = 4
            long long diff =
                    c1[i] - safe_mod((long long)(x), (long long)(MOD1));
            if (diff < 0) diff += MOD1;
            static constexpr unsigned long long offset[5] = {
                    0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
            x -= offset[diff % 5];
            c[i] = x;
        }

        return c;
    }
} // namespace NTT using ModInt
#endif

} // namespace Utils
#endif //BOJ_FFT_HPP