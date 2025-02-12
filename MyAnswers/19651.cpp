//
// Created by june0 on 2025-02-13.
//
//
// ** The #include statements were replaced by [ CCopy ] **
// @See http://github.com/Aledo-Jun/CCopy
//

// [ #include "Utils/using_templates.hpp" ]


#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using ld [[maybe_unused]] = double;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;



// end of [ Utils/using_templates.hpp ]

#ifndef ONLINE_JUDGE
#define LOCAL
#else
/**
 * Namespace for Fast I/O
 *
 * @class@b INPUT
 * class which can replace the cin
 *
 * @class@b OUTPUT
 * class which can replace the cout
 *
 * @Description
 * These classes use low-level i/o functions (@c fread()/mmap() for input, @c fwrite()/write() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iomanip>

    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char* p;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }
        INPUT() {
            struct stat st;
            fstat(0, &st);
            p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
        }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            return *p++;
        }

        char ReadChar() {
            char ret = _ReadChar();
            for (; IsBlank(ret); ret = _ReadChar());

            return ret;
        }

        template<class T>
        T ReadInt() {
            T ret = 0;
            char curr = _ReadChar();
            bool minus_flag = false;

            for (; IsBlank(curr); curr = _ReadChar());
            if (curr == '-') minus_flag = true, curr = _ReadChar();
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret = 10 * ret + (curr & 15);
            if (IsEnd(curr)) __END_FLAG__ = true;

            return minus_flag ? -ret : ret;
        }

        std::string ReadString() {
            std::string ret;
            char curr = _ReadChar();
            for (; IsBlank(curr); curr = _ReadChar());
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (IsEnd(curr)) __END_FLAG__ = true;

            return ret;
        }

        double ReadDouble() {
            std::string ret = ReadString();
            return std::stod(ret);
        }

        long double ReadLongDouble() {
            std::string ret = ReadString();
            return std::stold(ret);
        }

        std::string getline() {
            std::string ret;
            char curr = _ReadChar();
            for (; curr != '\n' && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (__GET_LINE_FLAG__) __END_FLAG__ = true;
            if (IsEnd(curr)) __GET_LINE_FLAG__ = true;

            return ret;
        }

        friend INPUT &getline(INPUT &in, std::string &s) {
            s = in.getline();
            return in;
        }
    } _in;
    /* End of Class INPUT */

    /* Class OUTPUT */
    class OUTPUT {
    private:
        char _write_buffer[SZ];
        int _write_idx;
        int _precision = 6;
    public:
        ~OUTPUT() { Flush(); }

        explicit operator bool() const { return true; }

        void Flush() {
            write(1, _write_buffer, _write_idx);
            _write_idx = 0;
        }

        void SetPrecision(int precision) {
            _precision = precision;
        }

        void WriteChar(char c) {
            if (_write_idx == SZ) Flush();
            _write_buffer[_write_idx++] = c;
        }

        template<class T>
        void WriteInt(T n) {
            int sz = GetSize(n);
            if (_write_idx + sz >= SZ) Flush();
            if (n < 0) _write_buffer[_write_idx++] = '-', n = -n;
            for (int i = sz; i-- > 0; n /= 10)
                _write_buffer[_write_idx + i] = n % 10 | 48;
            _write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        template<class T>
        void WriteDouble(T d) {
            WriteString(FloatingToFixedString(d, _precision));
        }

        template<class T>
        int GetSize(T n) {
            int ret = 1;
            for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;

            return ret;
        }

        template<class T>
        std::string FloatingToFixedString(T val, int precision) {
            char buf[64];
            if constexpr (std::is_same_v<double, T>)
                snprintf(buf, sizeof(buf), "%.*f", precision, val);
            else
                snprintf(buf, sizeof(buf), "%.*Lf", precision, val);
            return std::string(buf);
        }
    } _out;
    /* End of Class OUTPUT */

    /* Operators */
    INPUT &operator>>(INPUT &in, char &i) {
        i = in.ReadChar();
        return in;
    }

    INPUT &operator>>(INPUT &in, std::string &i) {
        i = in.ReadString();
        return in;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    INPUT &operator>>(INPUT &in, T &i) {
        if constexpr (std::is_same_v<double, T>) i = in.ReadDouble();
        else if constexpr (std::is_same_v<long double, T>) i = in.ReadLongDouble();
        else if constexpr (std::is_integral_v<T>) i = in.ReadInt<T>();
        return in;
    }

    OUTPUT &operator<<(OUTPUT &out, char i) {
        out.WriteChar(i);
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, const std::string &i) {
        out.WriteString(i);
        return out;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    OUTPUT &operator<<(OUTPUT &out, T i) {
        if constexpr (std::is_floating_point_v<T>) out.WriteDouble(i);
        else if constexpr (std::is_integral_v<T>) out.WriteInt(i);
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, OUTPUT &(*fp)(OUTPUT &)) {
        return fp(out);
    }

    OUTPUT &flush(OUTPUT& out) {
        out.Flush();
        return out;
    }

    OUTPUT &fixed(OUTPUT& out) {
        // Do nothing since there's no other floating point format than fixed.
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, const _Setprecision &m) {
        out.SetPrecision(m._M_n);
        return out;
    }


    /* Macros for convenience */
    #undef fastIO
    #define fastIO 1
    #define cin _in
    #define cout _out
    #define istream INPUT
    #define ostream OUTPUT
};
using namespace FastIO;
#endif
// [ #include "DataStructure/SegTree_iter.h" ]


#include <cmath>
#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
/**
 * Segment Tree using iterative method
 * @tparam T type of elements
 * @tparam func function object to be called to perform the query
 * @tparam updating_func function object to be called to update the containing element
 */
        template<typename T,
                typename func = plus<T>,
                typename updating_func = plus<T>>
        class SegTree_iter {
        private:
            func f;
            updating_func updating_f;
            T default_query;

            vector<T> tree, arr;
            int size, height, n;

            void init() {
                for (int i = n - 1; i > 0; i--)
                    tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
            }

            void _update(int i, T value) {
                i += n;
                tree[i] = updating_f(tree[i], value);
                for (i >>= 1; i > 0; i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
            }

            T _query(int i) {
                T res = default_query;
                for (i += n; i > 0; i >>= 1) res = f(res, tree[i]);
                return res;
            }

            T _query(int l, int r) {
                T res1 = default_query, res2 = default_query;
                for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
                    if (l & 1) res1 = f(res1, tree[l++]);
                    if (~r & 1) res2 = f(tree[r--], res2);
                    // NOTE: There exists cases that the operation's order must be considered
                }
                return f(res1, res2);
            }

        public:
            SegTree_iter() = default;
            SegTree_iter(int sz, T&& default_query = {}) : default_query(std::move(default_query)) {
                height = (int) ceil(log2(sz));
                size = (1 << (height + 1));
                n = size >> 1;
                tree.resize(size + 1, default_query);
            }

            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
             */
            SegTree_iter(const vector<T> &v, T&& default_query = {}) : SegTree_iter(v.size()) {
                arr = v;
                this->default_query = default_query;
                std::copy(arr.begin(), arr.end(), tree.begin() + n);
                init();
            }

            void update(int idx, T value) {
                _update(idx, value);
            }

            T query(int idx) {
                return _query(idx);
            }

            T query(int left, int right) {
                return _query(left, right);
            }
        }; // class SegTree_iter
    }
}


// end of [ DataStructure/SegTree_iter.h ]

// [ #include "DataStructure/LazySegTree_iter.h" ]


using namespace std;

namespace DataStructure {
    namespace SegTree {
/**
 * Lazy Segment Tree using iterative method
 * @tparam T value type
 * @tparam S lazy type
 * @tparam TT functor to merge tree nodes -> T(T,T)
 * @tparam SS functor to update the lazy value -> S(S,S)
 * @tparam TS functor to apply lazy update to tree node -> T(T,S,int)
 */
        template<typename T, typename S = T,
                typename TT = T(T, T),
                typename SS = S(S, S),
                typename TS = T(T, S, int)>
        class LazySegTree_iter {
        private:
            TT f;
            SS lazy_to_lazy;
            TS lazy_to_tree;
            T default_query;
            S default_lazy;

            vector<T> tree, arr;
            vector<S> lazy;
            int size{}, height{}, n{};

            void init() {
                for (int i = n - 1; i >= 1; i--) pull(i);
            }

            void apply(int node, S value, int offset) {
                tree[node] = lazy_to_tree(tree[node], value, offset);
                if (node < n) lazy[node] = lazy_to_lazy(lazy[node], value);
            }

            void pull(int node) {
                tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
            }

            void pull_all(int l, int r) {
                for (int i = 1; i <= height; i++) {
                    if ((l >> i << i) != l) pull(l >> i);
                    if ((r >> i << i) != r) pull((r - 1) >> i);
                }
            }

            void push(int node, int offset) {
                if (lazy[node] == default_lazy) return;
                apply(node << 1, lazy[node], offset >> 1);
                apply(node << 1 | 1, lazy[node], offset >> 1);
                lazy[node] = default_lazy;
            }

            void push_all(int l, int r) {
                for (int i = height, k = n; i >= 1; i--, k >>= 1) {
                    if ((l >> i << i) != l) push(l >> i, k);
                    if ((r >> i << i) != r) push((r - 1) >> i, k);
                }
            }

            void _update(int i, S value) {
                i += n;
                for (int j = height, k = n >> 1; j >= 1; j--, k >>= 1) push(i >> j, k);
                tree[i] = lazy_to_tree(tree[i], value, 1);
                for (int j = 1; j <= height; j++) pull(i >> j);
            }

            void _update(int l, int r, S value) {
                l += n, r += n;
                push_all(l, r + 1);

                int l0 = l, r0 = r;
                for (int k = 1; l <= r; l >>= 1, r >>= 1, k <<= 1) {
                    if (l & 1) apply(l++, value, k);
                    if (~r & 1) apply(r--, value, k);
                }

                l = l0, r = r0;
                pull_all(l, r + 1);
            }

            T _query(int i) {
                i += n;
                for (int j = height, k = n >> 1; j >= 1; j--, k >>= 1) push(i >> j, k);
                return tree[i];
            }

            T _query(int l, int r) {
                l += n, r += n;
                push_all(l, r + 1);

                T res1 = default_query, res2 = default_query;
                for (; l <= r; l >>= 1, r >>= 1) {
                    if (l & 1) res1 = f(res1, tree[l++]);
                    if (~r & 1) res2 = f(tree[r--], res2);
                    // NOTE: There exists cases that the operation's order must be considered
                }
                return f(res1, res2);
            }

            int _get_kth(T k) {
                for (int node = 1, offset = n;; offset >>= 1) {
                    if (node >= n) return node - n;
                    push(node, offset);
                    if (k <= tree[node << 1]) node = node << 1;
                    else {
                        k -= tree[node << 1];
                        node = node << 1 | 1;
                    }
                }
            }

            bool is_valid_range(int idx) {
                return 0 <= idx && idx < n;
            }

            bool is_valid_range(int l, int r) {
                return ((l <= r) && is_valid_range(l) && is_valid_range(r));
            }

        public:
            LazySegTree_iter() = default;

            /**
             * Construct segTree with the size of @p sz filled with default values
             * @param sz
             */
            LazySegTree_iter(int sz, T _default_query = {}, S _default_lazy = {})
                    : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy)) {
                height = (int) ceil(log2(sz));
                size = (1 << (height + 1));
                n = size >> 1;
                tree.resize(size + 1, default_query);
                lazy.resize(size + 1, default_lazy);
            }

            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>TT</i> with
             */
            explicit
            LazySegTree_iter(const vector<T> &v, T _default_query = 0, S _default_lazy = 0)
                    : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy)) {
                arr = v;
                height = (int) ceil(log2(v.size()));
                size = (1 << (height + 1));
                n = size >> 1;
                tree.resize(size + 1, default_query);
                lazy.resize(size + 1, default_lazy);
                std::copy(arr.begin(), arr.end(), tree.begin() + n);
                init();
            }

            void update(int idx, S value) {
                if (!is_valid_range(idx)) return;
                _update(idx, value);
            }

            void update(int l, int r, S value) {
                _update(max(0, l), min(r, n-1), value);
            }

            T query(int idx) {
                if (!is_valid_range(idx)) return 0;
                return _query(idx);
            }

            T query(int l, int r) {
                return _query(max(0, l), min(r, n-1));
            }

            int get_kth(T k) {
                return _get_kth(k);
            }
        }; // class LazySegTree_iter
    }
}


// end of [ DataStructure/LazySegTree_iter.h ]

struct TT { ll operator()(const ll l, const ll r){ return l + r; }};
struct TS { ll operator()(const ll l, const ll r, const int offset){ return l + r * offset; }};
using lazy_segtree = DataStructure::SegTree::LazySegTree_iter<ll,ll,TT,TT,TS>;

struct goldNode {
    int l = 0, r = 0, mx = 0, flag = -1; // flag := is the range is contiguous, -1 = ignore this node
    goldNode() = default;
    goldNode(int val) : l(val), r(val), mx(val), flag(val) {} // NOLINT: intended implicit conversion
    goldNode(int l, int r, int mx, int flag) : l(l), r(r), mx(mx), flag(flag) {}
};
struct goldMerge {
    goldNode operator()(const goldNode &l, const goldNode &r) {
        if (l.flag == -1) return r;
        if (r.flag == -1) return l;
        return goldNode(l.flag ? l.mx + r.l : l.l,
                        r.flag ? l.r + r.mx : r.r,
                        max({l.mx, r.mx, l.r + r.l}),
                        l.flag && r.flag);
    }
};
template<typename T>
struct replacement { T operator()([[gnu::unused]] const T &l, const T &r) const { return r; }};
using segtree = DataStructure::SegTree::SegTree_iter<goldNode,goldMerge,replacement<goldNode>>;

int32_t main() {
    fastIO;
    int n, m;
    cin >> n;
    vector<int> v(n);
    for (auto &e : v) cin >> e;

    lazy_segtree segTree(n, 0);
    for (int i = 0; i < n; i++) {
        segTree.update(i, v[i]);
        segTree.update(i+1, -v[i]);
    }
    // A[i] = segTree.query(0, i)

    // B[i] := 2A[i] - A[i-1] - A[i+1] for 0 < i < n-1
    // => 0 iff A[i-1..i+1] is an arithmetic sequence
    segtree segTree2(n); // count the maximum length of the consecutive 0s
    for (int i = 1; i < n-1; i++)
        segTree2.update(i, goldNode((2*v[i] - v[i-1] - v[i+1]) == 0));

    cin >> m;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            ll x, y;
            cin >> l >> r >> x >> y;
            l--, r--;
            segTree.update(l, x);
            segTree.update(l+1, r, y);
            segTree.update(r+1, -(x + (r - l) * y));
            // if A[l..r] changes, only B[l-1, l, r, r+1] changes
            for (const auto i: {l-1, l, r, r+1})
                if (0 < i && i < n-1)
                    segTree2.update(i, (2 * segTree.query(0, i) - segTree.query(0, i - 1) - segTree.query(0, i + 1)) == 0);
        } else {
            int i, j;
            cin >> i >> j;
            i--, j--;
            if (i == j) cout << 1 << endl;
            else if (i + 1 == j) cout << 2 << endl;
            else {
                cout << segTree2.query(i+1, j-1).mx + 2 << endl;
            }
        }
    }

    return 0;
}

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */
