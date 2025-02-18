//
// Created by june0 on 2025-02-18.
//

#ifndef BOJ_BARRET_H
#define BOJ_BARRET_H

namespace Math {
    /// Structure for fast modular multiplication
    struct Barrett {
        unsigned MOD;
        unsigned long long inv_MOD;

        explicit Barrett(unsigned m) : MOD(m), inv_MOD((unsigned long long) (-1) / MOD + 1) {}

        [[nodiscard]]
        unsigned mod() const { return MOD; }

        [[nodiscard]]
        unsigned multiply(unsigned a, unsigned b) const {
            unsigned long long res1 = a;
            res1 *= b;
            unsigned long long res2 = ((unsigned __int128) (res1) * inv_MOD) >> 64;
            res2 *= MOD;
            return (res1 - res2 + (res1 < res2 ? MOD : 0));
        }
    }; // struct Barrett
}

#endif //BOJ_BARRET_H
