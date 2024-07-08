//
// Created by june0 on 2024-07-09.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
#define GRAPH_TYPE_DEFINED
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
#define MATRIX_TYPE_DEFINED
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
 * These classes use low-level i/o functions (@c fread()/mmap() for input, @c fwrite()/write() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char* p;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }
        INPUT() {
            struct stat st;
            fstat(0, &st);
            p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
        }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            return *p++;
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
            write(1, writeBuffer, write_idx);
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

const int MAX = 1 << 19; // ≃ 500'000

/// @see https://gina65.tistory.com/30
namespace FWHT {
    enum Conv_Type {OR, AND, XOR};

    template<Conv_Type type,
            std::enable_if_t<type == Conv_Type::OR>* = nullptr,
            typename T = int>
    void _fwht(vector<T> &_v, bool _is_inv) {
        int n = (int) _v.size();
        int sgn = _is_inv ? -1 : 1;
        for (int i = 1; i < n; i <<= 1)
            for (int j = 0; j < n; j += i << 1)
                for (int k = 0; k < i; k++)
                    _v[i + j + k] += sgn * _v[j + k];
    }

    template<Conv_Type type,
            std::enable_if_t<type == Conv_Type::AND>* = nullptr,
            typename T = int>
    void _fwht(vector<T> &_v, bool _is_inv) {
        int n = (int) _v.size();
        int sgn = _is_inv ? -1 : 1;
        for (int i = 1; i < n; i <<= 1)
            for (int j = 0; j < n; j += i << 1)
                for (int k = 0; k < i; k++)
                    _v[j + k] += sgn * _v[i + j + k];
    }

    template<Conv_Type type,
            std::enable_if_t<type == Conv_Type::XOR>* = nullptr,
            typename T = int>
    void _fwht(vector<T> &_v, bool _is_inv) {
        int n = (int) _v.size();
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += i << 1) {
                for (int k = 0; k < i; k++) {
                    T tmp = _v[i + j + k];
                    _v[i + j + k] = _v[j + k] - tmp;
                    _v[j + k] += tmp;

                    if (_is_inv) {
                        _v[i + j + k] >>= 1;
                        _v[j + k] >>= 1;
                    }
                }
            }
        }
    }

    template<Conv_Type type, typename Value_Type = int>
    class FWHT {
        using T = Value_Type;
    public:
        void fwht(std::vector<T> &a) {
            _fwht<type>(a, false);
        }
        void inv_fwht(std::vector<T> &a) {
            _fwht<type>(a, true);
        }

        static std::vector<T> _convolution(std::vector<T> &&_a, std::vector<T> &&_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
#if __has_builtin(__builtin_clz)
            int l = 32 - __builtin_clz(n + m), len = 1 << l;
#else
            int len = 1;
            while (len < n + m) len <<= 1;
#endif
            _a.resize(len);
            _fwht<type>(_a, false);
            _b.resize(len);
            _fwht<type>(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fwht<type>(_a, true);
            return _a;
        }

        static std::vector<T> _convolution_pow(std::vector<T> &&_a, int _exp) {
            int n = (int) _a.size();
#if __has_builtin(__builtin_clz)
            int l = 32 - __builtin_clz(n + n), len = 1 << l;
#else
            int len = 1;
            while (len < n + n) len <<= 1;
#endif
            _a.resize(len);
            _fwht<type>(_a, false);

            for (int i = 0; i < len; i++)
                _a[i] *= pow(_a[i], _exp - 1);

            _fwht<type>(_a, true);
            return _a;
        }

        static std::vector<T> convolution(const std::vector<T> &a,
                                          const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            std::vector<T> _a(a.begin(), a.end()), _b(b.begin(), b.end());
            return _convolution(std::move(_a), std::move(_b));
        }

        static std::vector<T> convolution_pow(const std::vector<T> &a, int exp) {
            int n = (int) a.size();
            if (n == 0) return {};

            std::vector<T> _a(a.begin(), a.end());
            return _convolution_pow(std::move(_a), exp);
        }
    };
}
using namespace FWHT;

int32_t main() {
    fastIO;
    int n, m; // <= 500'000
    cin >> n >> m;
    vector<ll> v(n);
    for (auto &e : v) {
        cin >> e; // <= 1e18
        e %= m + 1;
    }

    // Prob: count i < j < k s.t. v[i] ^ v[j] ^ v[k] == 0
    //  i.e) count j < k for all i s.t. v[i] == v[j] ^ v[k]
    vector<ll> a(m + 1, 0);
    for (const auto &e : v) a[e]++;

    auto conv = ::FWHT::FWHT<XOR, ll>::convolution_pow(a, 2);
    conv[0] -= n;
    for (auto &e : conv) e /= 2;

    ll ans = 0;
    for (const auto &i : v) {
        ll tmp = 1LL * (conv[i] - (a[0] - (i == 0)));
        ans += tmp;
    }

    cout << ans / 3;

    return 0;
}