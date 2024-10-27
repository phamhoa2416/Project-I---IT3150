#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    int numVertices;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adj.resize(numVertices);
        visited.resize(numVertices, false);
    }

    void add_edge(int u, int v)
    {
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    void dfs(int u)
    {
        visited[u] = true;
        cout << u + 1 << " ";

        for (int v : adj[u])
            if (!visited[v])
                dfs(v);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    g.dfs(0);
}
