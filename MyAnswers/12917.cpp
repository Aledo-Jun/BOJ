//
// Created by june0 on 2024-04-07.
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


#ifdef NLINE_JUDGE // DO NOT USE THIS (IDK why this doesn't work, maybe output problem)
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

        static bool IsBlank(char c) { return c == ' ' || c == '\total'; }

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
            for (; curr != '\total' && !IsEnd(curr); curr = _ReadChar())
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
            if (write_idx + sz >= SZ) Flush();
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
#else
#define LOCAL_

template<typename T, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<T,S>& e) {
    out << e.first << ' ' << e.second << endl;
    return out;
}
template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& v) {
    for (const auto& e : v) out << e << '\n';
    return out;
}

#endif // LOCAL_

/**
   * @brief Suffix Automaton
   * @tparam IndexSize Size of the char set used for the string
   * @tparam MAX_N the maximum length of the string
   * @Reference <a href="https://github.com/koosaga/olympiad/blob/master/Library/codes/string/suffix_automaton.cpp">koosaga</a>
   */
template<int IndexSize = 26, int MAX_N = 1'000'000>
class SuffixAutomaton {
    struct node {
        int children[IndexSize];
        int suffix;
        int len;

        node() : suffix(0), len(0) {
            std::fill_n(children, IndexSize, -1);
        }
        node(int len, int suffix) : suffix(suffix), len(len) {
            std::fill_n(children, IndexSize, -1);
        }
    };

public:
    std::vector<node> automaton;
    int total;
    std::vector<int> cnt;

    int buk[MAX_N + 5], aux[MAX_N * 2 + 5];

    void append(int c) {
        assert(0 <= c && c <= IndexSize);
        auto curr = total;
        automaton.emplace_back(node(automaton[curr].len + 1, 0));
        total = automaton.size() - 1;
        cnt[total] = 1;
        while (curr != -1 && automaton[curr].children[c] == -1) {
            automaton[curr].children[c] = total;
            curr = automaton[curr].suffix;
        }
        if (curr != -1) {
            auto prv = automaton[curr].children[c];
            auto upd = automaton[curr].children[c];
            if (automaton[curr].len + 1 < automaton[prv].len) {
                upd = (int)automaton.size();
                auto new_node = automaton[prv];
                new_node.len = automaton[curr].len + 1;
                automaton.emplace_back(new_node);
                automaton[prv].suffix = upd;
                while (curr != -1 && automaton[curr].children[c] == prv){
                    automaton[curr].children[c] = upd;
                    curr = automaton[curr].suffix;
                }
            }
            automaton[total].suffix = upd;
        }
    }

    SuffixAutomaton(const string& str) : total(0) {
        automaton.reserve(MAX_N * 2);
        automaton.emplace_back(node(0, -1));
        cnt.resize(MAX_N * 2);

        for (const auto& c : str) this->append(c - 'a');
        for (int i = 1; i <= total; i++) ++buk[automaton[i].len];
        for (int i = 1; i <= MAX_N; i++) buk[i] += buk[i - 1];
        for (int i = total; i >= 1; i--) aux[buk[automaton[i].len]--] = i;
        for (int i = total; i >= 1; i--) cnt[automaton[aux[i]].suffix] += cnt[aux[i]];
    }

    [[nodiscard]] std::size_t size() const { return automaton.size(); }
    node& operator[](int i) { return automaton[i]; }
}; // class SuffixAutomaton

int32_t main() {
    fastIO;
    string str;
    cin >> str;
    int n = (int) str.size();

    SuffixAutomaton<26, 100'000> sam(str);

    ll ans = n;
    for (int i = 1; i < sam.size(); i++) {
        ans = max(ans, 1LL * sam[i].len * sam.cnt[i]);
    }
    cout << ans;

    return 0;
}

#ifdef ANOTHER_SOLUTION
// Use Suffix Array instead
using namespace SAIS_LITE;

int32_t main() {
    fastIO;
    string str;
    cin >> str;
    int n = (int)str.size();

    vector<int> sfx(n), lcp(n);
    saislcpxx(str.begin(), sfx.begin(), lcp.begin(), n);

    ll ans = 0;
    std::stack<int> st;
    st.emplace(-1);
    for (int i = 1; i < n; i++) {
        while (st.top() > 0 && lcp[st.top()] > lcp[i]) {
            int h = lcp[st.top()];
            st.pop();
            int w = i - st.top();
            ans = max(ans, 1LL * h * w);
        }
        st.emplace(i);
    }
    while (st.top() > 0) {
        int h = lcp[st.top()];
        st.pop();
        int w = n - st.top();
        ans = max(ans, 1LL * h * w);
    }

    ans = max(ans, ll(n));
    cout << ans;

    return 0;
}

#endif