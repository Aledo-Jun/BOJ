//
// Created by june0 on 2024-01-30.
//

#ifndef BOJ_ORDEREDSET_HPP
#define BOJ_ORDEREDSET_HPP

#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace Utils
{
namespace OrderedSet
{
    using namespace std;
    using namespace __gnu_pbds;

    using ordered_set = __gnu_pbds::tree<
            int,
            __gnu_pbds::null_type,
            std::less<>,
            __gnu_pbds::rb_tree_tag,
            __gnu_pbds::tree_order_statistics_node_update>;

    using ordered_multiset = __gnu_pbds::tree<
            int,
            __gnu_pbds::null_type,
            std::less_equal<>,
            __gnu_pbds::rb_tree_tag,
            __gnu_pbds::tree_order_statistics_node_update>;

    void multiset_erase(ordered_multiset &OS, int val) {
        int index = (int) OS.order_of_key(val);
        auto it = OS.find_by_order(index);
        if (*it == val) OS.erase(it);
    }
}
}
#endif //BOJ_ORDEREDSET_HPP
