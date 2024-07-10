//
// Created by june0 on 2024-07-02.
//

#ifndef BOJ_GAMETHEORY_HPP
#define BOJ_GAMETHEORY_HPP

#include <cstring>
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

        class SpragueGrundy2D {
            int r, c;
            std::vector<std::vector<int>> grundyNumbers;

        public:
            explicit SpragueGrundy2D(int r, int c) : r(r), c(c), grundyNumbers(r + 1, std::vector<int>(c + 1, 0)) {
                calc_set();
            }

            void calc_set() {
                //ll mx = 0;
                for (int i = 1; i <= r; i++) {
                    int g = 0;
                    int cnt[4040];
                    std::memset(cnt, 0, sizeof(cnt));
                    for (int j = 1; j <= c; j++) {

                        for (int k = 1; k < i; k++) cnt[grundyNumbers[i-k][j]]++;
                        for (int k = 1; k < std::min(i, j); k++) cnt[grundyNumbers[i-k][j-k]]++;

                        g = std::max(0, g - 100);
                        while (cnt[g]) g++;
                        grundyNumbers[i][j] = g;
                        cnt[g] = 1;

                        for (int k = 1; k < i; k++) cnt[grundyNumbers[i-k][j]]--;
                        for (int k = 1; k < std::min(i, j); k++) cnt[grundyNumbers[i-k][j-k]]--;
                    }
                }
                //cout << mx << endl << endl; // => 4012
            }

            int get(int i, int j) {

            }
        };


    }
}
#endif //BOJ_GAMETHEORY_HPP
