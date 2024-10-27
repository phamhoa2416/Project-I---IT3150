#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
private:
    vector<long int> parent, rank;
    
public:
    DSU(long int size) {
        parent.resize(size);
        rank.resize(size);
        
        for (long int i = 0; i < size; ++i) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
    
    long int find(long int i) {
        if (parent[i] == -1) 
            return i;
            
        return parent[i] = find(parent[i]);
    }
    
    void unite(long int u, long int v) {
        long int s1 = find(u);
        long int s2 = find(v);
        
        if (s1 != s2) {
            if (rank[s1] < rank[s2])
                parent[s1] = s2;
            else if (rank[s1] > rank[s2])
                parent[s2] = s1;
            else {
                parent[s2] = s1;
                rank[s1] ++;
            }
        }
    }
};

class Graph {
private:
    long int numVertices;
    vector<vector<long int>> adj;
public:
    Graph(long int numVertices) {
        this->numVertices = numVertices;
        adj = vector<vector<long int>>();
    }
    
    void add_edge(long int u, long int v, long int w) {
        adj.push_back({w, u - 1, v - 1});
    }
    
    long int kruskal_mst() {
        sort(adj.begin(), adj.end());
        
        DSU dsu(numVertices);
        
        long int result = 0;
        
        for (auto edge: adj) {
            long int w = edge[0];
            long int u = edge[1];
            long int v = edge[2];
            
            if (dsu.find(u) != dsu.find(v)) {
                dsu.unite(u, v);
                result += w;
            }
        }
        
        return result;
    }
};

int main() {
    long int n, m;
    cin >> n >> m;
    
    Graph g(n);
    
    for (long int i = 0; i < m; ++i) {
        long int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    
    cout << g.kruskal_mst();
    return 0;
}
