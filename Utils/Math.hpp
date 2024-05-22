#ifndef BOJ_MATH_HPP
#define BOJ_MATH_HPP

#include <vector>
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

    constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
        a = safe_mod(a, b);
        if (a == 0) return {b, 0};

        long long s = b, t = a;
        long long m0 = 0, m1 = 1;

        while (t) {
            long long u = s / t;
            s -= t * u;
            m0 -= m1 * u;

            auto tmp = s;
            s = t;
            t = tmp;
            tmp = m0;
            m0 = m1;
            m1 = tmp;
        }
        if (m0 < 0) m0 += b / s;
        return {s, m0};
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

    int factorial_mod(int n, int MOD) {
        int res = 1;
        for (int i = 1; i <= n; i++) {
            res = (int) (1LL * res * i) % MOD;
        }
        return res;
    }

    int _binomial_coefficient(int n, int k, int MOD) {
        // Calculate n! / (k! * (n-k)!)
        int numerator = factorial_mod(n, MOD);
        int denominator = (int) (1ULL * factorial_mod(k, MOD) * factorial_mod(n - k, MOD)) % MOD;

        int denominator_inverse = pow_mod(denominator, MOD - 2, MOD);

        int result = (int) (1ULL * numerator * denominator_inverse) % MOD;
        return result;
    }

    // Calculate the binomial coefficient using Lucas' theorem
    int binomial_coefficient(int n, int k, int MOD) {
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
            result = (result * binomial_coefficient(n_remain, k_remain, MOD)) % MOD;
        }
        return result;
    }

    // Calculate the sum of the geometric series from r^0 to r^n recursively
    int geometric_sum(int r, int n, int MOD) {
        if (n == 0) return 1;
        if (n == 1) return (r + 1) % MOD;
        if (n % 2 == 0)
            return (int) (1LL * geometric_sum(r, n / 2 - 1, MOD) * (1 + pow_mod(r, n / 2, MOD)) % MOD + pow_mod(r, n, MOD)) % MOD;
        return (int) (1LL * geometric_sum(r, n / 2, MOD) * (1 + pow_mod(r, n / 2 + 1, MOD))) % MOD;
    }

    /// TODO: Make own Matrix class
    // Matrix size
    const int SIZE = 2;
    template<typename T> using matrix = vector<vector<T>>;

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

    int fib(int n, int MOD) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        matrix<int> A = {{1, 1},
                         {1, 0}};
        matrixPow(A, n - 1, MOD);

        return A[0][0];
    }

    int subtract(int a, int b, int MOD) {
        return (a - b + MOD) % MOD;
    }

    int multiply(int a, int b, int MOD) {
        return (int) ((long long) a * b) % MOD;
    }

    int modularDeterminant(matrix<int> &mat, int MOD) {
        int n = (int) mat.size();
        int det = 1;

        for (int i = 0; i < n; i++) {
            // Find pivot element and swap rows if necessary
            int pivot = -1;
            for (int j = i; j < n; j++) {
                if (mat[j][i] != 0) {
                    pivot = j;
                    break;
                }
            }
            if (pivot == -1)
                return 0;  // Matrix is singular

            if (pivot != i) {
                swap(mat[i], mat[pivot]);
                det = multiply(det, -1, MOD);  // Swap rows, so negate the determinant
            }

            // Reduce to row echelon form
            int pivotElement = mat[i][i];
            int pivotInverse = pow_mod(pivotElement, MOD - 2, MOD);

            for (int j = i + 1; j < n; j++) {
                int factor = multiply(mat[j][i], pivotInverse, MOD);
                for (int k = i; k < n; k++) {
                    mat[j][k] = subtract(mat[j][k], multiply(mat[i][k], factor, MOD), MOD);
                }
            }

            // Update determinant
            det = multiply(det, pivotElement, MOD);
        }

        return det;
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