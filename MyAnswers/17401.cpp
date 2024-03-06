//
// Created by june0 on 2024-03-06.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

//
/// "Premature optimization is the root of all evil." -- Donald Knuth
//
namespace Matrix {
    template<typename T, typename = void>
    struct supports_arithmetic : public std::false_type { };

    template<typename T>
    struct supports_arithmetic<T,
            void_t<decltype(std::declval<T>() + std::declval<T>()),
                    decltype(std::declval<T>() - std::declval<T>()),
                    decltype(std::declval<T>() * std::declval<T>()),
                    decltype(std::declval<T>() / std::declval<T>())>>
            : public std::true_type { };

    struct matrix_base { };

    template<typename T>
    using is_matrix = std::is_base_of<matrix_base, T>;

    template<typename T>
    using is_matrix_t = std::enable_if_t<is_matrix<T>::value>;

    struct matrix_shape {
        int n_rows, n_cols;

        bool operator==(const matrix_shape &other) const {
            return (n_rows == other.n_rows) && (n_cols == other.n_cols);
        }

        bool operator!=(const matrix_shape &other) const { return !(*this == other); }
    };

    /**
     * @brief Static Matrix class that uses fixed-size array for its storage
     * @tparam T  Value type, must support arithmetic operations(+, -, *, /)
     * @tparam n_rows Number of rows, must be positive
     * @tparam n_cols Number of columns, must be positive
     */
    template<typename T,
            int n_rows,
            int n_cols,
            std::enable_if_t<supports_arithmetic<T>::value && 0 < n_rows && 0 < n_cols> * = nullptr>
    class StaticMatrix : matrix_base {
        using value_type = T;

    private:
        T Data[n_rows][n_cols];

        static constexpr matrix_shape _shape{n_rows, n_cols};

    public:
        [[nodiscard]]
        static constexpr matrix_shape shape() { return _shape; }

        static constexpr int get_n_rows() { return n_rows; }

        static constexpr int get_n_cols() { return n_cols; }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        static constexpr StaticMatrix identity() {
            StaticMatrix result;
            for (int i = 0; i < n_rows; i++) result[i][i] = value_type(1);
            return result;
        }

        ////////////////////////////////
        // Constructors
        ////////////////////////////////

        StaticMatrix() = default;

        template<typename U>
        explicit StaticMatrix(const std::vector<std::vector<U>> &data) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < data[i].size(); j++) {
                    Data[i][j] = value_type(data[i][j]);
                }
                for (int j = data[i].size(); j < n_cols; j++) {
                    Data[i][j] = value_type(0);
                }
            }
        }

        StaticMatrix(initializer_list<initializer_list<value_type>> data) {
            auto row = data.begin();
            for (int i = 0; i < n_rows && row != data.end(); i++, row++) {
                auto _cur = std::begin(Data[i]);
                auto _first = row->begin();
                auto _last = row->end();
                for (; _first != _last && _cur != std::end(Data[i]); _cur++, _first++) {
                    *_cur = *_first;
                }
                for (; _cur != std::end(Data[i]); _cur++) *_cur = value_type(0);
            }
            for (int i = data.size(); i < n_rows; i++) {
                std::fill(std::begin(Data[i]), std::end(Data[i]), value_type(0));
            }
        }

        ////////////////////////////////////////
        // Operators
        ////////////////////////////////////////

        // Subscription operator
        value_type *operator[](int idx) {
            return Data[idx];
        }

        const value_type *operator[](int idx) const {
            return Data[idx];
        }

        // Unary plus
        StaticMatrix operator+() {
            return *this;
        }

        // Unary minus
        StaticMatrix operator-() {
            StaticMatrix result;
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    result[i][j] = -this->Data[i][j];
                }
            }
            return result;
        }

        // StaticMatrix + StaticMatrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t <MatrixType> * = nullptr,
                is_matrix_t <MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == MatrixType2::get_n_rows() &&
                                 MatrixType::get_n_cols() == MatrixType2::get_n_cols()> * = nullptr>
        friend MatrixType
        operator+(const MatrixType &a, const MatrixType2 &b) {
            MatrixType result;
            int rows = MatrixType::get_n_rows();
            int cols = MatrixType::get_n_cols();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    result[i][j] = a[i][j] + b[i][j];
                }
            }
            return result;
        }

        // StaticMatrix += StaticMatrix
        template<class MatrixType,
                is_matrix_t <MatrixType> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == n_rows &&
                                 MatrixType::get_n_cols() == n_cols> * = nullptr>
        StaticMatrix operator+=(const MatrixType &rhs) {
            return *this = (*this + rhs);
        }

        // StaticMatrix - StaticMatrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t <MatrixType> * = nullptr,
                is_matrix_t <MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == MatrixType2::get_n_rows() &&
                                 MatrixType::get_n_cols() == MatrixType2::get_n_cols()> * = nullptr>
        friend MatrixType
        operator-(const MatrixType &a, const MatrixType2 &b) {
            return a + (-b);
        }

        // StaticMatrix -= StaticMatrix
        template<class MatrixType,
                is_matrix_t <MatrixType> * = nullptr,
                std::enable_if_t<MatrixType::get_n_rows() == n_rows &&
                                 MatrixType::get_n_cols() == n_cols> * = nullptr>
        StaticMatrix operator-=(const MatrixType &rhs) {
            return *this = (*this - rhs);
        }

        // StaticMatrix * StaticMatrix
        template<class MatrixType,
                class MatrixType2,
                is_matrix_t <MatrixType> * = nullptr,
                is_matrix_t <MatrixType2> * = nullptr,
                std::enable_if_t<MatrixType::get_n_cols() == MatrixType2::get_n_rows()> * = nullptr>
        friend auto
        operator*(const MatrixType &a, const MatrixType2 &b) {
            StaticMatrix<typename MatrixType::value_type,
                    MatrixType2::get_n_rows(),
                    MatrixType::get_n_cols()> result;
            int rows = MatrixType2::get_n_rows();
            int cols = MatrixType::get_n_cols();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    result[i][j] = value_type(0);
                    for (int k = 0; k < rows; ++k) {
                        result[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
            return result;
        }

        // StaticMatrix *= StaticMatrix
        template<class MatrixType,
                is_matrix_t <MatrixType> * = nullptr,
                std::enable_if_t<n_cols == MatrixType::get_n_rows()> * = nullptr>
        StaticMatrix operator*=(const MatrixType &rhs) {
            return *this = (*this * rhs);
        }

        // StaticMatrix + scalar
        template<typename S,
                std::enable_if_t<std::is_scalar_v<S>> * = nullptr>
        StaticMatrix operator+(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] += scalar;
                }
            }
        }

        // StaticMatrix - scalar
        template<typename S>
        StaticMatrix operator-(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] -= scalar;
                }
            }
        }

        // StaticMatrix * scalar
        template<typename S,
                std::enable_if_t<!is_matrix<S>::value> * = nullptr>
        StaticMatrix operator*(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] *= scalar;
                }
            }
        }

        // StaticMatrix / scalar
        template<typename S>
        StaticMatrix operator/(S scalar) {
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    this->Data[i][j] /= scalar;
                }
            }
        }

        // StaticMatrix += scalar
        template<typename S>
        StaticMatrix operator+=(S scalar) {
            return *this = (*this + scalar);
        }

        // StaticMatrix -= scalar
        template<typename S>
        StaticMatrix operator-=(S scalar) {
            return *this = (*this - scalar);
        }

        // StaticMatrix *= scalar
        template<typename S,
                std::enable_if_t<std::is_scalar_v<S>> * = nullptr>
        StaticMatrix operator*=(S scalar) {
            return *this = (*this * scalar);
        }

        // StaticMatrix /= scalar
        template<typename S>
        StaticMatrix operator/=(S scalar) {
            return *this = (*this / scalar);
        }

        // StaticMatrix == StaticMatrix
        template<class MatrixType,
                is_matrix_t <MatrixType> * = nullptr>
        bool operator==(const StaticMatrix &rhs) const {
            if (this->shape() != rhs.shape()) return false;
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    if (this->Data[i][j] != rhs[i][j]) return false;
                }
            }
            return true;
        }

        friend std::ostream& operator<<(std::ostream& out, const StaticMatrix& m){
            for (int i = 0; i < m.get_n_rows(); i++) {
                for (int j = 0; j < m.get_n_cols(); j++)
                    out << m[i][j] << ' ';
                out << '\n';
            }
            out << flush;
            return out;
        }

        ////////////////////////////////////////////////////////////////
        // Mathematical operations
        ////////////////////////////////////////////////////////////////

        StaticMatrix<value_type, n_cols, n_rows>
        transpose() {
            StaticMatrix<value_type, n_cols, n_rows> result;
            for (int i = 0; i < n_rows; i++) {
                for (int j = 0; j < n_cols; j++) {
                    result[j][i] = this->Data[i][j];
                }
            }
            return result;
        }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        std::size_t trace() {
            std::size_t result = 0;
            for (int i = 0; i < n_rows; i++) result += this->Data[i][i];
            return result;
        }

        template<std::enable_if_t<n_rows == n_cols> * = nullptr>
        std::size_t determinant() {
            throw std::runtime_error("Not implemented");
            // TODO: move implementation from Math.hpp
        }
    }; // class StaticMatrix

    template<typename T>
    struct is_square_matrix : std::false_type { };

    template<typename T, int n_rows, int n_cols>
    struct is_square_matrix<StaticMatrix<T, n_rows, n_cols>>
            : std::conditional<n_rows == n_cols, std::true_type, std::false_type>::type { };

    template<typename T>
    using is_square_matrix_t = std::enable_if_t<is_square_matrix<T>::value>;

    template<class MatrixType,
            is_square_matrix_t<MatrixType> * = nullptr>
    MatrixType pow(const MatrixType& a, int n){
        MatrixType base = a;
        MatrixType result = MatrixType::identity();
        while (n) {
            if (n & 1) result *= base;
            base *= base;
            n >>= 1;
        }
        return result;
    }
} // namespace StaticMatrix
namespace Modulo {
    struct modint_base { };

    template<typename T>
    using is_modint = std::is_base_of<modint_base, T>;
    template<typename T>
    using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    template<typename T>
    using is_signed_int =
            typename std::conditional_t<std::is_integral_v<T> && std::is_signed_v<T>,
                    std::true_type,
                    std::false_type>;

    template<typename T>
    using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

    template<typename T>
    using is_unsigned_int =
            typename std::conditional_t<std::is_integral_v<T> && std::is_unsigned_v<T>,
                    std::true_type,
                    std::false_type>;

    template<typename T>
    using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

    /**
     * an Integer type that modular arithmetic is automatically applied
     * @tparam MOD the modulus that will be applied to the value
     */
    template<unsigned long long MOD,
            enable_if_t<(MOD >= 1)> * = nullptr>
    class ModInt : modint_base {
        using mint = ModInt;

    private:
        unsigned long long _v;

        static constexpr unsigned long long _umod() { return MOD; }

    public:
        static constexpr unsigned long long mod() { return MOD; }

        [[nodiscard]]
        unsigned long long value() const { return _v; }

        [[nodiscard]]
        mint pow(unsigned long long n) const {
            mint base = *this, res = 1;
            while (n > 0) {
                if (n & 1) res *= base;
                base *= base;
                n >>= 1;
            }
            return res;
        }

        [[nodiscard]]
        mint inv() const {
            return pow(_umod() - 2);
        }

        ////////////////////////////////////////////////////////////////
        // Constructors
        ////////////////////////////////////////////////////////////////

        ModInt() : _v(0) {}

        ModInt(const mint &other) : _v(other._v) {}

        template<typename T,
                is_signed_int_t<T> * = nullptr>
        /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
            __int128 x = value % _umod();
            if (x < 0) x += _umod();
            _v = x;
        }

        template<typename T,
                is_unsigned_int_t<T> * = nullptr>
        /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
            _v = value % _umod();
        }

        ////////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////////

        /* Assignment operators */
        mint &operator=(const mint &other) {
            _v = other._v;
            return *this;
        }

        mint &operator+=(const mint &rhs) {
            unsigned __int128 tmp = _v;
            tmp += rhs._v;
            _v = tmp % _umod();
            return *this;
        }

        mint &operator-=(const mint &rhs) {
            __int128 tmp = _v;
            tmp -= rhs._v;
            if (tmp < 0) tmp += _umod();
            _v = tmp % _umod();
            return *this;
        }

        mint &operator*=(const mint &rhs) {
            unsigned __int128 tmp = _v;
            tmp *= rhs._v;
            _v = tmp % _umod();
            return *this;
        }

        mint &operator/=(const mint &rhs) {
            return *this = *this * rhs.inv();
        }


        /* Binary operators */
        friend mint operator+(const mint &lhs, const mint &rhs) {
            return mint(lhs) += rhs;
        }

        friend mint operator-(const mint &lhs, const mint &rhs) {
            return mint(lhs) -= rhs;
        }

        friend mint operator*(const mint &lhs, const mint &rhs) {
            return mint(lhs) *= rhs;
        }

        friend mint operator/(const mint &lhs, const mint &rhs) {
            return mint(lhs) /= rhs;
        }


        /* Unary operators */
        mint operator+() { return *this; }

        mint operator-() { return mint() - *this; }


        /* Increment/Decrement operators */
        mint &operator++() {
            _v++;
            if (_v == _umod()) _v = 0;
            return *this;
        }

        mint &operator--() {
            if (_v == 0) _v = _umod();
            _v--;
            return *this;
        }

        mint operator++(int) {
            mint res = *this;
            ++*this;
            return res;
        }

        mint operator--(int) {
            mint res = *this;
            --*this;
            return res;
        }

        /* Conditional operators */
        bool operator==(const mint &other) { return _v == other._v; }

        bool operator==(const unsigned long long &other) { return _v == other; }

        bool operator!=(const mint &other) { return _v != other._v; }

        bool operator!=(const unsigned long long &other) { return _v != other; }

        /* I/O operator */
        friend std::ostream &operator<<(std::ostream &out, const mint &m) {
            out << m._v;
            return out;
        }

        friend std::istream &operator>>(std::istream &in, mint &m) {
            in >> m._v;
            m._v %= _umod();
            return in;
        }
    };

    int pow_mod(int a, int pow, int MOD) {
        int base = a;
        int res = 1;
        while (pow > 0) {
            if (pow & 1) {
                res = (int) (1ULL * res * base) % MOD;
            }
            base = (int) (1ULL * base * base) % MOD;
            pow >>= 1;
        }
        return res;
    }

    int factorial_mod(int n, int MOD) {
        int res = 1;
        for (int i = 1; i <= n; i++) {
            res = (int) (1ULL * res * i) % MOD;
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
            result = (result * _binomial_coefficient(n_remain, k_remain, MOD)) % MOD;
        }
        return result;
    }
} // namespace Modulo

using mint = Modulo::ModInt<1'000'000'007>;

int32_t main() {
    fastIO;
    int t, n, d;
    cin >> t >> n >> d;

    vector<Matrix::StaticMatrix<mint,20,20>> maps(t);
    for (int i = 0; i < t; i++){
        int m; cin >> m;
        for (int j = 0; j < m; j++){
            int u, v, w;
            cin >> u >> v >> w;
            maps[i][u-1][v-1] = w;
        }
    }
    auto tmp = Matrix::StaticMatrix<mint,20,20>::identity();
    for (int i = 0; i < t; i++){
        tmp *= maps[i];
    }
    auto res = pow(tmp, d / t);
    for (int i = 0; i < d % t; i++) res *= maps[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << res[i][j] << ' ';
        cout << endl;
    }

    return 0;
}