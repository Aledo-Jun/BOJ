//
// Created by june0 on 2024-06-16.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
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
 * Lazy Segment Tree using iterative method
 * @tparam T value type
 * @tparam S lazy type
 * @tparam TT functor to merge tree nodes -> T(T,T)
 * @tparam SS functor to update the lazy value -> S(S,S)
 * @tparam TS functor to apply lazy update to tree node -> T(T,S,int)
 */
template<typename T, typename S = T,
        typename TT = T(T,T),
        typename SS = S(S,S),
        typename TS = T(T,S,int)>
class LazySegTree_iter {
private:
    TT f;
    SS lazy_to_lazy;
    TS lazy_to_tree;
    T default_query{};
    S default_lazy{};

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

    void push(int node, int offset = 2) {
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
        for (int j = height; j >= 1; j--) push(i >> j);
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
        for (int j = height; j >= 1; j--) push(i >> j);
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
        for (int node = 1, offset = n; ; offset >>= 1) {
            if (node >= n) return node - n;
            push(node, offset);
            if (k <= tree[node << 1]) node = node << 1;
            else {
                k -= tree[node << 1];
                node = node << 1 | 1;
            }
        }
    }

public:
    LazySegTree_iter() = default;
    /**
     * Construct segTree with the size of @p sz filled with default values
     * @param sz
     */
    explicit
    LazySegTree_iter(int sz, T _default_query = {}, S _default_lazy = {})
            : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy))
    {
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
            : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy))
    {
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
        _update(idx, value);
    }

    void update(int l, int r, S value) {
        _update(l, r, value);
    }

    T query(int idx) {
        return _query(idx);
    }

    T query(int left, int right) {
        return _query(left, right);
    }

    int get_kth(T k) {
        return _get_kth(k);
    }
}; // class LazySegTree_iter

struct T {
    /*
     * Suppose a node is representing a range of [s,...m,...e]
     * l := max_contiguous_sum[(s,...m,...),...e]
     * r := max_contiguous_sum[s,...,(...m,...e)]
     * mx := max_contiguous_sum[(s,...m,...e)] -> answer
     * sum := total sum of the range
     */
    ll l, r, mx, sum;
};
struct TT {
    T operator()(const T& l, const T& r) {
        return {max({l.l, l.sum + r.l, 0LL}),
                max({l.r + r.sum, r.r, 0LL}),
                max({l.mx, r.mx, l.r + r.l, 0LL}),
                l.sum + r.sum};
    }
};
struct SS {
    int operator()(const int& l, const int& r) {
        return r;
    }
};
struct TS {
    T operator()(const T& l, int r, int offset) {
        return {max(r * offset, 0),
                max(r * offset, 0),
                max(r * offset, 0),
                r * offset};
    }
};

using lazy_segtree = LazySegTree_iter<T,int,TT,SS,TS>;

/**
 * @brief Heavy Light Decomposition to perform a query on a path in a tree
 */
class HLD {
private:
    vector<int> sz,     // size of the subtree
    depth,  // depth of the node
    top,    // top of the chain the node belongs to
    S;   // Euler Tour
    vector<vector<int>> parent; // parent of the node (binary lifting table)

    int root, n;
    graph<int> adj;     // adjacent list for original tree
    vector<vector<int>> g;

    vector<bool> visited;
    void dfs(int u) { // construct g
        visited[u] = true;
        for (const auto& [v, w]: adj[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            g[u].emplace_back(v);
            dfs(v);
        }
    }

    // construct sz, depth, parent, and make the nodes adjacent if they belong to the same chain
    void dfs1(int u) {
        sz[u] = 1;
        for (auto& v : g[u]) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) std::swap(v, g[u][0]);
        }
    }

    int pv = 0;
    // construct S, T, R, and top
    void dfs2(int u) {
        S[u] = ++pv;
        for (const auto& v: g[u]) {
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
    }

    /* Add something to Utilize the HLD e.g. SegTree */
    vector<int> arr;
    lazy_segtree segTree;

public:
    explicit
    HLD(graph<int>& g, vector<int>& w, int root = 1) : adj(std::move(g)), arr(std::move(w)), root(root), n((int)g.size()) {
        sz.resize(n);
        depth.resize(n);
        parent.resize(n, vector<int>(1));
        top.resize(n);
        S.resize(n);
        this->g.resize(n);
        visited.resize(n);

        dfs(root), dfs1(root), dfs2(root);

        // initialize additional variables
        segTree = lazy_segtree(n, {0,0,0,0}, INT_MAX);
        for (int i = 1; i < n; i++) {
            segTree.update(S[i], arr[i]);
        }
    }

    void update(int x, int y, int val) {
        while (top[x] ^ top[y]) {
            if (depth[top[x]] < depth[top[y]]) swap(x, y);
            int st = top[x];
            segTree.update(S[st], S[x], val);
            x = parent[st][0];
        }
        if (depth[x] > depth[y]) swap(x, y);
        segTree.update(S[x], S[y], val);
    }

    TT merge{};
    ll query(int x, int y) {
        struct T res1{}, res2{};
        //if (S[x] > S[y]) swap(x, y);
        while (top[x] ^ top[y]) {
            if (depth[top[x]] < depth[top[y]]) {
                int st = top[y];
                res2 = merge(segTree.query(S[st], S[y]), res2);
                y = parent[st][0];
            } else {
                int st = top[x];
                res1 = merge(segTree.query(S[st], S[x]), res1);
                x = parent[st][0];
            }
        }
        if (depth[x] > depth[y]) res1 = merge(segTree.query(S[y], S[x]), res1);
        else res2 = merge(segTree.query(S[x], S[y]), res2);
        swap(res1.l, res1.r); // since res1 is calculated from top to bottom(lca->x)
        // what we need is path query from x to y (x->lca->y)
        return merge(res1, res2).mx;
    }

}; // class HLD

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }

    HLD solver(g, w);

    int q;
    cin >> q;
    while (q--) {
        int cmd, x, y, val;
        cin >> cmd >> x >> y;
        if (cmd == 1) {
            cout << solver.query(x, y) << endl;
        } else {
            cin >> val;
            solver.update(x, y, val);
        }
    }

    return 0;
}