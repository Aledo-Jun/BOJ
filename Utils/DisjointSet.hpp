#include <vector>

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
        template<std::enable_if_t<Union_By_Rank>* = nullptr>
        DisjointSet() {
            parent.assign(def_sz, 0);
            rank.assign(def_sz, 0);
        }

        DisjointSet() {
            parent.assign(def_sz, 0);
        }

        template<std::enable_if_t<Union_By_Rank>* = nullptr>
        DisjointSet(int sz) {
            parent.assign(sz, 0);
            for (int i = 0; i < sz; i++)
                parent[i] = i;
            rank.assign(sz, 0);
        }

        DisjointSet(int sz) {
            parent.assign(sz, 0);
            for (int i = 0; i < sz; i++)
                parent[i] = i;
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
        }

        // Dangle y to the root of x
        void uni(int x, int y) {
            int rootx = find(x);
            int rooty = find(y);

            if (rootx != rooty)
                parent[rooty] = rootx;
        }
    }; // class DisjointSet
} // namespace DisjointSet
} // namespace Utils