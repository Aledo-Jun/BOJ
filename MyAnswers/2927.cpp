//
// Created by june0 on 2024-07-20.
//
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

class DisjointSet {
    vector<int> par, rank;

public:
    DisjointSet(int sz) : par(sz + 1), rank(sz + 1, 0) {
        iota(all(par), 0);
    }

    int find(int x) {
        if (x != par[x]) par[x] = find(par[x]);
        return par[x];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (rank[x] < rank[y]) swap(x, y);
        par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
};

vector<int> penguins;

class BIT {
    vector<int> tree;
    int sz;

public:
    BIT(int sz) : sz(sz), tree(sz, 0) {}

    void update(int idx, int val) {
        int diff = val - penguins[idx];
        penguins[idx] = val;
        for (int i = idx; i < sz; i += i & -i) {
            tree[i] += diff;
        }
    }

    int query(int idx) {
        int res = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            res += tree[i];
        }
        return res;
    }

    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

class SegTree {
    vector<int> tree;
    int size, n;

public:
    SegTree(int sz) : size(1 << int(ceil(log2(sz)) + 1)), n(size >> 1) {
        tree.resize(size + 1, 0);
    }

    void update(int idx, int val) {
        tree[idx += n] = val;
        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = tree[idx <<  1] + tree[idx << 1 | 1];
    }

    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res += tree[l++];
            if (~r & 1) res += tree[r--];
        }
        return res;
    }
};

class HLD {
    graph<int> ori;
    vector<vector<int>> g;
    vector<int> sz, dep, par, top, S;

    void dfs(int u, int p) {
        for (const auto &[v, _]: ori[u]) {
            if (v == p) continue;
            g[u].emplace_back(v);
            dfs(v, u);
        }
    }

    void dfs1(int u) {
        sz[u] = 1;
        for (auto &v : g[u]) {
            dep[v] = dep[u] + 1;
            par[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }

    int pv = 0;
    void dfs2(int u) {
        S[u] = ++pv;
        for (const auto &v : g[u]) {
            segTree.update(S[u], penguins[u]);
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
    }

    BIT segTree;
public:
    HLD(graph<int> &&G) : ori(G), segTree(G.size()) {
        int n = (int) G.size();
        g.resize(n);
        sz.resize(n);
        dep.resize(n, 0);
        par.resize(n);
        top.resize(n);
        S.resize(n, 0);

        for (int i = 1; i < n; i++) {
            if (S[i]) continue;
            top[i] = i;
            dfs(i, 0), dfs1(i), dfs2(i);
        }
    }

    void penguin(int a, int b) {
        segTree.update(S[a], b);
    }

    int excursion(int a, int b) {
        int res = 0;
        while (top[a] ^ top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            res += segTree.query(S[top[a]], S[a]);
            a = par[top[a]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        res += segTree.query(S[a], S[b]);
        return res;
    }
};

enum query_type {B, E, P};
struct query {
    query_type type;
    int a, b;
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n + 1);
    penguins.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];
    int m;
    cin >> m;
    vector<query> q(m);
    for (auto &[cmd, a, b]: q) {
        string s;
        cin >> s >> a >> b;
        switch (s[0]) {
            case 'b': {
                cmd = B;
                break;
            }
            case 'e': {
                cmd = E;
                break;
            }
            case 'p': {
                cmd = P;
                break;
            }
            default: assert(0);
        }
    }

    vector<int> ans(m);
    DisjointSet ds(n + 1);
    graph<int> g(n + 1);
    for (int i = 0; i < m; i++) {
        const auto [cmd, a ,b] = q[i];
        switch (cmd) {
            case B: {
                ans[i] = ds.find(a) != ds.find(b);
                if (ans[i]) {
                    ds.merge(a, b);
                    g[a].emplace_back(b, 1);
                    g[b].emplace_back(a, 1);
                }
                break;
            }
            case E: {
                ans[i] = ds.find(a) == ds.find(b);
                break;
            }
            case P: break;
        }
    }

    HLD solver(std::move(g));
    for (int i = 1; i <= n; i++) solver.penguin(i, v[i]);

    for (int i = 0; i < m; i++) {
        const auto [cmd, a, b] = q[i];
        switch (cmd) {
            case B: {
                if (ans[i]) cout << "yes\n";
                else cout << "no\n";
                break;
            }
            case E: {
                if (ans[i]) cout << solver.excursion(a, b) << endl;
                else cout << "impossible\n";
                break;
            }
            case P: {
                solver.penguin(a, b);
                break;
            }
        }
    }

    return 0;
}