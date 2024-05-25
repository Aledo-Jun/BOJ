//
// Created by june0 on 2024-05-25.
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

template<typename T = int,
        typename Func = plus<T>,
        typename Inv_Func = minus<T>,
        T Identity = 0>
class FenWickTree {
private:
    Func f;
    Inv_Func inv_f;

    vector<T> tree;
    int size;

    void _update(int x, T val) {
        for (int i = x; i < size; i += (i & -i)) {
            tree[i] = f(tree[i], val);
        }
    }

    T _query(int x) {
        T res = Identity;
        for (int i = x; i > 0; i -= (i & -i)) {
            res = f(res, tree[i]);
        }
        return res;
    }

public:
    // Empty tree constructor
    FenWickTree(int size) : size(size) { // NOLINT
        tree.resize(size, Identity);
    }

    FenWickTree(const vector<T> &v) {
        size = (int) v.size();
        tree.resize(size);
        for (int i = 1; i < size; i++) {
            _update(i, v[i]);
        }
    }

    void update(int x, T val) {
        _update(x, val);
    }

    T query(int i) {
        return _query(i);
    }

    T query(int left, int right) {
        if (left > right) return Identity;
        return inv_f(_query(right), _query(left - 1));
    }
}; // class FenWickTree

pair<vector<int>,vector<int>> EulerTour(const graph<int>& g) {
    int n = (int) g.size() - 1;
    vector<int> S(n + 1), T(n + 1);

    vector<bool> visited(n + 1, false);
    function<void(int,int&)> dfs = [&](int u, int& d) -> void {
        S[u] = d;
        for (const auto& [v, _]: g[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            dfs(v, ++d);
        }
        T[u] = d;
    };

    int d = 1;
    dfs(1, d);

    return {S, T};
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1);
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        if (u == -1) continue;
        g[u].emplace_back(i, 1);
    }

    auto[S, T] = EulerTour(g);

    FenWickTree rsq(n + 1);

    for (int i = 0; i < m; i++) {
        int cmd, id, w;
        cin >> cmd;
        if (cmd == 1) {
            cin >> id >> w;
            rsq.update(S[id], w);
            rsq.update(T[id] + 1, -w);
        } else {
            cin >> id;
            cout << rsq.query(S[id]) << endl;
        }
    }

    return 0;
}