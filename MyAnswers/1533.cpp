//
// Created by june0 on 2024-02-20.
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

namespace Utils
{
    namespace Math {
        constexpr long long safe_mod(long long x, unsigned long long m) {
            x = (long long)(x % m);
            if (x < 0) x = (long long)(x + m);
            return x;
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

        constexpr unsigned pow_mod_constexpr(long long a, unsigned long long n, unsigned long long MOD) {
            if (MOD == 1) return 0;
            unsigned long long _a = safe_mod(a, MOD);
            unsigned long long res = 1;
            while (n) {
                if (n & 1) res = (res * _a) % MOD;
                n >>= 1;
                _a = (_a * _a) % MOD;
            }
            return res;
        }

        // NOTE : m must be prime
        constexpr unsigned primitive_root_constexpr(unsigned long long m) {
            // some popular roots
            if (m == 2) return 1;
            if (m == 786'433) return 10;
            if (m == 167'772'161) return 3;
            if (m == 469'762'049) return 3;
            if (m == 754'974'721) return 11;
            if (m == 998'244'353) return 3;
            if (m == 9'223'372'036'972'216'319ull) return 3;

            // find divisors of m - 1
            unsigned divs[20] = {};
            divs[0] = 2;
            unsigned cnt = 1;
            unsigned x = (m - 1) / 2;
            while (x % 2 == 0) x /= 2;
            for (int i = 3; (long long) (i) * i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            // find the first g s.t. there exist some d in divs, g^(m - 1)/d == 1 mod m
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
        }

        template<unsigned long long m> constexpr unsigned primitive_root = primitive_root_constexpr(m);

        // Structure for fast modular multiplication
        struct Barrett {
            unsigned MOD;
            unsigned long long inv_MOD;

            explicit Barrett(unsigned m) : MOD(m), inv_MOD((unsigned long long) (-1) / MOD + 1) {}

            [[nodiscard]]
            unsigned mod() const { return MOD; }

            [[nodiscard]]
            unsigned multiply(unsigned a, unsigned b) const {
                unsigned long long res1 = a;
                res1 *= b;
                unsigned long long res2 = ((unsigned __int128) (res1) * inv_MOD) >> 64;
                res2 *= MOD;
                return (res1 - res2 + (res1 < res2 ? MOD : 0));
            }
        };

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
    } // namespace Math

    namespace TypeTraits {
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

        template<typename T, typename = void>
        struct supports_arithmetic : public std::false_type { };

        template<typename T>
        struct supports_arithmetic<T,
                void_t<decltype(std::declval<T>() + std::declval<T>()),
                        decltype(std::declval<T>() - std::declval<T>()),
                        decltype(std::declval<T>() * std::declval<T>()),
                        decltype(std::declval<T>() / std::declval<T>())>>
                : public std::true_type { };

        template<typename T>
        using supports_arithmetic_v = typename supports_arithmetic<T>::value;

        struct modint_base { };

        template<typename T>
        using is_modint = std::is_base_of<modint_base, T>;
        template<typename T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;

        struct matrix_base { };

        template<typename T>
        using is_matrix = std::is_base_of<matrix_base, T>;

        template<typename T>
        using is_matrix_t = std::enable_if_t<is_matrix<T>::value>;

    } // namespace TypeTraits

    namespace Modulo {
        using namespace TypeTraits;
        using namespace Math;

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

    } // namespace Modulo

    namespace Matrix {
        using namespace TypeTraits;

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

    namespace SegTree {
/**
 * Segment Tree that contains the result of a query over the range.
 * @tparam T type of elements
 * @tparam func function object to be called to perform the query
 * @tparam updating_func function object to be called to update the containing element
 */
        template<typename T,
                typename func = plus<T>,
                typename updating_func = plus<T>>
        class SegTree {
        private:
            func f;
            updating_func updating_f;
            T default_query;

            vector<T> tree, arr;
            int size, height;

            T init(int node, int left, int right) {
                if (left == right) return tree[node] = arr[left];

                int mid = (left + right) >> 1;
                auto left_result = init(node << 1, left, mid);
                auto right_result = init(node << 1 | 1, mid + 1, right);
                tree[node] = f(left_result, right_result);

                return tree[node];
            }

            /**
             * Update the tree as a result of performing <i>updating_func</i> with <i>value</i> to the arr[idx]
             * @param node current node index in the tree
             * @param start starting index that the current node is covering
             * @param end ending index that the current node is covering
             * @param idx index of array that updating is required
             * @param value the value to be used for performing <i>updating_func</i> to the arr[idx]
             */
            void _update(int node, int start, int end, int idx, T value) {
                if (idx < start || end < idx) return;

                if (start == end) {
                    tree[node] = updating_f(tree[node], value);
                } else {
                    int mid = (start + end) >> 1;
                    _update(node << 1, start, mid, idx, value);
                    _update(node << 1 | 1, mid + 1, end, idx, value);
                    tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
                }
            }


            /**
             * Find the result of @p func over the array elements in range [left, right]
             * @param node current node index in the tree
             * @param start starting index that the current node is covering
             * @param end ending index that the current node is covering
             * @param left starting index of performing @p func
             * @param right ending index of performing @p func
             * @return the result of @p func over the array elements in range [left, right]
             */
            T _query(int node, int start, int end, int left, int right) {
                if (end < left || right < start) return default_query;
                if (left <= start && end <= right) return tree[node];

                int mid = (start + end) >> 1;
                auto left_result = _query(node << 1, start, mid, left, right);
                auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
                return f(left_result, right_result);
            }

        public:
            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
             */
            explicit SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
                arr = v;
                height = (int) ceil(log2(v.size()));
                size = (1 << (height + 1));
                tree.resize(size + 1);
                init(1, 0, v.size() - 1);
            }

            void update(int idx, T value) {
                _update(1, 0, arr.size() - 1, idx, value);
            }

            T query(int left, int right) {
                return _query(1, 0, arr.size() - 1, left, right);
            }

        }; // class SegTree
    } // namespace SegTree

    namespace OrderedSet {
        using namespace std;
        using namespace __gnu_pbds;

        using ordered_set = ::__gnu_pbds::tree<
                int,
                __gnu_pbds::null_type,
                std::less<>,
                __gnu_pbds::rb_tree_tag,
                __gnu_pbds::tree_order_statistics_node_update>;

        using ordered_multiset = __gnu_pbds::tree<
                int,
                __gnu_pbds::null_type,
                std::less_equal<>,
                __gnu_pbds::rb_tree_tag,
                __gnu_pbds::tree_order_statistics_node_update>;

        void multiset_erase(ordered_multiset &OS, int val) {
            int index = (int) OS.order_of_key(val);
            auto it = OS.find_by_order(index);
            if (*it == val) OS.erase(it);
        }
    } // namespace OrderedSet

    namespace DisjointSet {
        template<bool Union_By_Rank = true>
        class DisjointSet {
        private:
            const int def_sz = 1001;
            vector<int> parent;
            vector<int> rank;
        public:
            DisjointSet() {
                parent.assign(def_sz, 0);
                rank.assign(def_sz, 0);
            }

            explicit DisjointSet(int sz) {
                parent.assign(sz, 0);
                for (int i = 0; i < sz; i++)
                    parent[i] = i;
                rank.assign(sz, 0);
            }

            // find the root of x
            int find(int x) {
                if (x != parent[x]) {
                    parent[x] = find(parent[x]);
                }
                return parent[x];
            }

            // Union By Rank,
            // i.e. the parent relation could be relational(not specified).
            template<std::enable_if_t<Union_By_Rank>* = nullptr>
            void uni(int x, int y) {
                int rootx = find(x);
                int rooty = find(y);

                if (rootx != rooty) {
                    if (rank[rootx] < rank[rooty])
                        parent[rootx] = rooty;
                    else if (rank[rootx] > rank[rooty])
                        parent[rooty] = rootx;
                    else {
                        parent[rooty] = rootx;
                        rank[rootx]++;
                    }
                }
            }

            // Dangle y to the root of x
            void uni(int x, int y) {
                int rootx = find(x);
                int rooty = find(y);

                if (rootx != rooty)
                    parent[rooty] = rootx;
            }
        }; // class DisjointSet
    } // namespace DisjointSet

    namespace Graph {
        // Assumes that graph is 1-indexed //
        template<typename T> using graph = std::vector<std::vector<pair<int, T>>>;
        template<typename T> using matrix = std::vector<std::vector<T>>;
        const size_t INF = LLONG_MAX;
#pragma ide diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
        // because of unusual bug(it seems to be)
        // that ide warns that the functions parameter with template syntax is never used.

        template<typename T>
        std::vector<std::size_t> dijkstra(const graph<T> &g, int start) {
            std::priority_queue<pair<std::size_t, int>, vector<pair<std::size_t, int>>, std::greater<>> pq;
            std::vector<std::size_t> dist(g.size(), INF);
            pq.emplace(0, start);
            dist[start] = 0;
            while (!pq.empty()) {
                const auto& [d, u] = pq.top();
                pq.pop();

                if (d > dist[u]) continue;

                for (const auto &[v, w]: g[u]) {
                    if (d + w < dist[v]) {
                        dist[v] = d + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        }

        template<typename T>
        std::vector<std::size_t> bellmanFord(const graph<T> &g, int start) {
            int n = (int) g.size() - 1;
            std::vector<std::size_t> dist(n + 1, INF);
            dist[start] = 0;

            for (int i = 1; i < n; i++) {
                for (int u = 1; u <= n; u++) {
                    for (const auto &[v, w]: g[u]) {
                        if (dist[u] != INF && dist[u] + w < dist[v])
                            dist[v] = dist[u] + w;
                    }
                }
            }
            return dist;
        }

/**
 * Verify whether the graph has a negative cycle or not when called <i>after</i> calling bellmanFord
 */
        template<typename T>
        bool is_there_negative_cycle(const graph<T> &g, const std::vector<std::size_t> &dist) {
            int n = (int) g.size() - 1;
            for (int u = 1; u <= n; u++) {
                if (g[u].empty()) continue;
                for (const auto &[v, w]: g[u]) {
                    if (dist[u] != INF && dist[u] + w < dist[v])
                        return true;
                }
            }
            return false;
        }

        template<typename T>
        matrix<std::size_t> floydWarshall(const graph<T> &g) {
            int n = (int) g.size() - 1;
            matrix<std::size_t> res(n + 1, std::vector<std::size_t>(n + 1, INF));
            for (int i = 1; i <= n; i++) {
                for (const auto &e: g[i]) {
                    res[i][e.first] = e.second;
                }
            }
            for (int k = 1; k <= n; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        res[i][j] = std::min(res[i][j], res[i][k] + res[k][j]);
                    }
                }
            }
            return res;
        }

        template<typename T>
        void dfs_for_topological_order(graph<T> &g, int u, std::vector<bool> &visited, std::vector<int> &order) {
            if (visited[u]) return;
            visited[u] = true;

            for (const auto &[v, w]: g[u]) {
                dfs_for_topological_order(g, v, visited, order);
            }

            order.emplace_back(u);
        }

        template<typename T>
        std::vector<int> topological_order_dfs(const graph<T> &g) {
            int n = (int) g.size() - 1;
            std::vector<bool> visited(n + 1, false);
            std::vector<int> result;

            for (int i = 1; i <= n; i++)
                dfs_for_topological_order(g, i, visited, result);

            std::reverse(result.begin(), result.end());
            return result;
        }

        template<typename T>
        std::vector<int> topological_order_degree(const graph<T> &g) {
            int n = (int) g.size() - 1;
            std::vector<int> in_degree(g.size(), 0);
            std::vector<int> result;
            std::queue<int> q;
            for (int u = 1; u <= n; u++){
                for (const auto&[v, w] : g[u])
                    in_degree[v]++;
            }
            for (int u = 1; u <= n; u++){
                if (in_degree[u] == 0) q.emplace(u);
            }

            while (!q.empty()){
                int u = q.front(); q.pop();
                result.emplace_back(u);

                for (const auto&[v, w] : g[u]){
                    in_degree[v]--;
                    if (in_degree[v] == 0) q.emplace(v);
                }
            }

            return result;
        }

        template<typename T>
        struct Edge {
            int u, v;
            T w;

            Edge(int u, int v, T w) : u(u), v(v), w(w) {};

            bool operator<(const Edge &other) const {
                return w < other.w;
            }

            bool operator>(const Edge &other) const {
                return w > other.w;
            }
        };

        template<typename T>
        std::size_t minimumSpanningTree(const std::vector<Edge<T>> &g) {
            std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<>> minHeap(g.begin(), g.end());

            Utils::DisjointSet::DisjointSet ds(g.size() + 1);

            std::size_t res = 0;
            while (!minHeap.empty()) {
                auto e = minHeap.top();
                minHeap.pop();
                if (ds.find(e.u) != ds.find(e.v)) {
                    ds.uni(e.u, e.v);
                    res += e.w;
                }
            }
            return res;
        }

        template<typename T>
        void dfs_scc(const graph<T> &g, int u, std::vector<bool> &visited, std::stack<int> &finishing) {
            if (visited[u]) return;
            visited[u] = true;

            for (const auto &e: g[u]) {
                dfs_scc(g, e.first, visited, finishing);
            }
            finishing.emplace(u);
        }

        template<typename T>
        void inv_dfs_scc(const graph<T> &g, int u, std::vector<bool> &visited, std::vector<int> &curr_scc) {
            for (const auto &e: g[u]) {
                if (visited[e.first]) continue;
                visited[e.first] = true;
                inv_dfs_scc(g, e.first, visited, curr_scc);
            }
            curr_scc.emplace_back(u);
        }

        /**
         * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
         *
         * @tparam T ValueType
         * @param g The given graph
         * @param g_r The inverse of the given graph
         * @return std::vector of SCCs
         */
        template<typename T>
        matrix<int> scc(const graph<T> &g, const graph<T> &g_r) {
            std::vector<bool> visited(g.size(), false);
            std::stack<int> finishing_time;
            for (int i = 1; i < g.size(); i++) {
                if (visited[i]) continue;
                dfs_scc(g, i, visited, finishing_time);
            }

            visited.assign(g.size(), false);
            matrix<int> res;
            std::vector<int> curr_scc;
            while (!finishing_time.empty()) {
                int u = finishing_time.top();
                finishing_time.pop();
                if (visited[u]) continue;
                visited[u] = true;
                inv_dfs_scc(g_r, u, visited, curr_scc);
                res.emplace_back(curr_scc);
                curr_scc.clear();
            }

            return res;
        }
#pragma ide diagnostic pop
    } // namespace Graph

    namespace Tree {
        class LCA {
        private:
            int MAX_BIT;

            std::vector<int> depth; // Depth of each node
            std::vector<std::vector<int>> parent; // Binary Lifting table
            graph<int> adj; // Adjacency list of the tree, Assume that nodes are 1-indexed

        public:
            explicit LCA(const graph<int>& adj) : adj(adj) {
                int sz = (int) adj.size();
                MAX_BIT = std::ceil(std::log2(sz));
                depth.resize(sz);
                parent.resize(sz, vector<int>(MAX_BIT));
                make_tree(1, 0, 0);
            }

            void make_tree(int u, int p, int d) {
                depth[u] = d;
                parent[u][0] = p;
                for (int i = 1; i < 20; i++) {
                    parent[u][i] = parent[parent[u][i - 1]][i - 1];
                }
                for (const auto& [v, w]: adj[u]) {
                    if (v != p) {
                        make_tree(v, u, d + 1);
                    }
                }
            }

            int lca(int u, int v) {
                if (depth[u] < depth[v]) swap(u, v);
                for (int i = 19; i >= 0; i--) {
                    if (depth[u] - (1 << i) >= depth[v]) {
                        u = parent[u][i];
                    }
                }
                if (u == v) return u;
                for (int i = 19; i >= 0; i--) {
                    if (parent[u][i] != parent[v][i]) {
                        u = parent[u][i];
                        v = parent[v][i];
                    }
                }
                return parent[u][0];
            }
        };
    }
} // namespace Utils

using mint = Utils::Modulo::ModInt<1'000'003>;

void solve(int n, int s, int e, int t){
    Utils::Matrix::StaticMatrix<mint, 50, 50> base;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 4; j++){
            base[i * 5 + j + 1][i * 5 + j] = 1;
        }
    }
    char c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c;
            c -= '0';
            if (c == 1) base[i * 5][j * 5] = 1;
            if (c > 1) base[i * 5][j * 5 + c - 1] = 1;
        }
    }

    auto res = pow(base, t);

    cout << res[s * 5][e * 5] << endl;
}

int32_t main() {
    fastIO;
    int n, s, e, t;
    cin >> n >> s >> e >> t;

    solve(n, s - 1, e - 1, t);

    return 0;
}