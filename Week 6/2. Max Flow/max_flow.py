from collections import defaultdict

# This class represents a directed graph 
# using adjacency matrix representation
class Graph:
    def __init__(self, graph):
        self.graph = graph
        self.row = len(graph)
        
    def bfs(self, source, sink, parent):
        visited = [False] * self.row
        queue = []
        
        # Mark the source node as visited and enqueue it
        queue.append(source)
        visited[source] = True
        
        while queue:
            u = queue.pop(0)
            
            # Get all adjacent vertices of the dequeued vertex u
            # If a adjacent has not been visited, then mark it
            # visited and enqueue it
            for v, capacity in enumerate(self.graph[u]):
                if visited[v] == False and capacity > 0:
                    queue.append(v)
                    visited[v] = True
                    parent[v] = u
                    
                    if v == sink:
                        return True
                    
        return False
    
    def edmondsKarp(self, source, sink):
        source -= 1
        sink -= 1
        parent = [-1] * self.row
        max_flow = 0
        
        # Augment the flow while there is path from source to sink
        while self.bfs(source, sink, parent):
            path_flow = float("Inf")
            v = sink
            
            # Find minimum residual capacity of the edges along the
            # path filled by BFS
            while v != source:
                path_flow = min(path_flow, self.graph[parent[v]][v])
                v = parent[v]
                
            max_flow += path_flow
            
            # Update residual capacities of the edges and reverse edges
            # along the path
            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]
                
        return max_flow     
        
n, m = map(int, input().split())
source, sink = map(int, input().split())
graph = [[0] * n for _ in range(n)]
for _ in range(m):
    u, v, capacity = map(int, input().split())
    graph[u - 1][v - 1] = capacity
    
g = Graph(graph)
print(g.edmondsKarp(source, sink))