//
// Created by june0 on 2024-08-22.
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

int P[23001];

template<typename flow_t, std::enable_if_t<std::is_arithmetic_v<flow_t>>* = nullptr>
class Dinic_Large {
private:
    struct Edge {
        int u, v, rev, idx;
        flow_t cap, f = 0;
        bool is_back;
        Edge(int u, int v, flow_t cap, int rev, int idx, bool back)
                : u(u), v(v), cap(cap), rev(rev), idx(idx), is_back(back) {}
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge &e: g[u]) {
                if (e.cap - e.f > 0 && level[e.v] == -1) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }

        return level[t] != -1;
    }

    flow_t dfs(int u, int t, flow_t flow) {
        if (u == t)
            return flow;

        for (; ptr[u] < g[u].size(); ptr[u]++) {
            Edge &e = g[u][ptr[u]];

            if (e.cap - e.f > 0 && level[e.v] == level[u] + 1) {
                flow_t bottleneck = dfs(e.v, t, min(flow, e.cap - e.f));

                if (bottleneck > 0) {
                    e.f += bottleneck;
                    g[e.v][e.rev].f -= bottleneck;
                    return bottleneck;
                }
            }
        }
        return 0;
    }

public:
    static constexpr flow_t INF = std::numeric_limits<flow_t>::max();

    explicit Dinic_Large(int n) : n(n), g(n), level(n), ptr(n) {}

    void addEdge(int u, int v, flow_t cap, int idx = -1) {
        g[u].emplace_back(u, v, cap, g[v].size(), idx, false);
        g[v].emplace_back(v, u, 0, g[u].size() - 1, idx, true);
    }

    flow_t maxFlow(int s, int t) {
        flow_t flow = 0;

        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (true) {
                flow_t f = dfs(s, t, INF);
                if (f == 0) break;
                flow += f;
            }
        }

        return flow;
    }

    const vector<vector<Edge>>& get_graph() { return g; }
};

template <typename flow_t, template<typename> class MaxFlow = Dinic_Large>
class MaxFlowLowerBound {
    MaxFlow<flow_t> maxFlow;
    vector<flow_t> demand, low;
    int n; // # of vertices - (src, sink)
    flow_t pD = 0, mD = 0; // sum of demands(plus, minus)
    int S, T; // src, sink

public:
    explicit MaxFlowLowerBound(int sz) : maxFlow(sz + 2), demand(sz, 0), n(sz), S(sz), T(sz + 1) {}
    MaxFlowLowerBound(const vector<flow_t> &init_demand) : MaxFlowLowerBound(init_demand.size()) {
        demand = init_demand;
    }

    void addEdge(int u, int v, flow_t lb, flow_t ub) {
        maxFlow.addEdge(u, v, (ub - lb) >> 1, low.size());
        demand[u] += lb;
        demand[v] -= lb;
        low.emplace_back(lb);
    }

    void init(int s, int t) {
        for (int i = 0; i < n; i++) {
            if (i == s || i == t) {
                if (demand[i] < 0) {
                    maxFlow.addEdge(S, i, (-demand[i] + 1) / 2);
                    mD -= demand[i];
                } else if (demand[i] > 0) {
                    maxFlow.addEdge(i, T, (demand[i] + 1) / 2);
                    pD += demand[i];
                }
            } else {
                if (abs(demand[i]) & 1) {
                    cout << -1;
                    exit(0);
                }
                if (demand[i] < 0) {
                    maxFlow.addEdge(S, i, -demand[i] / 2);
                    mD -= demand[i];
                } else if (demand[i] > 0) {
                    maxFlow.addEdge(i, T, demand[i] / 2);
                    pD += demand[i];
                }
            }
        }
    }

    bool is_there_circulation(int s, int t) {
        maxFlow.addEdge(t, s, maxFlow.INF);
        init(s, t);
        auto flow = maxFlow.maxFlow(S, T) * 2 - (demand[s] & 1);
        return flow == pD && flow == mD;
    }

    flow_t max_flow(int s, int t) {
        if (is_there_circulation(s, t)) {
            return maxFlow.maxFlow(s, t) * 2 - (demand[s] & 1);
        } else {
            return -1;
        }
    }

    vector<flow_t> solve() {
        const auto &g = maxFlow.get_graph();
        vector<flow_t> res(low.size());

        for (int i = 0; i < n; i++) {
            for (const auto &[u, v, rev, idx, cap, f, is_back]: g[i]) {
                if (is_back || idx == -1) continue;
                res[idx] = (low[idx] + f * 2);
            }
        }
        return res;
    }
}; // class MaxFlowLowerBound

int32_t main() {
    fastIO;
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    MaxFlowLowerBound<ll> solver(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, c, p;
        cin >> u >> v >> c >> p;
        solver.addEdge(u, v, p, c);
    }
    auto f = solver.max_flow(s, t);
    if (f == -1) return cout << -1, 0;
    else cout << f << endl;

    auto res = solver.solve();

    for (int i = 0; i < m; i++) cout << res[i] << endl;

    return 0;
}