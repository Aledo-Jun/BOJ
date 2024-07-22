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
class RangeMaxQuery {
    vector<int> tree;
    int sz, n;
public:
    RangeMaxQuery(int size) : sz(1 << int(ceil(log2(size)) + 1)), n(sz >> 1){
        tree.resize(sz, -1e9);
    }

    void update(int idx, int val) {
        tree[idx += n] = val;
        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
    }

    int query(int l, int r) {
        int res = -1e9;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (~r & 1) res = max(res, tree[r--]);
        }
        return res;
    }
};

struct market {
    int location, profit;
    market(int l, int p) : location(l), profit(p) {}
    bool operator<(const market& other) { return location < other.location; }
};

const int MAX = 500'001;
int32_t main() {
    fastIO;
    int n, up, down, home;
    cin >> n >> up >> down >> home;
    vector<vector<market>> markets(MAX + 2);
    for (int i = 0; i < n; i++) {
        int t, l, p;
        cin >> t >> l >> p;
        markets[t].emplace_back(l, p);
    }
    markets[0].emplace_back(home, 0);
    markets.back().emplace_back(home, 0);

    // dp[i][j] := max profit when covering markets up to markets[i][j]
    // dp[i][j] = max_{(r,c) s.t. opens before (i,j)}(dp[r][c] - cost((r,c)->(i,j))) + profit[i][j]
    // cost((r,c)->(i,j)) = 1) (r,c) is higher than (i,j), (loc(r,c) - loc(i,j)) * down
    //                       = loc(r,c) * down - (loc(i,j) * down)
    //                      2) (r,c) is lower  than (i,j), (loc(i,j) - loc(r,c)) * up
    //                       = -loc(r,c) * up + (loc(i,j) * up)
    // where each of second term is a constant, and the problem becomes the one to find the max value for
    // dp[r][c] - loc(r,c) * down or dp[r][c] + loc(r,c) * up
    // Now we divide the dp into two parts, up->down and down->up.
    // And let rmq_up and rmq_down store the down->'up' and up->'down' values respectively.
    // Now we can get dp[i][j] by querying rmqs and adding up the remaining term(parenthesis at 1) and 2)).

    matrix<int> dp_up(MAX + 1), dp_down(MAX + 1);
    RangeMaxQuery rmq_up(MAX + 1), rmq_down(MAX + 1);

    auto calc_up = [&](int i, int j) {
        int mx = -1e9;
        if (j)
            mx = dp_up[i][j-1] - (markets[i][j].location - markets[i][j-1].location) * up;
        mx = max({mx,
                  rmq_up.query(markets[i][j].location, MAX) + markets[i][j].location * down,
                  rmq_down.query(0, markets[i][j].location) - markets[i][j].location * up});
        return mx + markets[i][j].profit;
    };
    auto calc_down = [&](int i, int j) {
        int mx = -1e9;
        if (j != markets[i].size() - 1)
            mx = dp_down[i][j+1] - (markets[i][j+1].location - markets[i][j].location) * down;
        mx = max({mx,
                  rmq_up.query(markets[i][j].location, MAX) + markets[i][j].location * down,
                  rmq_down.query(0, markets[i][j].location) - markets[i][j].location * up});
        return mx + markets[i][j].profit;
    };

    rmq_up.update(markets[0][0].location, - markets[0][0].location * down);
    rmq_down.update(markets[0][0].location, markets[0][0].location * up);
    for (int i = 1; i <= MAX + 1; i++) {
        sort(all(markets[i]));
        dp_up[i].resize(markets[i].size());
        dp_down[i].resize(markets[i].size());
        for (int j = 0; j < markets[i].size(); j++) {
            dp_up[i][j] = calc_up(i, j);
        }
        for (int j = (int)markets[i].size() - 1; j >= 0; j--) {
            dp_down[i][j] = calc_down(i, j);
        }
        for (int j = 0; j < markets[i].size(); j++) {
            rmq_up.update(markets[i][j].location, max(dp_up[i][j], dp_down[i][j]) - markets[i][j].location * down);
            rmq_down.update(markets[i][j].location, max(dp_up[i][j], dp_down[i][j]) + markets[i][j].location * up);
        }
    }
    cout << max(dp_up[MAX + 1][0], dp_down[MAX + 1][0]);

    return 0;
}