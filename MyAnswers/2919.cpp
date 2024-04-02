//
// Created by june0 on 2024-04-02.
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

matrix<int> v;
vector<int> len;
vector<int> ptr; // points the top of each deck

int rank_[1 << 10][1 << 10][10]; // [idx of deck][pos of card][bit]

struct cmp { // compare two decks with index of a and b
    bool operator()(const int a, const int b) const { // return value is reversed
        int pos_a = ptr[a];
        int pos_b = ptr[b];
        for (int bit = 9; bit >= 0; bit--) {
            if (pos_a + (1 << bit) > len[a] || pos_b + (1 << bit) > len[b]) continue;

            // compare the prefixes of the decks
            if (rank_[a][pos_a][bit] == rank_[b][pos_b][bit]) {
                // 처음엔 가장 긴 prefix를 비교, 같다면 그 길이의 절반 만큼 연장해서 비교
                pos_a += (1 << bit);
                pos_b += (1 << bit);
            } else return rank_[a][pos_a][bit] < rank_[b][pos_b][bit];
        }
        // at this point, one of the decks is prefix of the other.
        // then choose the longer one.
        if (len[a] - pos_a != len[b] - pos_b) return len[a] - pos_a > len[b] - pos_b;
        return a < b;
    }
};

struct card {
    int idx, pos;
    ll rank;

    card(int i, int j, ll r) : idx(i), pos(j), rank(r) {}

    bool operator<(const card& other) const {
        return rank < other.rank;
    }
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    v.resize(n);
    len.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> len[i];
        v[i].resize(len[i]);
        for (auto& e : v[i]) cin >> e;
    }

    // iterate over all substrings with length of 1, 2, 4, 8, ... etc.
    for (int bit = 0; bit < 10; bit++) {
        int l = 1 << bit;
        int half = l >> 1;
        vector<card> deck;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j + l <= len[i]; j++) {
                ll r = 0;
                if (bit == 0) r = v[i][j];
                else r = rank_[i][j][bit - 1] * 100'000'100LL + rank_[i][j + half][bit - 1];

                deck.emplace_back(i, j, r);
            }
        }

        // rank compression
        ll prev_rank = -1;
        int rr = -1;
        sort(deck.begin(), deck.end());

        for (const auto& [idx, pos, r]: deck) {
            if (prev_rank != r) {
                prev_rank = r;
                rr++;
            }
            rank_[idx][pos][bit] = rr;
        }
    }

    ptr.resize(n, 0);
    set<int, cmp> pq;
    for (int i = 0; i < n; i++) pq.emplace(i);

    while (!pq.empty()) {
        int idx = *pq.begin();
        pq.erase(pq.begin());
        cout << v[idx][ptr[idx]++] << ' ';
        if (ptr[idx] < len[idx]) pq.emplace(idx);
    }

    return 0;
}