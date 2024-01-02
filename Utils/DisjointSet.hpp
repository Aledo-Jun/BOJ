#include <vector>

using namespace std;

class disjointSet {
    const int def_sz = 1001;
    vector<int> parent;
    vector<int> rank;
public:
    disjointSet(){
        parent.assign(def_sz, 0);
        rank.assign(def_sz, 0);
    }
    disjointSet(int sz){
        parent.assign(sz, 0);
        for (int i = 0; i < sz; i++)
            parent[i] = i;
        rank.assign(sz, 0);
    }

    // find the root of x
    int find(int x){
        if (x != parent[x]){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void uni(int x, int y){
        int rootx = find(x);
        int rooty = find(y);

        if (rootx != rooty){
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
};
