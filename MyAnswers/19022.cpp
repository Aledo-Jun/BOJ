//
// Created by june0 on 2024-08-23.
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

class MinCostMaxFlow {
    const int INF = 1e9;

    struct Edge {
        int u, v, cap, rev, cost;

        Edge(int u, int v, int cap, int rev, int cost) : u(u), v(v), cap(cap), rev(rev), cost(cost) {}
    };

private:
    int n;
    vector<vector<Edge>> g;
    vector<int> dist;
    vector<Edge *> prev;

    bool bellmanFord(int s, int t) {
        dist.assign(n, INF);
        queue<int> q;
        vector<bool> is_in_q(n, false);

        dist[s] = 0;
        q.emplace(s);
        is_in_q[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            is_in_q[u] = false;
            for (auto &e: g[u]) {
                if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    prev[e.v] = &e;
                    if (!is_in_q[e.v]) {
                        is_in_q[e.v] = true;
                        q.emplace(e.v);
                    }
                }
            }
        }
        return dist[t] != INF;
    }

public:
    explicit MinCostMaxFlow(int n) : n(n), g(n), dist(n), prev(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        g[u].emplace_back(u, v, cap, g[v].size(), cost);
        g[v].emplace_back(v, u, 0, g[u].size() - 1, -cost);
    }

    pair<int, int> minCostMaxFlow(int s, int t) {
        int flow = 0, cost = 0;
        while (bellmanFord(s, t)) {
            // find minimum flow
            int curr = INF;
            for (auto e = prev[t]; e; e = prev[e->u]) {
                curr = min(curr, e->cap);
            }
            flow += curr;

            for (auto e = prev[t]; e; e = prev[e->u]) {
                cost += curr * e->cost;

                // reverse direction
                e->cap -= curr;
                g[e->v][e->rev].cap += curr;
            }
        }
        return {flow, cost};
    }
}; // class MCMF

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;

    vector<int> in(n + 1), out(n + 1);
    MinCostMaxFlow mcmf(n + n + 2);
    const int S = 0, T = n + n + 1;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        out[u] += w;
        in[v] += w;
        mcmf.addEdge(u, n + v, w, 0);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int ub = in[i] + out[i];
        mcmf.addEdge(S, i, ub, 0);
        mcmf.addEdge(n + i, T, ub, 0);
        mcmf.addEdge(i, n + i, ub, 1);
        mcmf.addEdge(n + i, i, ub, 0);
        ans += ub;
    }
    cout << ans - mcmf.minCostMaxFlow(S, T).second;

    return 0;
}