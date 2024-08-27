#ifndef BOJ_MATH_HPP
#define BOJ_MATH_HPP

#include <vector>
#include <array>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

namespace Utils::Math {
    constexpr long long safe_mod(long long x, long long m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }

    constexpr long long gcd(long long a, long long b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    // returns {x,y,g} s.t. ax + by = g = gcd(a,b) >=0.
    constexpr std::array<long long,3> ext_gcd(long long a, long long b) {
        long long x = 1, y = 0;
        long long z = 0, w = 1;
        while (b) {
            long long p = a / b, q = a % b;
            x -= y * p, std::swap(x, y);
            z -= w * p, std::swap(z, w);
            a = b, b = q;
        }
        if (a < 0) {
            x = -x, z = -z, a = -a;
        }
        return {x, z, a};
    }

    // returns {x,g} s.t. a * x = g (mod m)
    constexpr std::pair<long long, long long> inv_gcd(long long a, long long MOD) {
        auto [x, y, g] = ext_gcd(a, MOD);
        return {safe_mod(x, MOD), g};
    }

    long long mod_inv(int a, int MOD) {
        auto [x, y, g] = ext_gcd(a, MOD);
        assert(g == 1);
        return safe_mod(x, MOD);
    }

    template<typename T>
    T pow_mod(T a, __int128 pow, __int128 MOD) {
        __int128 base = a;
        __int128 res = 1;
        while (pow > 0) {
            if (pow & 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            pow >>= 1;
        }
        return res;
    }

    array<vector<int>,2> precompute_factorials(int MOD) {
        vector<int> fact(MOD), inv_fact(MOD);
        fact[0] = 1;
        for (int i = 1; i < MOD; i++) fact[i] = fact[i - 1] * i % MOD;
        inv_fact[MOD - 1] = mod_inv(fact[MOD - 1], MOD);
        for (int i = MOD - 2; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;

        return {fact, inv_fact};
    }

    // fact[i] := product of integers i <= p^q && i % p != 0
    array<vector<int>,2> precompute_factorials(int p, int q) {
        int MOD = (int) pow(p, q);
        vector<int> fact(MOD), inv_fact(MOD);
        fact[0] = inv_fact[0] = 1;
        for (int i = 1; i < MOD; i++) {
            if (i % p) fact[i] = fact[i - 1] * i % MOD;
            else fact[i] = fact[i - 1];

            inv_fact[i] = mod_inv(fact[i], MOD);
        }

        return {fact, inv_fact};
    }

    int _binomial_coefficient(int n, int k, int MOD, const vector<int>& fact, const vector<int>& inv_fact) {
        if (k > n) return 0;
        return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
    }

    int Lucas(int n, int k, int MOD, const vector<int>& fact, const vector<int>& inv_fact) {
        int res = 1;
        while (n && k) {
            int n_remain = n % MOD;
            int k_remain = k % MOD;
            if (k_remain > n_remain) return 0;
            res = 1LL * res * _binomial_coefficient(n_remain, k_remain, MOD, fact, inv_fact) % MOD;
            n /= MOD;
            k /= MOD;
        }
        return res;
    }

    /**
     * Generalization of Lucas' Theorem for modulo prime powers p^q
     * (if q == 1, simply use Lucas instead)
     * @return binomial_coefficient(n, k) mod p^q
     * @see https://web.archive.org/web/20170202003812/http://www.dms.umontreal.ca/~andrew/PDF/BinCoeff.pdf Thm.1
     */
    int Lucas_pow_of_prime(int n, int k, int p, int q, const vector<int>& fact, const vector<int>& inv_fact) {
        int MOD = (int) pow(p, q);
        int A = n, B = k, C = n - k;
        vector<int> ai, bi, ci;
        vector<int> Ai, Bi, Ci;
        while (A || B || C) {
            ai.emplace_back(A % p);
            bi.emplace_back(B % p);
            ci.emplace_back(C % p);

            Ai.emplace_back(A % MOD);
            Bi.emplace_back(B % MOD);
            Ci.emplace_back(C % MOD);

            A /= p;
            B /= p;
            C /= p;
        }

        vector<int> e_prefix;
        int carry = 0;
        for (int i = 0; i < ai.size(); i++) {
            int val = bi[i] + ci[i] + carry;
            if (val >= p) {
                carry = 1;
                e_prefix.emplace_back(1);
            } else {
                carry = 0;
                e_prefix.emplace_back(0);
            }
        }
        for (int i = 1; i < e_prefix.size(); i++) e_prefix[i] += e_prefix[i - 1];

        int e0 = e_prefix.back();
        int eq_1 = e0 - e_prefix[q - 2]; // e_(q-1)
        if (p == 2 && q >= 3) eq_1 = 0;

        int res = (int) pow(p, e0) * (eq_1 & 1 ? -1 : 1) % MOD;
        for (int i = 0; i < ai.size(); i++) {
            res = res * fact[Ai[i]] % MOD;
            res = res * inv_fact[Bi[i]] % MOD;
            res = res * inv_fact[Ci[i]] % MOD;
        }
        return (res + MOD) % MOD;
    }

    int factorial_mod(int n, int MOD) {
        int res = 1;
        for (int i = 1; i <= n; i++) {
            res = (int) (1LL * res * i) % MOD;
        }
        return res;
    }

    int binomial_coefficient_naive(int n, int k, int MOD) {
        // Calculate n! / (k! * (n-k)!)
        int numerator = factorial_mod(n, MOD);
        int denominator = (int) (1ULL * factorial_mod(k, MOD) * factorial_mod(n - k, MOD)) % MOD;

        int denominator_inverse = pow_mod(denominator, MOD - 2, MOD);

        int result = (int) (1ULL * numerator * denominator_inverse) % MOD;
        return result;
    }

    // Lucas' theorem for prime MOD
    int Lucas_prime(int n, int k, int MOD) {
        int result = 1;
        while (n > 0 && k > 0) {
            int n_remain = n % MOD;
            int k_remain = k % MOD;
            n /= MOD;
            k /= MOD;
            if (n_remain < k_remain) {
                result = 0;
                break;
            }
            result = (result * Lucas_prime(n_remain, k_remain, MOD)) % MOD;
        }
        return result;
    }

    /**
     * Chinese Remainder Theorem(CRT) implementation
     * @param remainders a_i := remainders[i]
     * @param moduli     p_i := moduli[i]
     * @return the solution of the system of linear congruence
     *        { x = a_i mod p_i }
     */
    int Chinese_remainder_theorem(const std::vector<int>& remainders, const std::vector<int>& moduli) {
        int N = 1;
        for (int mod : moduli) N *= mod;

        int res = 0;
        for (int i = 0; i < moduli.size(); i++) {
            int ai = remainders[i];
            int Ni = N / moduli[i];
            int Mi = mod_inv(Ni, moduli[i]);
            res = (res + 1LL * ai * Mi % N * Ni % N) % N;
        }

        return res;
    }

    // use this for composite modulo
    int binomial_coefficient(int n, int k) {
        // this example is for MOD = 142857 = 27 * 11 * 13 * 37
        vector<int> primes = {27, 11, 13, 37};
        auto [fact27, inv_fact27] = precompute_factorials(3, 3);
        auto [fact11, inv_fact11] = precompute_factorials(11);
        auto [fact13, inv_fact13] = precompute_factorials(13);
        auto [fact37, inv_fact37] = precompute_factorials(37);

        vector<int> remainders(4);
        remainders[0] = Lucas_pow_of_prime(n, k, 3, 3, fact27, inv_fact27);
        remainders[1] = Lucas(n, k, 11, fact11, inv_fact11);
        remainders[2] = Lucas(n, k, 13, fact13, inv_fact13);
        remainders[3] = Lucas(n, k, 37, fact37, inv_fact37);

        return Chinese_remainder_theorem(remainders, primes);
    }

    // Calculate the sum of the geometric series from r^0 to r^n recursively
    int geometric_sum(int r, int n, int MOD) {
        if (n == 0) return 1;
        if (n == 1) return (r + 1) % MOD;
        if (n % 2 == 0)
            return (int) (1LL * geometric_sum(r, n / 2 - 1, MOD) * (1 + pow_mod(r, n / 2, MOD)) % MOD + pow_mod(r, n, MOD)) % MOD;
        return (int) (1LL * geometric_sum(r, n / 2, MOD) * (1 + pow_mod(r, n / 2 + 1, MOD))) % MOD;
    }

    /**
     * Count the number of integer pairs (x,y) s.t. px + qy <= r
     */
    template<typename int_t>
    int_t LatticePointCount(int_t p, int_t q, int_t r) {
        if (p + q > r) return 0;
        if (p < q) swap(p, q);
        int_t Q = p / q, R = p % q;
        int_t t = (Q * r + R) / p;
        int_t t1 = (t - 1) / Q * (2 * t - Q * (1 + (t - 1) / Q)) / 2;
        int_t t2 = LatticePointCount(q, R, r - q * t);
        return t1 + t2;
    }

    /**
     * Calculate sum_{i=1..n}((p * i) // q)
     */
    template<typename int_t>
    int_t FloorSum(int_t p, int_t q, int_t n) {
        int_t res = 0;
        res += p / q * n * (n + 1) / 2;
        p %= q;
        res += LatticePointCount(p, q, p * (n + 1));
        return res;
    }


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

    // Function to check if the given number is prime
    // It uses the fact that every prime number larger than 5 is
    // in the form of 6k - 1 or 6k + 1
    bool is_prime_naive(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    using ull = unsigned long long;

    bool miller_rabin(ull n, ull a) {
        for (ull d = n - 1; ; d >>= 1) {
            ull t = pow_mod(a, d, n);
            if (t == n - 1) return true;
            if (d & 1) return t == 1 || t == n - 1;
        }
        // cannot reach here
    }

    // Figure out the number's primality using Miller-Rabin algorithm
    bool is_prime(ull n) {
        if (n < 2) return false;
        static ull a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // works for n <= 2^64
        for (ull p : a) {
            if (n == p) return true;
            if (n % p == 0) return false;
        }
        for (ull p : a) {
            if (!miller_rabin(n, p)) return false;
        }
        return true;
    }

    // Pollard-rho algorithm to find the prime factor of the given number 'without' order
    ull pollard_rho(__int128 n) {
        if (~n & 1) return 2;
        if (is_prime(n)) return n;

        static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<ull> rand(2, n - 1);
        __int128 x = rand(rng), y = x, c = rand(rng) % 10 + 1;
        __int128 d = 1;
        auto f = [&](__int128 x) { return ((x * x) % n + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = gcd(abs(x - y), n);
            if (d == n) return pollard_rho(d); // resolve possible infinite loop
        }
        if (is_prime(d)) return d;
        return pollard_rho(d);
    }

    // Count the number of positive integers less than or equal to n
    // that are coprime with n, using Euler's totient function.
    int phi_naive(int n) {
        int res = n;

        for (int p = 2; p * p <= n; p++) {
            if (n % p == 0) {
                while (n % p == 0)
                    n /= p;

                res -= res / p;
            }
        }

        if (n > 1)
            res -= res / n;

        return res;
    }

    ull phi(ull n) {
        if (n == 1) return 1;
        ull res = n;
        while (n > 1 && !is_prime(n)) {
            ull factor = pollard_rho(n);
            while (n % factor == 0) n /= factor;
            res -= res / factor;
        }
        if (n > 1) res -= res / n;

        return res;
    }

} // namespace Utils
#endif