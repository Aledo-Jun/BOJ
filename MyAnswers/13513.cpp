//
// Created by june0 on 2024-06-11.
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

/**
 * @brief Removable Priority Queue
 */
template<typename T, typename Container = vector<T>, typename Comp = less<T>>
class PQ {
    priority_queue<T, Container, Comp> pq, removed;

public:
    void emplace(int x) { pq.emplace(x); }
    void erase(int x) { removed.emplace(x); }
    void refresh() {
        while (!removed.empty() && pq.top() == removed.top()) {
            pq.pop();
            removed.pop();
        }
    }
    int top() {
        refresh();
        return pq.top();
    }
    int size() {
        refresh();
        return pq.size();
    }
    bool empty() {
        refresh();
        return pq.empty();
    }
};

const int MAX = 100'001;
const int INF = 1e9;

class CentroidTree {
    int n, root;
    int MAX_BIT;
    graph<int> g;
    vector<int> sz,    // size of the subtree
    depth, // depth of the node
    dist,  // distance from the initial root
    tree,  // centroid tree(tree[i] = parent of i at the centroid tree)
    S, T, E;  // Euler Tour
    vector<vector<int>> parent;

    int pw = 0;
    int dfs(int u, int p) {
        sz[u] = 1;
        E[++pw] = u;
        S[u] = pw;
        for (const auto& [v, w]: g[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dist[v] = dist[u] + w;
            parent[v][0] = u;
            for (int i = 1; i < MAX_BIT; i++) {
                parent[v][i] = parent[parent[v][i - 1]][i - 1];
            }
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
        fill(all(lg2), -1);
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

    int get_dist(int u, int v) {
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
    vector<bool> color;
    vector<unordered_map<int,PQ<int>>> sub;
    vector<multiset<int>> sub_mx;
    PQ<int> ans;
    int cnt = 0;

    explicit
    CentroidTree(const graph<int>& g, int root = 1) : g(g), n((int)g.size()), root(root) {
        sz.resize(n, 0);
        depth.resize(n, 0);
        dist.resize(n, 0);
        S.resize(n), T.resize(n), E.resize(n * 2);
        tree.resize(n);
        MAX_BIT = std::ceil(std::log2(n));
        parent.resize(n, vector<int>(MAX_BIT));

        color.resize(n);
        sub.resize(n);
        sub_mx.resize(n);
        ans.emplace(0);

        dfs(root, -1);
        lca_prepare();
        build_centroid_tree(root);

        for (int i = 1; i < n; i++) {
            sub[i][i] = PQ<int>();
            if (tree[i]) sub[tree[i]][i] = PQ<int>();
        }
    }

    void update(int u) {
        color[u] = !color[u];
        if (color[u]) cnt++;
        else cnt--;

        // climb up the centroid tree and update ancestor's set
        for (int v = u, prev = u;; prev = v, v = tree[v]) {
            int d = get_dist(u, v);
            auto &ms = sub[v][prev];
            if (color[u]) {
                if (ms.empty() || ms.top() < d) {
                    int prev_ans = get_ans(v);
                    if (!ms.empty()) {
                        sub_mx[v].erase(ms.top());
                    }
                    sub_mx[v].emplace(d);
                    int curr_ans = get_ans(v);

                    if (prev_ans != -1) ans.erase(prev_ans);
                    if (curr_ans != -1) ans.emplace(curr_ans);

                    ms.emplace(d);
                } else {
                    ms.emplace(d);
                }
            } else {
                int mx = ms.top();
                ms.erase(d);
                if (ms.empty() || ms.top() < mx) {
                    int prev_ans = get_ans(v);
                    sub_mx[v].erase(mx);
                    if (!ms.empty()) sub_mx[v].emplace(ms.top());
                    int curr_ans = get_ans(v);

                    if (prev_ans != -1) ans.erase(prev_ans);
                    if (curr_ans != -1) ans.emplace(curr_ans);
                }
            }
            if (tree[v] == v) break;
        }
    }
    int get_ans(int u) {
        if (sub_mx[u].size() < 2) return -1;
        return *sub_mx[u].rbegin() + *next(sub_mx[u].rbegin());
    }

    int query() {
        if (cnt == 0) return -1;
        if (cnt == 1) return 0;
        return ans.top();
    }
} ;

int32_t main() {
    fastIO;
    int n, q;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    CentroidTree solver(g);

    for (int i = 1; i <= n; i++) solver.update(i);

    cin >> q;
    while (q--) {
        int cmd, x;
        cin >> cmd;
        if (cmd == 1) {
            cin >> x;
            solver.update(x);
        } else {
            cout << solver.query() << endl;
        }
    }

    return 0;
}