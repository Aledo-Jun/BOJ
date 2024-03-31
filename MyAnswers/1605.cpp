//
// Created by june0 on 2024-03-31.
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

template<typename String = std::string>
class SA_IS {
    using T = typename String::value_type;
private:
    int sz;
    std::vector<int> str; // compressed string
    int bucket_sz; // bucket size after compression (== # of distinct characters in the string)

    std::vector<int> sfx, rev, lcp;
    std::vector<int> ptr; // for counting sort

    bool sfx_initialized = false, lcp_initialized = false;

    void build_sfx(const std::vector<int>& s, int bucket, std::vector<int>& sa) {
        int n = static_cast<int>(s.size());
        if (n == 1) {
            sa[0] = 0;
            return;
        }

        std::vector<bool> is_S_type(n, false);
        std::vector<int> cnt(bucket + 1, 0); // for counting sort

        // 1. Check the type of each character and the number of LMS.
        int lms_cnt = 0;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] < s[i + 1]) is_S_type[i] = true;
            else if (s[i] == s[i + 1]) is_S_type[i] = is_S_type[i + 1];
            else lms_cnt += is_S_type[i + 1];
        }

        std::fill(sa.begin(), sa.end(), -1);
        for (int i = 0; i < n; i++) cnt[s[i] + 1]++;
        for (int i = 1; i <= bucket; i++) cnt[i] += cnt[i - 1];

        // 2. Sort LMS's using counting sort.
        if (lms_cnt) {
            std::vector<int> lms_pos(lms_cnt + 1), sub(lms_cnt, 0);
            std::vector<int> sub_sa(lms_cnt, 0); // Guessed SA only using LMS's

            // 2-1. Specify the position of LMS's
            ptr.assign(std::next(cnt.begin()), cnt.end());
            for (int i = 1, j = 0; i < n; i++) {
                if (is_S_type[i] && !is_S_type[i - 1]) {
                    rev[i] = j; // there is j-th lms at i
                    lms_pos[j++] = i;
                    sa[--ptr[s[i]]] = i;
                }
            }
            lms_pos[lms_cnt] = n;

            // 2-2. Induced sorting.
            ptr.assign(cnt.begin(), std::prev(cnt.end()));
            sa[ptr[s[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) { // sort L-type (left->right)
                int j = sa[i] - 1;
                if (j >= 0 && !is_S_type[j])
                    sa[ptr[s[j]]++] = j;
            }
            ptr.assign(std::next(cnt.begin()), cnt.end());
            for (int i = n - 1; i >= 0; i--) { // sort S-type (right->left)
                int j = sa[i] - 1;
                if (j >= 0 && is_S_type[j])
                    sa[--ptr[s[j]]] = j;
            }

            for (int i = 0, j = 0; i < n; i++) {
                if (sa[i] > 0 && is_S_type[sa[i]] && !is_S_type[sa[i] - 1]) {
                    sub_sa[j++] = rev[sa[i]];
                }
            }

            // 2-3. For each consecutive LMS's in sub_sa,
            for (int i = 1; i < lms_cnt; i++) {
                int q1 = sub_sa[i - 1], q2 = sub_sa[i];
                int j1 = lms_pos[q1], j2 = lms_pos[q2];
                int n1 = lms_pos[q1 + 1] - j1;
                int n2 = lms_pos[q2 + 1] - j2;
                sub[q2] = sub[q1];
                // Check whether they are equal or not.
                // If not, give the second one another name.
                if (n1 != n2) sub[q2]++;
                else {
                    for (int j = 0; j < n1; j++) {
                        if (s[j1 + j] < s[j2 + j] || is_S_type[j1 + j] < is_S_type[j2 + j]) {
                            sub[q2]++;
                            break;
                        }
                    }
                }
            }

            // 2-4. At this point, sub_sa is sorted.
            // But the actual SA might not be sorted properly(might exist duplicates).
            int sub_bucket = sub[sub_sa[lms_cnt - 1]] + 1;
            if (sub_bucket < lms_cnt)               // if not properly sorted,
                build_sfx(sub, sub_bucket, sub_sa); // recurse

            // 2-5. Merge sorted sub_sa to sa.
            std::fill(sa.begin(), sa.end(), -1);
            ptr.assign(std::next(cnt.begin()), cnt.end());
            for (int i = lms_cnt - 1; i >= 0; i--) {
                int j = lms_pos[sub_sa[i]];
                sa[--ptr[s[j]]] = j;
            }
        }

        // 3. Finally, clean up the rest of the characters.
        ptr.assign(cnt.begin(), std::prev(cnt.end()));
        sa[ptr[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int j = sa[i] - 1;
            if (j >= 0 && !is_S_type[j])
                sa[ptr[s[j]]++] = j;
        }
        ptr.assign(std::next(cnt.begin()), cnt.end());
        for (int i = n - 1; i >= 0; i--) {
            int j = sa[i] - 1;
            if (j >= 0 && is_S_type[j])
                sa[--ptr[s[j]]] = j;
        }
    }

    void build_lcp() {
        assert(sfx_initialized);
        for (int i = 0; i < sz; i++) rev[sfx[i]] = i;
        str.emplace_back(-1);
        for (int i = 0, h = 0; i < sz; i++) {
            if (rev[i]) {
                int prev = sfx[rev[i] - 1];
                while (str[prev + h] == str[i + h]) h++;
                lcp[rev[i]] = h;
            }
            h = std::max(h - 1, 0);
        }
        str.pop_back();
    }

public:
    /* implicit */ SA_IS(const String& s) // NOLINT
            : sz(static_cast<int>(s.size())), str(sz), rev(sz), sfx(sz)
    {
        const auto mn = std::numeric_limits<T>::min();
        const auto mx = std::numeric_limits<T>::max();
        std::vector<int> compressor(mx - mn + 1);
        for (int i = 0; i < sz; i++) compressor[s[i] - mn] = 1;
        for (int i = 1; i < static_cast<int>(compressor.size()); i++) compressor[i] += compressor[i - 1];
        for (int i = 0; i < sz; i++) str[i] = compressor[s[i] - mn] - 1;
        bucket_sz = compressor.back();

        build_sfx(str, bucket_sz, sfx);
        sfx_initialized = true;
    }

    int operator[](int i) const { return sfx[i]; }
    std::vector<int> get_sfx() { return sfx; }
    std::vector<int> get_lcp() {
        if (lcp_initialized) return lcp;

        lcp.resize(sz, 0);
        build_lcp();
        lcp_initialized = true;
        return lcp;
    }
};

int32_t main() {
    fastIO;
    int n;
    string s;
    cin >> n >> s;

    SA_IS sais(s);
    auto sfx = sais.get_sfx();
    auto lcp = sais.get_lcp();

    cout << *max_element(all(lcp));

    return 0;
}