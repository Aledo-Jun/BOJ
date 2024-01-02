#include <vector>

using namespace std;

namespace math_utils {

    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    const int MOD = 1'000'000'007;

    int pow_mod(int a, int pow) {
        int base = a;
        int res = 1;
        while (pow > 0) {
            if (pow & 1) {
                res = (1LL * res * base) % MOD;
            }
            base = (1LL * base * base) % MOD;
            pow >>= 1;
        }
        return res;
    }

    int factorial_mod(int n) {
        int res = 1;
        for (int i = 1; i <= n; i++) {
            res = (1LL * res * i) % MOD;
        }
        return res;
    }

    int _binomial_coefficient(int n, int k) {
        // Calculate n! / (k! * (n-k)!)
        int numerator = factorial_mod(n);
        int denominator = (1LL * factorial_mod(k) * factorial_mod(n - k)) % MOD;

        int denominator_inverse = pow_mod(denominator, MOD - 2);

        int result = (1LL * numerator * denominator_inverse) % MOD;
        return result;
    }

    // Calculate the binomial coefficient using Lucas' theorem
    int binomial_coefficient(int n, int k) {
        int result = 1;
        while (n > 0 && k > 0){
            int n_remain = n % MOD;
            int k_remain = k % MOD;
            n /= MOD;
            k /= MOD;
            if (n_remain < k_remain) {
                result = 0;
                break;
            }
            result = (result * binomial_coefficient(n_remain, k_remain)) % MOD;
        }
        return result;
    }

    // Calculate the sum of the geometric series from r^0 to r^n recursively
    int geometric_sum(int r, int n){
        if (n == 0) return 1;
        if (n == 1) return (r + 1) % MOD;
        if (n % 2 == 0)
            return (1LL * geometric_sum(r, n / 2 - 1) * (1 + pow_mod(r, n / 2)) % MOD + pow_mod(r, n)) % MOD;
        return (1LL * geometric_sum(r, n / 2) * (1 + pow_mod(r, n / 2 + 1))) % MOD;
    }

    // Matrix size
    const int SIZE = 2;
    template<typename T> using matrix = vector<vector<T>>;

    // Matrix multiplication operation
    template<typename T,
            typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
    void multiply(matrix<T> &A, matrix<T> &B) {
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
            typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
    void matrixPow(matrix<T> &A, int n) {
        matrix<T> result(SIZE, vector<T>(SIZE, 0));
        for (int i = 0; i < SIZE; i++)
            result[i][i] = 1; // Identity matrix

        while (n > 0) {
            if (n & 1) {
                multiply(result, A);
            }

            multiply(A, A);
            n >>= 1;
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                A[i][j] = result[i][j];
            }
        }
    }

    int fib(int n){
        if (n == 0) return 0;
        if (n == 1) return 1;

        matrix<int> A = {{1, 1},
                         {1, 0}};
        matrixPow(A, n - 1);

        return A[0][0];
    }

    int subtract(int a, int b) {
        return (a - b + MOD) % MOD;
    }
    int multiply(int a, int b) {
        return ((long long)a * b) % MOD;
    }

    int modularDeterminant(vector<vector<int>> &mat) {
        int n = mat.size();
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
                det = multiply(det, -1);  // Swap rows, so negate the determinant
            }

            // Reduce to row echelon form
            int pivotElement = mat[i][i];
            int pivotInverse = pow_mod(pivotElement, MOD - 2);

            for (int j = i + 1; j < n; j++) {
                int factor = multiply(mat[j][i], pivotInverse);
                for (int k = i; k < n; k++) {
                    mat[j][k] = subtract(mat[j][k], multiply(mat[i][k], factor));
                }
            }

            // Update determinant
            det = multiply(det, pivotElement);
        }

        return det;
    }

    int count_factors(int n, int p){
        int res = 0;

        for (int i = p; n / i >= 1; i *= p){
            res += n / i;
        }

        return res;
    }

    vector<int> prime_sieve(int n){
        vector<bool> is_prime = vector<bool>(n+1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; i++){
            if (is_prime[i]){
                for (int j = i * i; j <= n; j += i){
                    is_prime[j] = false;
                }
            }
        }
        vector<int> sieve;
        for (int i = 2; i <= n; i++){
            if (is_prime[i])
                sieve.push_back(i);
        }
        return sieve;
    }

    // Function to check if the given number is prime
    // It uses the fact that every prime number larger than 5 is
    // in the form of 6k - 1 or 6k + 1
    bool isPrime(int n){
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6){
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    // Count the number of positive integers less than or equal to n
    // that are coprime with n, using Euler's totient function.
    int phi(int n){
        int res = n;

        for (int p = 2; p * p <= n; p++){
            if (n % p == 0){
                while (n % p == 0)
                    n /= p;

                res -= res / p;
            }
        }

        if (n > 1)
            res -= res / n;

        return res;
    }

}// End math_utils

