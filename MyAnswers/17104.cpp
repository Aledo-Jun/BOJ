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
            int len = 2;
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

    namespace Math {
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
            for (int i = 3; i <= n; i++) {
                if (is_prime[i])
                    sieve.push_back(i);
            }
            return sieve;
        }
    } // namespace Math
} // namespace Utils

using namespace Utils::FFT;
using namespace Utils::Math;
using cpx = complex<double>;

const int MAX_N = 1'000'000;

// Used some trick that every odd prime can be represented as 2*a + 1.
// This fact makes given n can be denoted as n = p + q = 2(a + b + 1) = 2*k.
// So for any primes p and q, except 2, a = (p - 1) / 2, b = (q - 1) / 2.
// Therefore, what we do here is to count the number of a, b pairs
// s.t. a + b = k - 1 = n / 2 - 1
// note : n = 4 = 2 + 2 is a special case.

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    auto primes = prime_sieve(MAX_N); // except 2
    vector<cpx> a(MAX_N / 2 + 1, 0), b(MAX_N / 2 + 1, 0);
    for (const auto& p : primes) {
        a[(p - 1) / 2] = b[(p - 1) / 2] = 1;
    }
    _fft_convolution(a, b);
    while (t--) {
        int n;
        cin >> n;
        if (n == 4) {
            cout << 1 << endl;
            continue;
        }
        ll ans = ceil(round(a[n / 2 - 1].real()) / 2);
        cout << ans << endl;
    }

    return 0;
}

#ifdef ANOTHER_SOLUTION
// Actually this problem can be solved using only one fft (not two) as below.
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

        void _fft_convolution(std::vector<base> &_a) {
            int n = (int) _a.size();
            int len = 2;
            while (len < n + n) len <<= 1;

            _a.resize(len);
            _fft(_a, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _a[i];

            _fft(_a, true);
        }
    } // namespace FFT

    namespace Math {
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
            for (int i = 3; i <= n; i++) {
                if (is_prime[i])
                    sieve.push_back(i);
            }
            return sieve;
        }
    } // namespace Math
} // namespace Utils

using namespace Utils::FFT;
using namespace Utils::Math;
using cpx = complex<double>;

const int MAX_N = 1'000'000;

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    auto primes = prime_sieve(MAX_N); // except 2
    vector<cpx> a(MAX_N + 1, 0);
    vector<int> c(MAX_N * 2 + 1, 0);
    for (const auto& p : primes) a[p] += 1, c[p * 2] += 1;
    _fft_convolution(a);
    while (t--) {
        int n;
        cin >> n;
        if (n == 4) {
            cout << 1 << endl;
            continue;
        }
        ll ans = round(a[n].real());
        ll tmp = c[n];
        cout << (ans - tmp) / 2 + tmp << endl;
    }

    return 0;
}
#endif // ANOTHER_SOLUTION