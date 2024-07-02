//
// Created by june0 on 2024-07-02.
//

#ifndef BOJ_GAMETHEORY_HPP
#define BOJ_GAMETHEORY_HPP

#include <vector>
#include <set>

namespace Utils
{
    namespace GameTheory
    {

        class SpragueGrundy {
            int n;
            std::vector<int> grundyNumbers;

        public:
            explicit SpragueGrundy(int size) : n(size), grundyNumbers(size + 1, 0) {}

            void calc_set() {
                for (int i = 1; i <= n; i++) {
                    std::set<int> s;

                    while (s.count(grundyNumbers[i])) grundyNumbers[i]++;
                }
            }

            int operator[](int i) { return grundyNumbers[i]; }

        };

    }
}
#endif //BOJ_GAMETHEORY_HPP
