#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adj;
    vector<bool> visited;
public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adj.resize(numVertices);
        visited.resize(numVertices, false);
    }

    void add_edge(int u, int v) {
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
        
        sort(adj[u - 1].begin(), adj[u - 1].end());
        sort(adj[v - 1].begin(), adj[v - 1].end());
    }

    void bfs(int u) {
        queue<int> q;

        visited[u] = true;
        q.push(u);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current + 1 << " ";

            for (int v : adj[current]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }
    
    void bfs_extend() {
        visited.assign(numVertices, false);
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i])
                bfs(i);
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.bfs_extend();
    return 0;
}
