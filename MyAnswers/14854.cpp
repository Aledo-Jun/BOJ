//
// Created by june0 on 2024-07-04.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using namespace __gnu_cxx;
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

template<typename T>
constexpr T pow_mod(T a, __int128 pow, __int128 MOD) {
    __int128 base = a;
    __int128 res = 1;
    while (pow > 0) {
        if (pow & 1) {
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD;
        pow >>= 1;
    }
    return res;
}

constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// returns {x,y,g} s.t. ax + by = g = gcd(a,b) >=0.
constexpr std::array<long long,3> ext_gcd(long long a, long long b) {
    long long x = 1, y = 0;
    long long z = 0, w = 1;
    while (b) {
        long long p = a / b, q = a % b;
        x -= y * p, std::swap(x, y);
        z -= w * p, std::swap(z, w);
        a = b, b = q;
    }
    if (a < 0) {
        x = -x, z = -z, a = -a;
    }
    return {x, z, a};
}

// returns {x,g} s.t. a * x = g (mod m)
constexpr std::pair<long long, long long> inv_gcd(long long a, long long MOD) {
    auto [x, y, g] = ext_gcd(a, MOD);
    return {safe_mod(x, MOD), g};
}

int mod_inv(int a, int MOD) {
    auto [x, y, g] = ext_gcd(a, MOD);
    assert(g == 1);
    return safe_mod(x, MOD);
}

array<vector<int>,2> precompute_factorials(int MOD) {
    vector<int> fact(MOD), inv_fact(MOD);
    fact[0] = 1;
    for (int i = 1; i < MOD; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[MOD - 1] = mod_inv(fact[MOD - 1], MOD);
    for (int i = MOD - 2; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;

    return {fact, inv_fact};
}

array<vector<int>,2> precompute_factorials(int p, int q) {
    int MOD = (int) pow(p, q);
    vector<int> fact(MOD), inv_fact(MOD);
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < MOD; i++) {
        if (i % p) fact[i] = fact[i - 1] * i % MOD;
        else fact[i] = fact[i - 1];

        inv_fact[i] = mod_inv(fact[i], MOD);
    }

    return {fact, inv_fact};
}

int binomial_coefficient(int n, int k, int MOD, const vector<int>& fact, const vector<int>& inv_fact) {
    if (k > n) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int Lucas(int n, int k, int MOD, const vector<int>& fact, const vector<int>& inv_fact) {
    int res = 1;
    while (n && k) {
        int n_remain = n % MOD;
        int k_remain = k % MOD;
        if (k_remain > n_remain) return 0;
        res = 1LL * res * binomial_coefficient(n_remain, k_remain, MOD, fact, inv_fact) % MOD;
        n /= MOD;
        k /= MOD;
    }
    return res;
}
/**
 * Generalization of Lucas' Theorem for modulo prime powers p^q
 * (if q == 1, simply use Lucas instead)
 * @return binomial_coefficient(n, k) mod p^q
 * @see https://web.archive.org/web/20170202003812/http://www.dms.umontreal.ca/~andrew/PDF/BinCoeff.pdf Thm.1
 */
int Lucas_pow_of_prime(int n, int k, int p, int q, const vector<int>& fact, const vector<int>& inv_fact) {
    int MOD = (int) pow(p, q);
    int A = n, B = k, C = n - k;
    vector<int> ai, bi, ci;
    vector<int> Ai, Bi, Ci;
    while (A || B || C) {
        ai.emplace_back(A % p);
        bi.emplace_back(B % p);
        ci.emplace_back(C % p);

        Ai.emplace_back(A % MOD);
        Bi.emplace_back(B % MOD);
        Ci.emplace_back(C % MOD);

        A /= p;
        B /= p;
        C /= p;
    }

    vector<int> e_prefix;
    int carry = 0;
    for (int i = 0; i < ai.size(); i++) {
        int val = bi[i] + ci[i] + carry;
        if (val >= p) {
            carry = 1;
            e_prefix.emplace_back(1);
        } else {
            carry = 0;
            e_prefix.emplace_back(0);
        }
    }
    for (int i = 1; i < e_prefix.size(); i++) e_prefix[i] += e_prefix[i - 1];

    int e0 = e_prefix.back();
    int eq_1 = e0 - e_prefix[q - 2]; // e_(q-1)
    if (p == 2 && q >= 3) eq_1 = 0;

    int res = (int) pow(p, e0) * (eq_1 & 1 ? -1 : 1) % MOD;
    for (int i = 0; i < ai.size(); i++) {
        res = res * fact[Ai[i]] % MOD;
        res = res * inv_fact[Bi[i]] % MOD;
        res = res * inv_fact[Ci[i]] % MOD;
    }
    return (res + MOD) % MOD;
}

/**
 * Chinese Remainder Theorem(CRT) implementation
 * @param remainders a_i := remainders[i]
 * @param moduli     p_i := moduli[i]
 * @return the solution of the system of linear congruence
 *        { x = a_i mod p_i }
 */
int Chinese_remainder_theorem(const std::vector<int>& remainders, const std::vector<int>& moduli) {
    int N = 1;
    for (int mod : moduli) N *= mod;

    int res = 0;
    for (int i = 0; i < moduli.size(); i++) {
        int ai = remainders[i];
        int Ni = N / moduli[i];
        int Mi = mod_inv(Ni, moduli[i]);
        res = (res + 1LL * ai * Mi % N * Ni % N) % N;
    }

    return res;
}

vector<int> primes = {27, 11, 13, 37};
auto [fact27, inv_fact27] = precompute_factorials(3, 3);
auto [fact11, inv_fact11] = precompute_factorials(11);
auto [fact13, inv_fact13] = precompute_factorials(13);
auto [fact37, inv_fact37] = precompute_factorials(37);

int binomial_coefficient(int n, int k) {
    vector<int> remainders(4);
    remainders[0] = Lucas_pow_of_prime(n, k, 3, 3, fact27, inv_fact27);
    remainders[1] = Lucas(n, k, 11, fact11, inv_fact11);
    remainders[2] = Lucas(n, k, 13, fact13, inv_fact13);
    remainders[3] = Lucas(n, k, 37, fact37, inv_fact37);

    return Chinese_remainder_theorem(remainders, primes);
}

int32_t main() {
    fastIO;
    int tc;
    cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;
        cout << binomial_coefficient(n, k) << endl;
    }

    return 0;
}