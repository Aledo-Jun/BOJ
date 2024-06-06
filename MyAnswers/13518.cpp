//
// Created by june0 on 2024-06-06.
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

int N, sqrt_n = 400, M;
vector<int> w, R;

struct query {
    int l, r, idx, k;

    query() = default;
    query(int l, int r, int idx, int k = 0) : l(l), r(r), idx(idx), k(k) {}
    /* Add extra variables */

    bool operator<(const query &other) const {
        if (l / sqrt_n == other.l / sqrt_n)
            return ((l / sqrt_n) & 1) ? r < other.r : r > other.r;
        return l < other.l;
    }
};

class Mo {
public:
    std::vector<query> q;
    std::vector<int> ans, cnt, occupied;
    int res = 0; // if the res can be maintained, use this.

    Mo() = default;
    Mo(const std::vector<query>& q, int n) : q(q), ans(q.size()), cnt(1'000'001, 0), occupied(n, 0) {}

    void add(int i) {
        occupied[i]++;
        if (occupied[i] == 2) {
            if (--cnt[w[i]] == 0) res--;
        }
        if (occupied[i] == 1){
            if (cnt[w[i]]++ == 0) res++;
        }
    }
    void del(int i) {
        occupied[i]--;
        if (occupied[i] == 1) {
            if (cnt[w[i]]++ == 0) res++;
        }
        if (occupied[i] == 0) {
            if (--cnt[w[i]] == 0) res--;
        }
    }

    void go() {
        res = 0;
        int s = q[0].l, e = s - 1;

        for (const auto &[l, r, idx, k]: q) {
            while (s > l) add(R[--s]);
            while (e < r) add(R[++e]);
            while (s < l) del(R[s++]);
            while (e > r) del(R[e--]);

            if (k) add(R[k]);
            ans[idx] = res;
            if (k) del(R[k]);
        }

        for (const auto& elem : ans) cout << elem << endl;
    }
};

/**
 * @brief Heavy Light Decomposition to perform a query on a path in a tree
 */
class HLD {
private:
    vector<int> sz,     // size of the subtree
    depth,  // depth of the node
    parent, // parent of the node
    top,    // top of the chain the node belongs to
    S, T;   // Euler Tour

    int root;
    graph<int> adj;     // adjacent list for original tree
    vector<vector<int>> g;

    vector<bool> visited;
    void dfs(int u) { // construct g
        visited[u] = true;
        for (const auto& [v, _]: adj[u]) {
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
            parent[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) std::swap(v, g[u][0]);
        }
    }

    int pv = 0, pw = 0;
    // construct S, T, and top
    void dfs2(int u) {
        S[u] = ++pv;
        R[++pw] = u;
        for (const auto& v: g[u]) {
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
        T[u] = ++pv;
        R[++pw] = u;
    }

    /* Add something to Utilize the HLD e.g. SegTree */
    Mo solver;

    int lca(int x, int y) {
        while (top[x] ^ top[y]) {
            if (depth[top[x]] < depth[top[y]]) swap(x, y);
            x = parent[top[x]];
        }
        return depth[x] < depth[y] ? x : y;
    }

public:
    explicit
    HLD(const graph<int>& g, vector<query>& q, int root = 1) : adj(g), root(root) {
        int n = (int) g.size();
        sz.resize(n);
        depth.resize(n);
        parent.resize(n);
        top.resize(n);
        S.resize(n), T.resize(n), R.resize(n * 2);
        this->g.resize(n);
        visited.resize(n);
        dfs(root), dfs1(root), dfs2(root);

        // initialize additional variables
        for (auto& [x, y, idx, k]: q) {
            if (S[x] > S[y]) swap(x, y);
            int z = lca(x, y);
            y = S[y];
            if (x == z) {
                x = S[x];
            } else {
                x = T[x];
                k = S[z]; // add lca
            }
        }
        sort(all(q));
        solver = Mo(q, n);
    }

    void solve() {
        solver.go();
    }
}; // class HLD

int32_t main() {
    fastIO;
    cin >> N;
    w.resize(N + 1);
    for (int i = 1; i <= N; i++) cin >> w[i];
    graph<int> g(N + 1);
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        g[a].emplace_back(b, 1);
        g[b].emplace_back(a, 1);
    }

    cin >> M;
    vector<query> q(M);
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        q[i] = {x, y, i};
    }

    HLD solver(g, q);

    solver.solve();

    return 0;
}