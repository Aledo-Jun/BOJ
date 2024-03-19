//
// Created by june0 on 2024-03-19.
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

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

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

    class LazySegTree {
    private:
        vector<int> tree, lazy;
        vector<int> v;
        int size, height;

        int init(int node, int left, int right) {
            if (left == right) return tree[node] = v[left];

            int mid = (left + right) >> 1;
            auto left_result = init(node << 1, left, mid);
            auto right_result = init(node << 1 | 1, mid + 1, right);
            tree[node] = (left_result + right_result);

            return tree[node];
        }

        void update_lazy(int node, int start, int end) {
            if (lazy[node]) {
                tree[node] += lazy[node] * (end - start + 1);
                if (start != end) {
                    lazy[node << 1] += lazy[node];
                    lazy[node << 1 | 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }

        /**
         * Update the tree as a result of adding values to the array from s_idx to e_idx
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param s_idx starting index that updating is required
         * @param e_idx ending index that updating is required
         * @param value the value to be added to the array
         */
        void _update(int node, int start, int end, int s_idx, int e_idx, int value) {
            update_lazy(node, start, end);

            if (e_idx < start || end < s_idx) return;

            if (s_idx <= start && end <= e_idx) {
                tree[node] += value * (end - start + 1);
                if (start != end) {
                    lazy[node << 1] += value;
                    lazy[node << 1 | 1] += value;
                }
                return;
            }

            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, s_idx, e_idx, value);
            _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
            tree[node] = (tree[node << 1] + tree[node << 1 | 1]);
        }

        /**
         * Find the sum of the array elements in range [left, right]
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param left starting index of summation
         * @param right ending index of summation
         * @return the sum of the array elements in range [left, right]
         */
        int _query(int node, int start, int end, int left, int right) {
            update_lazy(node, start, end);

            if (left > end || right < start) return 0;
            if (left <= start && end <= right) return tree[node];

            int mid = (start + end) >> 1;
            auto left_result = _query(node << 1, start, mid, left, right);
            auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
            return (left_result + right_result);
        }

    public:

        /**
         * Constructor for a lazy segment tree
         * @param arr  Build a segment tree from the given array
         */
        explicit LazySegTree(const vector<int> &arr) {
            v = arr;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1);
            lazy.resize(size + 1);
            init(1, 0, (int)v.size() - 1);
        }

        void update(int s_idx, int e_idx, int value) {
            _update(1, 0, (int)v.size() - 1, s_idx, e_idx, value);
        }

        int query(int left, int right) {
            return _query(1, 0, (int)v.size() - 1, left, right);
        }
    }; // class LazySegTree

    class FenWickTree {
    private:
        vector<int> tree;
        int size;

        void _update(int x, int val) {
            for (int i = x; i < size; i += (i & -i)) {
                tree[i] += val;
            }
        }

        int _query(int x) {
            int res = 0;
            for (int i = x; i > 0; i -= (i & -i)) {
                res += tree[i];
            }
            return res;
        }

    public:
        FenWickTree(const vector<int> &v) {
            size = v.size();
            tree = vector<int>(size);
            for (int i = 1; i < size; i++) {
                _update(i, v[i]);
            }
        }

        void update(int x, int val) {
            _update(x, val);
        }

        int query(int left, int right, int k) {
            if (left == right) return left;

            int mid = (left + right) >> 1;
            int l = _query(left - 1);
            int m = _query(mid);
            if (m - l >= k) return query(left, mid, k);
            else return query(mid + 1, right, k - m + l);
        }
    }; // class FenWickTree
} // namespace SegTree
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
using mint = Modulo::ModInt<int(1e9 + 7)>;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<mint> v(n + 1, 0);

    // seg[i][j] : the number of increasing subsequences of length i that ends with j
    // therefore, seg[i].query(1, x-1) = seg[i + 1][x]
    vector<SegTree::SegTree<mint>> seg(12, SegTree::SegTree<mint>(v));

    for (int i = 0; i < n; i++){
        int x; cin >> x;
        seg[1].update(x, 1);
        for (int j = 2; j <= 11; j++){
            seg[j].update(x, seg[j - 1].query(1, x - 1));
        }
    }
    cout << seg[11].query(1, n);

    return 0;
}