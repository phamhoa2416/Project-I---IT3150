#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> Edge; 

class Graph
{
private:
    int numVertices;
    vector<vector<Edge>> graph;

public:
    Graph(int numVertices) : numVertices(numVertices)
    {
        graph.resize(numVertices);
    }

    void add_edge(int u, int v, int w)
    {
        graph[u - 1].push_back({v - 1, w});
    }

    int dijkstra(int start, int end)
    {
        vector<int> distance(numVertices, numeric_limits<int>::max()); // distance from start to each vertex
        vector<bool> visited(numVertices, false); // visited vertices
        
        distance[start - 1] = 0; // distance from start to start is 0

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap
        pq.push({0, start - 1}); // distance from start to start is 0

        while (!pq.empty()) // while there are vertices to visit
        {
            int u = pq.top().second; // choose the vertex with the smallest distance
            pq.pop(); // remove the vertex from the queue

            if (visited[u]) // if the vertex has been visited, skip it
                continue;
            visited[u] = true;

            for (const auto& edge : graph[u]) // for each neighbor of the vertex
            {
                int v = edge.first; // neighbor
                int weight = edge.second; // weight of the edge

                // If the neighbor has not been visited and the distance from start to the neighbor
                // is greater than the distance from start to the current vertex plus the weight of the edge
                if (!visited[v] && distance[u] != numeric_limits<int>::max() && distance[u] + weight < distance[v]) // 
                {
                    distance[v] = distance[u] + weight; // update the distance from start to the neighbor
                    pq.push({distance[v], v}); // add the neighbor to the queue for future iterations
                }
            }
        }

        int result = distance[end - 1]; // distance from start to end
        return result == numeric_limits<int>::max() ? -1 : result;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.add_edge(u, v, w);
    }

    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = graph.dijkstra(i + 1, j + 1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
