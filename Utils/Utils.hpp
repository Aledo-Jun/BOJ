#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

/*
 * Algorithm to find the LIS(Longest Increasing Subsequence)
 */
namespace LIS
{
    template<typename T, typename Iter, typename Container>
    Container _lis(const Iter &left, const Iter &right) {
        // from left to right - 1
        int n = std::distance(left, right);
        std::vector<int> idx(n);
        std::vector<T> lis;

        for (int i = 0; i < n; i++) {
            if (lis.size() == 0 || lis.back() < *(left + i)) {
                lis.emplace_back(*(left + i));
                idx[i] = lis.size() - 1;
            } else {
                auto it = std::lower_bound(lis.begin(), lis.end(), *(left + i));
                *it = *(left + i);
                idx[i] = std::distance(lis.begin(), it);
            }
        }

        std::vector<T> res;
        int j = lis.size() - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (idx[i] == j){
                j--;
                res.emplace_back(*(left + i));
            }
        }
        std::reverse(res.begin(), res.end());

        return Container(res);
    }

    template<typename Container>
    Container lis(const Container& v){
        return _lis<typename Container::value_type,
                    typename Container::const_iterator,
                    Container>(v.begin(), v.end());
    }
}// End namespace LIS

/**
 * @brief Removable Priority Queue
 */
template<typename T, typename Container = vector<T>, typename Comp = less<T>>
class PQ {
    priority_queue<T, Container, Comp> pq, removed;

public:
    void emplace(int x) { pq.emplace(x); }

    void erase(int x) { removed.emplace(x); }

    void refresh() {
        while (!removed.empty() && pq.top() == removed.top()) {
            pq.pop();
            removed.pop();
        }
    }

    int top() {
        refresh();
        return pq.top();
    }

    int size() {
        refresh();
        return pq.size();
    }

    bool empty() {
        refresh();
        return pq.empty();
    }
};