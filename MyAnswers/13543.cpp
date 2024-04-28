//
// Created by june0 on 2024-04-28.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
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

unsigned C[11][11]; // C[n][r] -> nCr
void init_binomial() {
    C[0][0] = 1;
    for (int i = 1; i < 11; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

template<typename T>
class SplayTree {
    struct Node {
        Node *l, *r, *p;
        T key; // value stored in the node
        int cnt; // # of nodes in the subtree

        /* Add more variables if needed */
        unsigned ans[11];

        Node() : l(nullptr), r(nullptr), p(nullptr), key(T(0)), cnt(1) {}
        Node(T key) : l(nullptr), r(nullptr), p(nullptr), key(key), cnt(1) {
            std::fill_n(ans, 11, key);
        }
    } *tree;

    // modify if needed
    void update(Node *x) {
        x->cnt = 1;
        if (x->l) x->cnt += x->l->cnt;
        if (x->r) x->cnt += x->r->cnt;

        int l_cnt = x->l ? x->l->cnt : 0;
        unsigned pow_[11]; pow_[0] = 1;
        for (int i = 1; i < 11; i++) pow_[i] = pow_[i - 1] * (l_cnt + 1);
        for (int i = 0; i < 11; i++) {
            x->ans[i] = pow_[i] * x->key;
            if (x->l) x->ans[i] += x->l->ans[i];
            if (x->r)
                for (int j = 0; j <= i; j++)
                    x->ans[i] += x->r->ans[j] * pow_[i - j] * C[i][j];
        }

    }

    void rotate(Node *x) {
        Node *p = x->p;
        Node *b;
        if (x == p->l) {
            p->l = b = x->r;
            x->r = p;
        } else {
            p->r = b = x->l;
            x->l = p;
        }
        x->p = p->p;
        p->p = x;
        if (b) b->p = p;
        (x->p ? p == x->p->l ? x->p->l : x->p->r : tree) = x;

        update(p);
        update(x);
    }

    void splay(Node *x) {
        while (x->p) {
            Node *p = x->p;
            Node *g = p->p;
            if (g) rotate((x == p->l) == (p == g->l) ? p : x);
            rotate(x);
        }
    }

public:
    explicit SplayTree(const std::vector<T> &v) {
        Node *p = tree = new Node(0);
        for (const auto& e : v) {
            p->r = new Node(e);
            p->r->p = p;
            p = p->r;
        }
        p->r = new Node(0);
        p->r->p = p;
        p = p->r;

        while (p) {
            update(p);
            p = p->p;
        }
    }

    /**
     * Insert a new node with the given key
     * @param key the key value to insert
     */
    void insert(T key) {
        Node *p = tree, **pp;
        if (!p) {
            Node *x = new Node(key);
            tree = x;
            return;
        }
        while (true) {
            if (key == p->key) return; // no duplicate allowed
            if (key < p->key) {
                if (!p->l) {
                    pp = &p->l;
                    break;
                }
                p = p->l;
            } else {
                if (!p->r) {
                    pp = &p->r;
                    break;
                }
                p = p->r;
            }
        }
        Node *x = new Node(key);
        *pp = x;  // p -> x
        x->p = p; // x -> p

        splay(x); // Crucial!
    }

    /**
     * The node with the given key becomes the root node after the function call
     * @param key the key value to find
     * @return true if found, false otherwise
     */
    bool find(T key) {
        Node *p = tree;
        if (!p) return false;
        while (p) {
            if (key == p->key) break;
            if (key < p->key) {
                if (!p->l) break;
                p = p->l;
            } else {
                if (!p->r) break;
                p = p->r;
            }
        }
        splay(p);
        return key == p->key;
    }

    void erase(T key) {
        if (!find(key)) return;
        Node *p = tree;
        if (p->l) {
            if (p->r) {
                tree = p->l;
                tree->p = nullptr;

                Node *x = tree;
                while (x->r) x = x->r;
                x->r = p->r;
                p->r->p = x;
                splay(x);
                delete p;
                return;
            }
            tree = p->l;
            tree->p = nullptr;
            delete p;
            return;
        }
        if (p->r) {
            tree = p->r;
            tree->p = nullptr;
            delete p;
            return;
        }
        delete p;
        tree = nullptr;
    }

    /**
     * Make the root node to be the k-th
     */
    void find_kth(int k) {
        Node *x = tree;
        while (true) {
            while (x->l && x->l->cnt > k) x = x->l;
            if (x->l) k -= x->l->cnt;
            if (!k--) break;
            x = x->r;
        }
        splay(x);
    }

    /**
     * Make the tree->r->l to represent the given interval [l,r]
     */
    void interval(int l, int r) {
        find_kth(l - 1);
        auto *p = tree;
        tree = p->r;
        tree->p = nullptr;
        find_kth(r - l + 1);
        p->r = tree;
        tree->p = p;
        tree = p;
    }

    /**
     * Insert a new node with the key of val into the given pos
     */
    void insert(int pos, T val) {
        find_kth(pos);
        auto *p = tree, *x = new Node(val);
        x->p = p;
        p->l->p = x;
        x->l = p->l;
        p->l = x;
        splay(x);
    }

    /**
     * Erase the node at the given pos
     */
    void erase_at(int pos) {
        interval(pos, pos);
        auto *x = tree->r->l;
        x->p->l = nullptr;
        splay(x->p);
        delete x;
    }

    /**
     * Update the node's key at pos to val
     */
    void update(int pos, T val) {
        find_kth(pos);
        tree->key = val;
        update(tree);
    }

    unsigned query(int l, int r, int k) {
        interval(l, r);
        return tree->r->l->ans[k];
    }
};


int32_t main() {
    fastIO;
    init_binomial();
    int n;
    cin >> n;
    vector<unsigned> v(n);
    for (auto& e : v) cin >> e;
    SplayTree<unsigned> splayTree(v);

    int m;
    cin >> m;
    while (m--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int pos, val;
            cin >> pos >> val;
            splayTree.insert(pos + 1, val);
        } else if (cmd == 2) {
            int pos;
            cin >> pos;
            splayTree.erase_at(pos + 1);
        } else if (cmd == 3) {
            int pos, val;
            cin >> pos >> val;
            splayTree.update(pos + 1, val);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            cout << splayTree.query(l + 1, r + 1, k) << endl;
        }
    }

    return 0;
}