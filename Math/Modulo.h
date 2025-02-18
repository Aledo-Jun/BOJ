//
// Created by june0 on 2025-02-18.
//

#ifndef BOJ_MODULO_H
#define BOJ_MODULO_H

#include <array>

namespace Math {
    constexpr long long safe_mod(long long x, long long m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }

    constexpr unsigned pow_mod_constexpr(long long a, long long n, unsigned MOD) {
        if (MOD == 1) return 0;
        a = safe_mod(a, MOD);
        unsigned long long res = 1;
        while (n) {
            if (n & 1) res = (res * a) % MOD;
            n >>= 1;
            a = (a * a) % MOD;
        }
        return res;
    }

    // NOTE : m must be prime
    constexpr unsigned primitive_root_constexpr(unsigned m) {
        // some popular roots
        if (m == 2) return 1;
        if (m == 167'772'161) return 3;
        if (m == 469'762'049) return 3;
        if (m == 754'974'721) return 11;
        if (m == 998'244'353) return 3;

        // find divisors of m - 1
        unsigned divs[20] = {};
        divs[0] = 2;
        unsigned cnt = 1;
        unsigned x = (m - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (int i = 3; (long long) (i) * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        if (x > 1) {
            divs[cnt++] = x;
        }
        // find the first g s.t. there exist some d in divs, g^(m - 1)/d == 1 mod m
        for (int g = 2;; g++) {
            bool ok = true;
            for (int i = 0; i < cnt; i++) {
                if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

    template<unsigned m> constexpr unsigned primitive_root = primitive_root_constexpr(m);

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
}

#endif //BOJ_MODULO_H
