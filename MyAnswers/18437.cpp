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

template<typename T,
        typename func = plus<T>,
        typename updating_func = plus<T>,
        typename updating_func2 = updating_func>
class LazySegTree {
private:
    func f;
    updating_func updating_f;
    updating_func2 lazy_to_tree; // may be needed or not, IDK

    vector<T> tree, lazy;
    vector<T> v;
    int size, height;
    T default_lazy;
    T default_query;

    T init(int node, int left, int right) {
        if (left == right) return tree[node] = v[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node] = f(left_result, right_result);

        return tree[node];
    }

    void update_lazy(int node, int start, int end) {
        if (lazy[node] != default_lazy) {
            tree[node] = lazy_to_tree(tree[node], lazy[node] * (end - start + 1));
            if (start != end) {
                lazy[node << 1] = updating_f(lazy[node << 1], lazy[node]);
                lazy[node << 1 | 1] = updating_f(lazy[node << 1 | 1], lazy[node]);
            }
            lazy[node] = default_lazy;
        }
    }

    /**
     * Update the tree as a result of adding values to the array from s_idx to e_idx
     * @param node current node index in the tree
     * @param start starting index that the current node is covering
     * @param end ending index that the current node is covering
     * @param s_idx starting index that updating is required
     * @param e_idx ending index that updating is required
     * @param value the value to be added to the array
     */
    void _update(int node, int start, int end, int s_idx, int e_idx, int value) {
        update_lazy(node, start, end);

        if (e_idx < start || end < s_idx) return;

        if (s_idx <= start && end <= e_idx) {
            lazy[node] = updating_f(lazy[node], value);
            update_lazy(node, start, end);
            return;
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, s_idx, e_idx, value);
        _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
        tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
    }

    /**
     * Find the sum of the array elements in range [left, right]
     * @param node current node index in the tree
     * @param start starting index that the current node is covering
     * @param end ending index that the current node is covering
     * @param left starting index of summation
     * @param right ending index of summation
     * @return the sum of the array elements in range [left, right]
     */
    T _query(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);

        if (end < left || right < start) return default_query;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return f(left_result, right_result);
    }

public:

    /**
     * Constructor for a lazy segment tree
     * @param arr  Build a segment tree from the given array
     */
    LazySegTree(const vector<int> &arr, T default_query, T default_lazy)
            : default_query(std::move(default_query)),
              default_lazy(std::move(default_lazy))
    {
        v = arr;
        height = (int) ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        lazy.resize(size + 1, default_lazy);
        init(1, 0, v.size() - 1);
    }

    void update(int s_idx, int e_idx, T value) {
        if (s_idx > e_idx) return;
        _update(1, 0, v.size() - 1, s_idx, e_idx, value);
    }

    T query(int left, int right) {
        if (left > right) return 0;
        return _query(1, 0, v.size() - 1, left, right);
    }
}; // class LazySegTree

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

struct replacement {
    int operator()(int l, int r) const {
        return r;
    }
};

int32_t main() {
    fastIO;
    int n, m;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        if (u == 0) continue;
        g[u].emplace_back(i, 1);
    }

    auto[S, T] = EulerTour(g);

    vector<int> tree(n + 1, 1);
    LazySegTree<int,plus<>,replacement> rsq(tree, 0, -1);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int cmd, id;
        cin >> cmd >> id;
        if (cmd == 1) {
            rsq.update(S[id] + 1, T[id], 1);
        } else if (cmd == 2) {
            rsq.update(S[id] + 1, T[id], 0);
        } else {
            cout << rsq.query(S[id] + 1, T[id]) << endl;
        }
    }

    return 0;
}