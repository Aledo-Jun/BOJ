//
// Created by june0 on 2024-06-12.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC optimize("O3,unroll-loops")
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
template<typename T> using graph [[maybe_unused]] = vector<vector<tuple<int,T,int>>>;
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
 * These classes use low-level i/o functions (@c fread() for input, @c fwrite() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char readBuffer[SZ];
        int read_idx, next_idx;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            if (read_idx == next_idx) {
                next_idx = (int)fread(readBuffer, sizeof(char), SZ, stdin);
                if (next_idx == 0) return 0;
                read_idx = 0;
            }
            return readBuffer[read_idx++];
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
            fwrite(writeBuffer, sizeof(char), write_idx, stdout);
            write_idx = 0;
        }

        void WriteChar(char c) {
            if (write_idx == SZ) Flush();
            writeBuffer[write_idx++] = c;
        }

        template<class T>
        void WriteInt(T total) {
            int sz = GetSize(total);
            if (write_idx + sz + 1 >= SZ) Flush();
            if (total < 0) writeBuffer[write_idx++] = '-', total = -total;
            for (int i = sz; i-- > 0; total /= 10)
                writeBuffer[write_idx + i] = total % 10 | 48;
            write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        void WriteDouble(double d) {
            WriteString(std::to_string(d));
        }

        template<class T>
        int GetSize(T total) {
            int ret = 1;
            for (total = total >= 0 ? total : -total; total >= 10; total /= 10) ret++;

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
    int size, height;

    void init() {
        for (int i = size / 2 - 1; i > 0; i--)
            tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    void _update(int i, T value) {
        i += size / 2;
        tree[i] = updating_f(tree[i], value);
        for (i >>= 1; i > 0; i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }

    T _query(int i) {
        T res = default_query;
        for (i += size / 2; i > 0; i >>= 1) res = f(res, tree[i]);
        return res;
    }

    T _query(int l, int r) {
        T res1 = default_query, res2 = default_query;
        for (l += size / 2, r += size / 2; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res1 = f(res1, tree[l++]);
            if (~r & 1) res2 = f(tree[r--], res2);
            // NOTE: There exists cases that the operation's order must be considered
        }
        return f(res1, res2);
    }

public:
    SegTree_iter() = default;
    /**
     * Constructor for a segment tree
     * @param v Array that the segment tree will be constructed from
     * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
     */
    SegTree_iter(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
        arr = v;
        height = (int) ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1, default_query);
        std::copy(arr.begin(), arr.end(), tree.begin() + size / 2);
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

struct max_query {
    int operator()(int l, int r) { return l > r ? l : r; }
};
struct replacement {
    int operator()(int l, int r) { return r; }
};

using segment_tree = SegTree_iter<int,max_query,replacement>;

/**
 * @brief Heavy Light Decomposition to perform a query on a path in a tree
 */
class HLD {
private:
    vector<int> sz,     // size of the subtree
    depth,  // depth of the node
    weight, // weight from the parent
    top,    // top of the chain the node belongs to
    S, T, R;   // Euler Tour
    vector<vector<int>> parent; // parent of the node (binary lifting table)

    int root, n;
    graph<int> adj;     // adjacent list for original tree
    vector<vector<int>> g;

    vector<bool> visited;
    void dfs(int u) { // construct g
        visited[u] = true;
        for (const auto& [v, w, idx]: adj[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            g[u].emplace_back(v);
            edge_map[idx] = v;
            weight[v] = w;
            dfs(v);
        }
    }

    // construct sz, depth, parent, and make the nodes adjacent if they belong to the same chain
    void dfs1(int u) {
        sz[u] = 1;
        for (auto& v : g[u]) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
//            for (int i = 1; i < 20; i++) {
//                parent[v][i] = parent[parent[v][i - 1]][i - 1];
//            }
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) std::swap(v, g[u][0]);
        }
    }

    int pv = 0;
    // construct S, T, R, and top
    void dfs2(int u) {
        S[u] = ++pv;
        R[S[u]] = u;
        for (const auto& v: g[u]) {
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
        T[u] = pv;
    }

    int get_centroid(int u, int threshold) {
        for (const auto& v: g[u]) {
            if (sz[v] * 2 > threshold) return get_centroid(v, threshold);
        }
        return u;
    }

    /* Add something to Utilize the HLD e.g. SegTree */
    segment_tree segTree;
    vector<int> edge_map; // edge(u->v) idx -> v

public:
    explicit
    HLD(const graph<int>& g, int root = 1) : adj(g), root(root), n((int)g.size()) {
        sz.resize(n);
        depth.resize(n);
        parent.resize(n, vector<int>(20));
        top.resize(n);
        weight.resize(n);
        S.resize(n); T.resize(n); R.resize(n);
        this->g.resize(n);
        visited.resize(n);

        edge_map.resize(n);
        dfs(root), dfs1(root), dfs2(root);

        // initialize additional variables
        vector<int> tmp(n);
        for (int i = 1; i < n; i++) {
            tmp[S[i]] = weight[i];
        }
        segTree = segment_tree(tmp);
    }

    void update(int x, int val) {
        segTree.update(S[edge_map[x]], val);
    }

    int query(int x, int y) {
        int res = 0;
        while (top[x] ^ top[y]) {
            if (depth[top[x]] < depth[top[y]]) swap(x, y);
            int st = top[x];
            // perform query from S[st] to S[x]
            res = max(res, segTree.query(S[st], S[x]));
            x = parent[st][0];
        }
        if (depth[x] > depth[y]) swap(x, y);
        // perform query from S[x] to S[y]
        res = max(res, segTree.query(S[x] + 1, S[y]));
        return res;
    }

}; // class HLD

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w, i);
        g[v].emplace_back(u, w, i);
    }

    HLD solver(g);

    int q;
    cin >> q;
    while (q--) {
        int cmd, x, y;
        cin >> cmd >> x >> y;
        if (cmd == 1) {
            solver.update(x, y);
        } else {
            cout << solver.query(x, y) << endl;
        }
    }

    return 0;
}