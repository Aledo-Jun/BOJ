#include <vector>
#include <numeric>

using namespace std;
namespace Utils
{
namespace DisjointSet
{
    template<bool Union_By_Rank = true>
    class DisjointSet {
    private:
        const int def_sz = 1001;
        vector<int> parent;
        vector<int> rank;
    public:
        DisjointSet() {
            parent.assign(def_sz, 0);
            std::iota(parent.begin(), parent.end(), 0);
            if constexpr (Union_By_Rank) rank.assign(def_sz, 0);
        }

        DisjointSet(int sz) {
            parent.assign(sz, 0);
            std::iota(parent.begin(), parent.end(), 0);
            if constexpr (Union_By_Rank) rank.assign(sz, 0);
        }

        // find the root of x
        int find(int x) {
            if (x != parent[x]) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        // Union By Rank,
        // i.e. the parent relation could be relational(not specified).
        template<std::enable_if_t<Union_By_Rank>* = nullptr>
        void uni(int x, int y) {
            int rootx = find(x);
            int rooty = find(y);
            if constexpr (Union_By_Rank) {
                if (rootx != rooty) {
                    if (rank[rootx] < rank[rooty])
                        parent[rootx] = rooty;
                    else if (rank[rootx] > rank[rooty])
                        parent[rooty] = rootx;
                    else {
                        parent[rooty] = rootx;
                        rank[rootx]++;
                    }
                }
            } else {
                if (rootx != rooty)
                    parent[rooty] = rootx;
            }
        }
    }; // class DisjointSet

    class WeightedDisjointSet {
    private:
        const int def_sz = 1001;
        vector<pair<int,int>> parent;
        vector<int> rank;
    public:
        WeightedDisjointSet() {
            parent.assign(def_sz, {0,0});
            rank.assign(def_sz, 0);
        }

        explicit WeightedDisjointSet(int sz) {
            parent.assign(sz, {0,0});
            for (int i = 0; i < sz; i++)
                parent[i] = {i, 0};
            rank.assign(sz, 0);
        }

        // find the root of x
        pair<int,int> find(int x, int w) {
            if (x != parent[x].first) {
                auto [p, pw] = find(parent[x].first, parent[x].second + w);
                parent[x] = {p, pw - w};
            }
            return {parent[x].first, parent[x].second + w};
        }

        // Union By Rank,
        // i.e. the parent relation could be relational(not specified).
        void uni(int x, int y, int w) {
            auto [rootx, wx] = find(x, 0);
            auto [rooty, wy] = find(y, 0);

            if (rootx != rooty) {
                if (rank[rootx] < rank[rooty]) {
                    parent[rootx] = {rooty, wy - wx - w};
                }
                else if (rank[rootx] > rank[rooty])
                    parent[rooty] = {rootx, wx - wy + w};
                else {
                    parent[rooty] = {rootx, wx - wy + w};
                    rank[rootx]++;
                }
            }
        }
    }; // class WeightedDisjointSet

} // namespace DisjointSet
} // namespace Utils