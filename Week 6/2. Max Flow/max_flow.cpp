#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph
{
private:
    int numVertices;
    vector<vector<int>> graph;

public:
    Graph(int numVertices) : numVertices(numVertices)
    {
        graph.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int u, int v, int w)
    {
        graph[u - 1][v - 1] = w;
    }

    bool bfs(vector<vector<int>> &residualGraph, int source, int sink, vector<int> &parent)
    {
        vector<bool> visited(numVertices, false); // visited vertices
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < numVertices; ++v)
            {
                if (!visited[v] && residualGraph[u][v] > 0)
                {
                    if (v == sink)
                    {
                        parent[v] = u;
                        return true;
                    }

                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return false;
    }

    int edmondsKarp(int source, int sink)
    {
        source--;
        sink--;
        // Create a residual graph and fill the residual graph
        // with given capacities in the original graph as
        // residual capacities in residual graph
        vector<vector<int>> residualGraph = graph; // residual graph
        vector<int> parent(numVertices);           // parent of each vertex

        int maxFlow = 0; // max flow

        // Augment flow while there is a path from source to sink
        while (bfs(residualGraph, source, sink, parent))
        {
            int pathFlow = INT_MAX; // flow through the path
            // Find minimum residual capacity of the edges along
            // the path filled by BFS, or find the maximum flow through the path found.
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                pathFlow = min(pathFlow, residualGraph[u][v]);
            }

            // Update residual capacities of the edges
            // and reverse edges along the path
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                residualGraph[u][v] -= pathFlow; // use the pathFlow units of its capacity in the residual graph
                residualGraph[v][u] += pathFlow; // add the pathFlow units of capacity to the reverse edge
            }

            // Add path flow to overall flow
            maxFlow += pathFlow;
        }

        return maxFlow;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    int source, sink;
    cin >> source >> sink;

    Graph graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int maxFlow = graph.edmondsKarp(source, sink);
    cout << maxFlow << endl;
    return 0;
}