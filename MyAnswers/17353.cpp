//
// Created by june0 on 2024-03-19.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

#ifdef ONLINE_JUDGE
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
#define int ll
namespace SegTree {
    /**
     * Segment Tree that contains the result of a query over the range.
     * @tparam T type of elements
     * @tparam func function object to be called to perform the query
     * @tparam updating_func function object to be called to update the containing element
     */
    template<typename T,
            typename func = plus<T>,
            typename updating_func = plus<T>>
    class SegTree {
    private:
        func f;
        updating_func updating_f;
        T default_query;

        vector<T> tree, arr;
        int size, height;

        T init(int node, int left, int right) {
            if (left == right) return tree[node] = arr[left];

            int mid = (left + right) >> 1;
            auto left_result = init(node << 1, left, mid);
            auto right_result = init(node << 1 | 1, mid + 1, right);
            tree[node] = f(left_result, right_result);

            return tree[node];
        }

        /**
         * Update the tree as a result of performing <i>updating_func</i> with <i>value</i> to the arr[idx]
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param idx index of array that updating is required
         * @param value the value to be used for performing <i>updating_func</i> to the arr[idx]
         */
        void _update(int node, int start, int end, int idx, T value) {
            if (idx < start || end < idx) return;

            if (start == end) {
                tree[node] = updating_f(tree[node], value);
            } else {
                int mid = (start + end) >> 1;
                _update(node << 1, start, mid, idx, value);
                _update(node << 1 | 1, mid + 1, end, idx, value);
                tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
            }
        }


        /**
         * Find the result of @p func over the array elements in range [left, right]
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param left starting index of performing @p func
         * @param right ending index of performing @p func
         * @return the result of @p func over the array elements in range [left, right]
         */
        T _query(int node, int start, int end, int left, int right) {
            if (end < left || right < start) return default_query;
            if (left <= start && end <= right) return tree[node];

            int mid = (start + end) >> 1;
            auto left_result = _query(node << 1, start, mid, left, right);
            auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
            return f(left_result, right_result);
        }

    public:
        /**
         * Constructor for a segment tree
         * @param v Array that the segment tree will be constructed from
         * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
         */
        explicit SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
            arr = v;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1);
            init(1, 0, v.size() - 1);
        }

        void update(int idx, T value) {
            _update(1, 0, arr.size() - 1, idx, value);
        }

        T query(int left, int right) {
            return _query(1, 0, arr.size() - 1, left, right);
        }

    }; // class SegTree

    class LazySegTree {
    private:
        vector<int> tree, lazy;
        vector<int> v;
        int size, height;

        int init(int node, int left, int right) {
            if (left == right) return tree[node] = v[left];

            int mid = (left + right) >> 1;
            auto left_result = init(node << 1, left, mid);
            auto right_result = init(node << 1 | 1, mid + 1, right);
            tree[node] = (left_result + right_result);

            return tree[node];
        }

        void update_lazy(int node, int start, int end) {
            if (lazy[node]) {
                tree[node] += lazy[node] * (end - start + 1);
                if (start != end) {
                    lazy[node << 1] += lazy[node];
                    lazy[node << 1 | 1] += lazy[node];
                }
                lazy[node] = 0;
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
                tree[node] += value * (end - start + 1);
                if (start != end) {
                    lazy[node << 1] += value;
                    lazy[node << 1 | 1] += value;
                }
                return;
            }

            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, s_idx, e_idx, value);
            _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
            tree[node] = (tree[node << 1] + tree[node << 1 | 1]);
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
        int _query(int node, int start, int end, int left, int right) {
            update_lazy(node, start, end);

            if (left > end || right < start) return 0;
            if (left <= start && end <= right) return tree[node];

            int mid = (start + end) >> 1;
            auto left_result = _query(node << 1, start, mid, left, right);
            auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
            return (left_result + right_result);
        }

    public:

        /**
         * Constructor for a lazy segment tree
         * @param arr  Build a segment tree from the given array
         */
        explicit LazySegTree(const vector<int> &arr) {
            v = arr;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1);
            lazy.resize(size + 1);
            init(1, 0, (int)v.size() - 1);
        }

        void update(int s_idx, int e_idx, int value) {
            _update(1, 0, (int)v.size() - 1, s_idx, e_idx, value);
        }

        int query(int left, int right) {
            return _query(1, 0, (int)v.size() - 1, left, right);
        }
    }; // class LazySegTree
} // namespace SegTree
int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n + 1, 0), pre(n + 1);
    for (int i = 1; i <= n; i++) cin >> pre[i];

    SegTree::LazySegTree segTree(v);

    int q;
    cin >> q;
    while (q--){
        int cmd; cin >> cmd;
        if (cmd == 1){
            int l, r;
            cin >> l >> r;
            segTree.update(l, r, +1);
            segTree.update(r + 1, r + 1, -(r - l + 1));
        } else {
            int x; cin >> x;
            cout << pre[x] + segTree.query(1, x) << endl;
        }
    }

    return 0;
}