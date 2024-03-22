//
// Created by june0 on 2024-03-22.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
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

#ifdef NONLINE_JUDGE
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

vector<int> ans;

/**
 * Aho-Corasick algorithm for string-searching in linear time(maybe? worst quadratic)
 * @tparam size size of the input character set(default is english alphabet, 26)
 * @tparam base the starting character of the set above(default is 'a')
 */
template<int size = 26, char base = 'a'>
class Aho_Corasick {
private:
    struct TrieNode {
        TrieNode* children[size];
        TrieNode* fail;
        int isEndOf;

        TrieNode() : isEndOf(-1), fail(nullptr) {
            fill(children, children + size, nullptr);
        }
        ~TrieNode() {
            for (auto child : children)
                delete child;
        }

        void insert(const string& word) {
            TrieNode* current = this;
            for (char c: word) {
                int index = c - base;
                if (current->children[index] == nullptr)
                    current->children[index] = new TrieNode;

                current = current->children[index];
            }
            current->isEndOf = sz++;
            lenOfPattern.emplace_back(word.size());
        }
    };

    TrieNode* root;
    bool is_initialized = false;
    static vector<int> lenOfPattern;
    static int sz;

public:
    void init() {
        queue<TrieNode*> q;
        q.emplace(root);
        root->fail = root;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            for (int i = 0; i < size; i++) {
                auto next = current->children[i];
                if (next == nullptr) continue;

                if (current == root) next->fail = root;
                else {
                    auto fail_node = current->fail;
                    while (fail_node != root && fail_node->children[i] == nullptr)
                        fail_node = fail_node->fail;
                    if (fail_node->children[i] != nullptr) fail_node = fail_node->children[i];

                    next->fail = fail_node;
                }
                if (next->fail->isEndOf != -1 &&
                    (next->isEndOf == -1 || lenOfPattern[next->isEndOf] < lenOfPattern[next->fail->isEndOf]))
                    next->isEndOf = next->fail->isEndOf;

                q.emplace(next);
            }
        }
    }

    void insert(const string& word) {
        root->insert(word);
    }

    Aho_Corasick() : root(new TrieNode) {}

    ~Aho_Corasick() {
        delete root;
    }

    void cover(const string& word) {
        if (!is_initialized) {
            init();
            is_initialized = true;
        }

        auto current = root;
        for (int i = 0; i < word.size(); i++) {
            int index = word[i] - base;
            while (current != root && current->children[index] == nullptr)
                current = current->fail;
            if (current->children[index] != nullptr)
                current = current->children[index];

            if (current->isEndOf != -1) {
                ans[i - lenOfPattern[current->isEndOf] + 1] += 1;
                ans[i + 1] -= 1;
            }
        }
    }

    void clear() {
        delete root;
        root = new TrieNode;
        is_initialized = false;
        lenOfPattern.clear();
        sz = 0;
    }
};

template<int size, char base>
vector<int> Aho_Corasick<size, base>::lenOfPattern = vector<int>();
template<int size, char base>
int Aho_Corasick<size, base>::sz = 0;

int32_t main() {
    fastIO;
    int n, m;
    string text;
    cin >> n >> text >> m;
    vector<string> patterns(m);
    for (auto& e : patterns) cin >> e;
    sort(patterns.begin(), patterns.end(), [](const string_view a, const string_view b){ return a.size() < b.size(); });

    ans.resize(n + 1, 0);
    Aho_Corasick solver;

    for (int bucket = 0; bucket < m; bucket += 500) {
        for (int i = bucket; i < m && i < bucket + 500; i++)
            solver.insert(patterns[i]);
        solver.cover(text);
        solver.clear();
    }

    for (int i = 1; i <= n; i++) ans[i] += ans[i - 1];
    cout << n - count_if(all(ans), [](const auto a){ return a > 0; });

    return 0;
}