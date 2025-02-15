//
// Created by june0 on 2025-02-15.
//

#ifndef BOJ_SEGTREEBEATS_H
#define BOJ_SEGTREEBEATS_H

#include <vector>
#include <cmath>
using namespace std;

/**
 * @brief A highly flexible Segment Tree Beats data structure.
 *
 * This template implements a general "Segment Tree Beats" structure which can be customized
 * to support various range queries and updates. Unlike a standard lazy segment tree, this
 * version supports more advanced update strategies (commonly known as "beats") by providing
 * two predicate functions (TAG and BREAK) that determine when an update can be applied directly
 * to a node and when further propagation (or “beating” the node) is required.
 *
 * For examples, @see https://github.com/Aledo-Jun/BOJ/blob/main/MyAnswers/17476.cpp
 *               @see https://github.com/Aledo-Jun/BOJ/blob/main/MyAnswers/17474.cpp
 *
 * The behavior of the segment tree is fully determined by the following function objects:
 *
 * - **MergeNode**: Function used to merge two child nodes into a parent node.
 * - **MergeLazy**: Function used to merge a lazy value into an existing lazy value at a node,
 *   using the node’s information as context.
 * - **UpdateLazy**: Function used to update (or combine) an existing lazy value with a new lazy
 *   value, again given the node’s current information.
 * - **ApplyLazy**: Function that applies a lazy value to a node given the node’s current value,
 *   the lazy value, and the length (number of elements) the node covers.
 * - **TAG (tag_condition)**: Predicate function that checks whether the current node meets a
 *   condition such that the lazy update can be applied directly (i.e. “tagged”) without going
 *   deeper into its children.
 * - **BREAK (break_condition)**: Predicate function that checks whether the node meets a condition
 *   that should cause the update to be skipped (or “broken off”) because it is not applicable.
 *
 * @tparam NodeType   The type used for the data stored in the segment tree nodes.
 * @tparam LazyType   The type used for lazy update values.
 * @tparam MergeNode  Function type for merging two nodes.
 *                    Signature: NodeType(NodeType, NodeType)
 * @tparam MergeLazy  Function type for merging two lazy values with node context.
 *                    Signature: LazyType(LazyType, LazyType, NodeType)
 * @tparam UpdateLazy Function type for updating a lazy value with a new lazy value given node context.
 *                    Signature: LazyType(LazyType, LazyType, NodeType)
 * @tparam ApplyLazy  Function type for applying a lazy update to a node.
 *                    Signature: NodeType(NodeType, LazyType, int)
 *                    The int parameter represents the length (or size) of the segment the node covers.
 * @tparam TAG        Predicate function type used to determine if the node can be updated directly.
 *                    The narrower, the better performance
 *                    Signature: bool(NodeType, LazyType)
 * @tparam BREAK      Predicate function type used to decide if the update should be skipped for the node.
 *                    The broader, the better performance
 *                    Signature: bool(NodeType, LazyType)
 */
template<typename NodeType, typename LazyType,
        typename MergeNode = NodeType(NodeType,NodeType),
        typename MergeLazy = LazyType(LazyType,LazyType,NodeType),
        typename UpdateLazy = LazyType(LazyType,LazyType,NodeType),
        typename ApplyLazy = NodeType(NodeType,LazyType,int),
        typename TAG = bool(NodeType,LazyType),
        typename BREAK = bool(NodeType,LazyType)>
class SegTreeBeats {
private:
    MergeNode mergeNode;
    MergeLazy mergeLazy;
    UpdateLazy updateLazy;
    ApplyLazy applyLazy;
    TAG tag_condition;
    BREAK break_condition;

    vector<NodeType> tree;
    vector<LazyType> lazy;

    int size{}, height{}, n{};
    NodeType default_node;
    LazyType default_lazy;

    void init() {
        for (int i = n - 1; i >= 1; i--) pull(i);
    }

    void pull(int node) {
        tree[node] = mergeNode(tree[node << 1], tree[node << 1 | 1]);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != default_lazy) {
            tree[node] = applyLazy(tree[node], lazy[node], end - start + 1);
            if (start != end) {
                lazy[node << 1] = mergeLazy(lazy[node << 1], lazy[node], tree[node]);
                lazy[node << 1 | 1] = mergeLazy(lazy[node << 1 | 1], lazy[node], tree[node]);
            }
            lazy[node] = default_lazy;
        }
    }

    void _update(int node, int start, int end, int l, int r, LazyType value) {
        push(node, start, end);

        if (r < start || end < l || break_condition(tree[node], value)) return;

        if (l <= start && end <= r) {
            if (tag_condition(tree[node], value)) {
                lazy[node] = updateLazy(lazy[node], value, tree[node]);
                push(node, start, end);
                return;
            }
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, l, r, value);
        _update(node << 1 | 1, mid + 1, end, l, r, value);
        pull(node);
    }

    NodeType _query(int node, int start, int end, int left, int right) {
        push(node, start, end);

        if (end < left || right < start) return default_node;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return mergeNode(left_result, right_result);
    }

public:
    SegTreeBeats() = default;

    explicit
    SegTreeBeats(int sz, NodeType default_node = {}, LazyType default_lazy = {})
            : default_node(std::move(default_node)), default_lazy(std::move(default_lazy)) {
        height = (int) ceil(log2(sz));
        size = (1 << (height + 1));
        n = size >> 1;
        tree.resize(size + 1, this->default_node);
        lazy.resize(size + 1, this->default_lazy);
    }

    explicit
    SegTreeBeats(const vector<NodeType> &v, NodeType default_node = {}, LazyType default_lazy = {})
            : default_node(std::move(default_node)),
              default_lazy(std::move(default_lazy)) {
        height = (int) ceil(log2(v.size()));
        size = (1 << (height + 1));
        n = size >> 1;
        tree.resize(size + 1, this->default_node);
        lazy.resize(size + 1, this->default_lazy);
        std::copy(v.begin(), v.end(), tree.begin() + n);
        init();
    }

    void update(int l, int r, LazyType value) {
        if (l > r) return;
        _update(1, 0, n - 1, l, r, value);
    }

    NodeType query(int l, int r) {
        if (l > r) return default_node;
        return _query(1, 0, n - 1, l, r);
    }
};

#endif //BOJ_SEGTREEBEATS_H
