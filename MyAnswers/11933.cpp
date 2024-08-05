//
// Created by june0 on 2024-08-05.
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

const ll INF = 0x3f3f3f3f3f3f3f3f;
/**
 * @brief Centroid Tree implementation
 */
class CentroidTree {
    int n, root;
    int MAX_BIT;
    graph<int> g;
    vector<int> sz,    // size of the subtree
    depth, // depth of the node
    tree,  // centroid tree(tree[i] = parent of i at the centroid tree)
    S, T, E;  // Euler Tour
    vector<ll> dist;  // distance from the initial root

    int pw = 0;
    int dfs(int u, int p) {
        sz[u] = 1;
        E[++pw] = u;
        S[u] = pw;
        for (const auto& [v, w]: g[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dist[v] = dist[u] + w;
            sz[u] += dfs(v, u);
            E[++pw] = u;
        }
        return sz[u];
    }

    vector<int> pw2, lg2;
    vector<vector<pair<int,int>>> ST;
    void lca_prepare(){
        pw2.resize(MAX_BIT);
        pw2[0] = 1;
        for (int i = 1; i < MAX_BIT; i++) pw2[i] = pw2[i - 1] << 1;

        lg2.resize(n * 2);
        fill(lg2.begin(), lg2.end(), -1);
        for (int i = 0; i < MAX_BIT; i++) if (pw2[i] < n * 2) lg2[pw2[i]] = i;
        for (int i = 1; i < n * 2; i++) if (lg2[i] == -1) lg2[i] = lg2[i - 1];

        ST.resize(MAX_BIT, vector<pair<int,int>>(n * 2));
        for (int i = 1; i < n * 2; i++) ST[0][i] = {depth[E[i]], E[i]};

        for(int k = 1; k < MAX_BIT; k++) {
            for (int i = 1; i < n * 2; i++) {
                if (i + pw2[k - 1] > n * 2) continue;
                ST[k][i] = min(ST[k - 1][i], ST[k - 1][i + pw2[k - 1]]);
            }
        }
    }

    int lca(int u, int v) {
        int l = S[u], r = S[v];
        if (l > r) swap(l, r);
        int k = lg2[r - l + 1];
        return min(ST[k][l], ST[k][r - pw2[k] + 1]).second;
    }

    ll get_dist(int u, int v) {
        return dist[u] + dist[v] - 2 * dist[lca(u, v)];
    }

    int get_centroid(int u) {
        for (const auto& [v, w]: g[u]) {
            if (sz[u] >> 1 < sz[v] && sz[v] < sz[u]) {
                sz[u] -= sz[v];
                sz[v] += sz[u];
                return get_centroid(v);
            }
        }
        return u;
    }

    void build_centroid_tree(int u, int p = -1) {
        u = get_centroid(u);

        if (p == -1) tree[u] = u;
        else tree[u] = p;

        for (const auto& [v, _]: g[u])
            if (sz[v] < sz[u])
                build_centroid_tree(v, u);
    }

public:
    CentroidTree() = default;

    explicit
    CentroidTree(const graph<int>& g, int root = 1) : g(g), n((int)g.size()), root(root) {
        sz.resize(n, 0);
        depth.resize(n, 0);
        dist.resize(n, 0);
        S.resize(n), T.resize(n), E.resize(n * 2);
        tree.resize(n);
        MAX_BIT = std::ceil(std::log2(n)) + 1;

        dfs(root, -1);
        lca_prepare();
        build_centroid_tree(root);

        x_dist.resize(n, INF);
    }

    vector<ll> x_dist;
    void update(int u) {
        for (int v = u;; v = tree[v]) {
            x_dist[v] = min(x_dist[v], get_dist(u, v));

            if (tree[v] == v) break;
        }
    }
    ll query(int u) {
        ll res = INF;
        for (int v = u;; v = tree[v]) {
            res = min(res, x_dist[v] + get_dist(u, v));

            if (tree[v] == v) break;
        }
        return res;
    }

    void clear(int u) {
        for (int v = u;; v = tree[v]) {
            x_dist[v] = INF;

            if (tree[v] == v) break;
        }
    }
}; // class CentroidTree

graph<int> g;
CentroidTree solver;

void Init(int N, vector<int> &A, vector<int> &B, vector<int> &D) {
    g.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        g[A[i]+1].emplace_back(B[i]+1, D[i]);
        g[B[i]+1].emplace_back(A[i]+1, D[i]);
    }
    solver = CentroidTree(g);
}

ll Query(int S, vector<int> &X, int T, vector<int> &Y) {
    ll ans = INF;
    for (int i = 0; i < S; i++) solver.update(X[i]+1);
    for (int i = 0; i < T; i++) ans = min(ans, solver.query(Y[i]+1));
    for (int i = 0; i < S; i++) solver.clear(X[i]+1);
    return ans;
}

int32_t main() {
    fastIO;
    int n, q;
    cin >> n >> q;
    vector<int> a(n-1), b(n-1), d(n-1);
    for (int i = 0; i < n - 1; i++) cin >> a[i] >> b[i] >> d[i];
    Init(n, a, b, d);

    while (q--) {
        int s, t;
        cin >> s >> t;
        vector<int> x(s), y(t);
        for (auto &e : x) cin >> e;
        for (auto &e : y) cin >> e;

        cout << Query(s, x, t, y) << endl;
    }

    return 0;
}