//
// Created by june0 on 2024-05-29.
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

int n;

template<typename T>
class SegTree {
private:
    vector<T> tree, tree2;
    int size, height;

    void init(int node, int left, int right) {
        if (left == right) {
            tree[node] = 0;
            tree2[node] = 1;
        } else {
            int mid = (left + right) >> 1;
            init(node << 1, left, mid);
            init(node << 1 | 1, mid + 1, right);
            tree2[node] = tree2[node << 1] + tree2[node << 1 | 1];
        }
    }

    void _update(int node, int start, int end, int l, int r, int value) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            tree[node] += value;
        } else {
            int mid = (start + end) / 2;
            _update(2 * node, start, mid, l, r, value);
            _update(2 * node + 1, mid + 1, end, l, r, value);
        }
        // update visibility(tree2) according to count(tree)
        if (tree[node] > 0) tree2[node] = 0;
        else if (start == end) tree2[node] = 1;
        else tree2[node] = tree2[node << 1] + tree2[node << 1 | 1];
    }

public:
    SegTree() {
        height = (int) ceil(log2(n));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        tree2.resize(size + 1);
        init(1, 1, n);
    }

    void update(int l, int r, T value) {
        if (l > r) return;
        _update(1, 1, n, l, r, value);
    }

    int find_kth(int k, int node = 1, int start = 1, int end = n) {
        if (start == end) return start;
        int mid = (start + end) >> 1;
        if (tree2[node << 1] >= k)
            return find_kth(k, node << 1, start, mid);
        else
            return find_kth(k - tree2[node << 1], node << 1 | 1, mid + 1, end);
    }

    int get_total_visible() {
        return tree2[1];
    }
}; // class SegTree

array<vector<int>,3> EulerTour(const graph<int>& g) {
    vector<int> S(n + 1), T(n + 1), R(n + 1);

    vector<bool> visited(n + 1, false);
    function<void(int,int&)> dfs = [&](int u, int& d) -> void {
        S[u] = d;
        R[d] = u;
        for (const auto& [v, _]: g[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            dfs(v, ++d);
        }
        T[u] = d;
    };

    int d = 1;
    dfs(1, d);

    return {S, T, R};
}

int32_t main() {
    fastIO;
    int m;
    cin >> n >> m;
    graph<int> g(n + 1);
    for (int u = 1, i; u <= n; u++) {
        cin >> i;
        for (int x; i; i--) {
            cin >> x;
            g[u].emplace_back(x, 1);
        }
    }

    auto [S, T, R] = EulerTour(g);
    vector<bool> toggled(n + 1, false);
    toggled[1] = true;

    SegTree<int> segTree;
    // initialize to be toggled off except folder #1
    for (int i = 2; i <= n; i++) {
        segTree.update(S[i] + 1, T[i], 1);
    }

    int ptr = 2;
    while (m--) {
        string cmd;
        cin >> cmd;
        if (cmd[0] == 't') {
            int idx = R[segTree.find_kth(ptr)];
            if (toggled[idx])
                segTree.update(S[idx] + 1, T[idx], +1);
            else {
                segTree.update(S[idx] + 1, T[idx], -1);
            }
            toggled[idx] = !toggled[idx];
        } else {
            int k;
            cin >> k;
            ptr += k;
            int total = segTree.get_total_visible();
            if (ptr < 2) ptr = 2;
            else if (total < ptr) ptr = total;
            cout << R[segTree.find_kth(ptr)] << endl;
        }
    }

    return 0;
}