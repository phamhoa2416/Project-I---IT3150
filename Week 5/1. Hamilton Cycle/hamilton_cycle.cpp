#include <iostream>
#include <vector>

using namespace std;

bool is_safe(int v, const vector<vector<int>>& graph, const vector<int>& path, int pos) {
    // Check if this vertex is an adjacent vertex of the previously added vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;
        
    // Check if the vertex has already included in the path        
    for (int i = 0; i < pos; ++i) 
        if (path[i] == v) 
            return false;
            
    return true;
}

bool hamiltonian_util(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    if (pos == graph.size()) {
        // Check if there is an edge from the last vertex to the first vertex
        if (graph[path[pos - 1]][path[0]] == 1) 
            return true;
        else 
            return false;
    }
    
    for (int v = 1; v < graph.size(); ++v) {
        if (is_safe(v, graph, path, pos)) {
            path[pos] = v;
            
            if (hamiltonian_util(graph, path, pos + 1))
                return true;
                
            path[pos] = -1;
        }
    }
    
    return false;
}

bool is_hamilton(const vector<vector<int>>& graph) {
    vector<int> path(graph.size(), -1);
    path[0] = 0;
    
    if (hamiltonian_util(graph, path, 1))
        return true;
        
    return false;
}

int main() {
    int T;
    cin >> T;
    
    vector<int> results;
    
    for (int t = 0; t < T; ++t) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> graph(n, vector<int>(n, 0));
        
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
        }
        
        results.push_back(is_hamilton(graph));
    }
    
    for (int result : results) {
        cout << result << endl;
    }
    
    return 0;
}
