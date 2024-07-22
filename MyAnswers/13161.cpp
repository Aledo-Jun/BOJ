//
// Created by june0 on 2024-07-22.
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

class Dinic {
    int n;
    vector<vector<int>> g, flow, cap;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        fill(all(level), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto &v: g[u]) {
                if (level[v] == -1 && cap[u][v] - flow[u][v] > 0) {
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int curr_flow) {
        if (u == t)
            return curr_flow;

        for (; ptr[u] < g[u].size(); ptr[u]++) {
            auto &v = g[u][ptr[u]];

            if (cap[u][v] - flow[u][v] > 0 && level[v] == level[u] + 1) {
                int bottleneck = dfs(v, t, min(curr_flow, cap[u][v] - flow[u][v]));

                if (bottleneck > 0) {
                    flow[u][v] += bottleneck;
                    flow[v][u] -= bottleneck;
                    return bottleneck;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int sz) : n(sz), g(sz), level(sz), ptr(sz),
                    flow(sz, vector<int>(sz, 0)), cap(sz, vector<int>(sz, 0)) {}

    void add_edge(int u, int v, int c, bool is_directed = true) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        cap[u][v] += c;
        if (!is_directed) cap[v][u] += c;
    }

    int max_flow(int s, int t) {
        int res = 0;
        while (bfs(s, t)) {
            fill(all(ptr), 0);
            while(int f = dfs(s, t, INT_MAX)) res += f;
        }
        return res;
    }

    auto min_cut(int s) {
        vector<bool> visited(n, false);
        queue<int> q;
        visited[s] = true;
        q.emplace(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto &v : g[u]) {
                if (!visited[v] && cap[u][v] - flow[u][v] > 0) {
                    visited[v] = true;
                    q.emplace(v);
                }
            }
        }
        return visited;
    }

};

int32_t main() {
    fastIO;
    int n;
    cin >> n;

    int s = 0, e = n + 1;
    Dinic dinic(n + 2);

    for (int t, i = 1; i <= n; i++) {
        cin >> t;
        if (t == 1) dinic.add_edge(s, i, 1e9);
        if (t == 2) dinic.add_edge(i, e, 1e9);
    }

    for (int i = 1; i <= n; i++) {
        for (int c, j = 1; j <= n; j++) {
            cin >> c;
            if (i < j) {
                dinic.add_edge(i, j, c);
                dinic.add_edge(j, i, c);
            }
        }
    }

    cout << dinic.max_flow(s, e) << endl;

    auto check = dinic.min_cut(s);

    for (int i = 1; i <= n; i++) if (check[i]) cout << i << ' ';
    cout << endl;
    for (int i = 1; i <= n; i++) if (!check[i]) cout << i << ' ';
    cout << endl;

    return 0;
}