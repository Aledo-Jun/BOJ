//
// Created by june0 on 2024-07-02.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
#define GRAPH_TYPE_DEFINED
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
#define MATRIX_TYPE_DEFINED
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

#ifdef ONLINE_JUDGE // Be careful if problem is about strings.
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
        char writeBuffer[SZ];
        int write_idx;
    public:
        ~OUTPUT() { Flush(); }

        explicit operator bool() const { return true; }

        void Flush() {
            write(1, writeBuffer, write_idx);
            write_idx = 0;
        }

        void WriteChar(char c) {
            if (write_idx == SZ) Flush();
            writeBuffer[write_idx++] = c;
        }

        template<class T>
        void WriteInt(T n) {
            int sz = GetSize(n);
            if (write_idx + sz >= SZ) Flush();
            if (n < 0) writeBuffer[write_idx++] = '-', n = -n;
            for (int i = sz; i-- > 0; n /= 10)
                writeBuffer[write_idx + i] = n % 10 | 48;
            write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        void WriteDouble(double d) {
            WriteString(std::to_string(d));
        }

        template<class T>
        int GetSize(T n) {
            int ret = 1;
            for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;

            return ret;
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
        if constexpr (std::is_floating_point_v<T>) i = in.ReadDouble();
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
    int size{}, height{}, n{};

    void init() {
        for (int i = n - 1; i > 0; i--)
            tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    void _update(int i, T value) {
        i += n;
        tree[i] = updating_f(tree[i], value);
        for (i >>= 1; i > 0; i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
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
        tree.resize(size + 1, this->default_query);
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
        return tree[idx + n];
    }

    T query(int left, int right) {
        return _query(left, right);
    }

    void clear() {
        fill(all(tree), T{});
    }
}; // class SegTree_iter

template<typename T = long long>
struct GoldMineSeg {
    /*
     * Suppose a node is representing a range of [s,...m,...e]
     * l := max_contiguous_sum[(s,...m,...),...e]
     * r := max_contiguous_sum[s,...,(...m,...e)]
     * mx := max_contiguous_sum[(s,...m,...e)] -> answer
     * sum := total sum of the range
     */
    T l = 0, r = 0, mx = 0, sum = 0;

    GoldMineSeg() = default;

    GoldMineSeg(T l, T r, T mx, T sum) : l(l), r(r), mx(mx), sum(sum) {}

    GoldMineSeg(T val) : l(val), r(val), mx(val), sum(val) {}
};

struct merge_goldmine {
    GoldMineSeg<> operator()(const GoldMineSeg<> &l, const GoldMineSeg<> &r) {
        return {max(l.l, l.sum + r.l),
                max(l.r + r.sum, r.r),
                max({l.mx, r.mx, l.r + r.l}),
                l.sum + r.sum};
    }
};
template<typename T>
struct replacement {
    T operator()(const T &l, const T &r) { return r; }
};

using segtree = SegTree_iter<GoldMineSeg<>, merge_goldmine, replacement<GoldMineSeg<>>>;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<array<int,3>> v(n);
    vector<int> X, Y;
    for (auto &[x, y, w]: v) {
        cin >> x >> y >> w;
        X.emplace_back(x);
        Y.emplace_back(y);
    }
    sort(all(X)); sort(all(Y));
    X.erase(unique(all(X)), X.end()); Y.erase(unique(all(Y)), Y.end());
    for (auto &[x, y, w]: v) {
        x = lower_bound(all(X), x) - X.begin() + 1;
        y = lower_bound(all(Y), y) - Y.begin() + 1;
    }
    sort(all(v), [&](const auto& a, const auto& b) {
        if (a[1] == b[1]) return a[0] < b[0];
        return a[1] < b[1];
    });

    int sz = (int) X.size();
    ll ans = 0;
    segtree segTree(sz + 1);
    for (int i = 0; i < n; i++) {
        if (i && v[i - 1][1] == v[i][1]) continue;
        segTree.clear();
        for (int j = i; j < n; j++) {
            segTree.update(v[j][0], {segTree.query(v[j][0]).mx + v[j][2]});
            if (j == n - 1 || v[j][1] != v[j + 1][1])
                ans = max(ans, segTree.query(1, sz).mx);
        }
    }
    cout << ans << endl;

    return 0;
}