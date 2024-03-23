//
// Created by june0 on 2024-03-23.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>

#include <utility>
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
 *  "Premature optimization is the _root_ of all evil."
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

template<int IndexSize = 26>
class Aho_Corasick {
    using Index_Fn = function<int(unsigned char)>;
private:
    struct TrieNode {
        TrieNode* children[IndexSize];
        TrieNode* fail;
        int isEndOf;

        TrieNode() : isEndOf(-1), fail(nullptr) {
            fill(children, children + IndexSize, nullptr);
        }
        ~TrieNode() {
            for (auto child : children) delete child;
        }

        void insert(const string& word, int& sz, const Index_Fn& index_of) {
            TrieNode* current = this;
            for (const auto c: word) {
                int index = index_of(c);
                if (current->children[index] == nullptr)
                    current->children[index] = new TrieNode;

                current = current->children[index];
            }
            current->isEndOf = sz++;
        }
    };

    TrieNode* _root_;
    bool is_initialized = false;
    int _size_;
    Index_Fn _index_fn_;

public:
    explicit Aho_Corasick(Index_Fn index_fn) : _root_(new TrieNode), _size_(0), _index_fn_(std::move(index_fn)) {}

    ~Aho_Corasick() { delete _root_; }

    void init() {
        queue<TrieNode*> q;
        q.emplace(_root_);
        _root_->fail = _root_;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            for (int i = 0; i < IndexSize; i++) {
                auto next = current->children[i];
                if (next == nullptr) continue;

                if (current == _root_) next->fail = _root_;
                else {
                    auto fail_node = current->fail;
                    while (fail_node != _root_ && fail_node->children[i] == nullptr)
                        fail_node = fail_node->fail;
                    if (fail_node->children[i] != nullptr) fail_node = fail_node->children[i];

                    next->fail = fail_node;
                }
                if (next->fail->isEndOf != -1)
                    next->isEndOf = next->fail->isEndOf;

                q.emplace(next);
            }
        }
    }

    void insert(const string& word) {
        _root_->insert(word, _size_, _index_fn_);
    }

    int count(const string& word) {
        if (!is_initialized) {
            init();
            is_initialized = true;
        }

        int res = 0;
        auto current = _root_;
        for (const auto c : word) {
            int index = _index_fn_(c);
            while (current != _root_ && current->children[index] == nullptr)
                current = current->fail;
            if (current->children[index] != nullptr)
                current = current->children[index];

            if (current->isEndOf != -1) {
                res++;
            }
        }
        return res;
    }

    void clear() {
        delete _root_;
        _root_ = new TrieNode;
        is_initialized = false;
        _size_ = 0;
    }
};

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        string dna, marker;
        cin >> n >> m >> dna >> marker;

        Aho_Corasick<4> solver([](const unsigned char c) -> int {
            switch (c) {
                case 'A': return 0;
                case 'C': return 1;
                case 'G': return 2;
                case 'T': return 3;
                default: throw std::runtime_error("invalid string");
            }
        });
        solver.insert(marker);
        for (auto it1 = marker.begin(); it1 != marker.end() - 1; it1++) {
            for (auto it2 = it1 + 1; it2 != marker.end(); it2++) {
                reverse(it1, it2 + 1);
                solver.insert(marker);
                reverse(it1, it2 + 1);
            }
        }
        cout << solver.count(dna) << endl;
    }
    return 0;
}