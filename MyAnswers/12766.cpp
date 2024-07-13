//
// Created by june0 on 2024-07-14.
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

vector<ll> dijkstra(const graph<int> &g, int start) {
    vector<ll> dist(g.size(), 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto &[v, w]: g[u]) {
            if (dist[v] > d + w) {
                pq.emplace(d + w, v);
                dist[v] = d + w;
            }
        }
    }
    return dist;
}
int32_t main() {
    fastIO;
    int n, // # of nodes
    b, // # of selectable nodes
    s, // # of groups
    r; // # of edges
    cin >> n >> b >> s >> r;

    graph<int> g(n + 1), rg(n + 1);
    for (int i = 0; i < r; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        rg[v].emplace_back(u, w);
    }

    auto dist1 = dijkstra(g, b + 1);
    auto dist2 = dijkstra(rg, b + 1);

    // let node i is in the group G whose size is g.
    // to select i, it adds (g-1)*(dist1[i] + dist2[i]) to the total cost
    // I want to make s groups s.t. minimize the total cost
    //
    // let cost(i) := dist1[i] + dist2[i]
    //     dp(i,s) := min cost to make s groups with i min cost() nodes
    // then,
    //   dp(i,s) = min_{j<i}(dp(j,s-1) + (i - j - 1)(cost(j+1) + cost(j+2) + ... + cost(i)))
    //
    // besides, let C(i,j) := (i - j - 1)(cost(j+1) + cost(j+2) + ... + cost(i))
    // then, C satisfies Quadrangle ineq. C(a,c) + C(b,d) <= C(a,d) + C(b,c) for a <= b <= c <= d
    // (proof is trivial if you visualize it)
    // So we can use DnC Optimization

    vector<ll> cost(b + 1, 0), prefix_cost(b + 1, 0);
    for (int i = 1; i <= b; i++) cost[i] = dist1[i] + dist2[i];
    sort(all(cost));
    for (int i = 1; i <= b; i++) prefix_cost[i] = prefix_cost[i - 1] + cost[i];

    auto C = [&](int i, int j) -> ll {
        return ll(i - j - 1) * (prefix_cost[i] - prefix_cost[j]);
    };

    vector<ll> dp(b + 1), ndp(b + 1);
    auto dnc = [&](auto&& self, int S, int s, int e, int l, int r) -> void {
        if (s > e) return;
        int m = (s + e) >> 1;
        int opt;
        ndp[m] = opt = -1;
        for (int j = max(l, m - m / S); j <= min(m - 1, r); j++) {
            ll curr = dp[j] + C(m, j);
            if (ndp[m] == -1 || ndp[m] > curr) {
                ndp[m] = curr;
                opt = j;
            }
        }
        self(self, S, s, m - 1, l, opt);
        self(self, S, m + 1, e, opt, r);
    };

    for (int i = 1; i <= b; i++) {
        dp[i] = C(i, 0);
    }
    for (int i = 2; i <= s; i++) dnc(dnc, i, i, b, 0, b), swap(dp, ndp);

    cout << dp[b];

    return 0;
}