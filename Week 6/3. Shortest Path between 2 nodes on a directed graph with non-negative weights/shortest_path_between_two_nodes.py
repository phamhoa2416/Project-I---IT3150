class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]
        
    def add_edge(self, u, v, w):
        self.graph[u - 1][v - 1] = w
        
    def shortest_path(self, start, end):
        distance = [float('inf') for _ in range(self.vertices)]
        visited = [False for _ in range(self.vertices)]
        
        distance[start - 1] = 0
        
        for _ in range(self.vertices):
            u = self.min_distance(distance, visited)
            visited[u] = True
            
            for v in range(self.vertices):
                if self.graph[u][v] > 0 and not visited[v] and distance[v] > distance[u] + self.graph[u][v]:
                    distance[v] = distance[u] + self.graph[u][v]
                    
        return distance[end - 1]
    
    def min_distance(self, distance, visited):
        min_distance = float('inf')
        min_index = -1
        
        for v in range(self.vertices):
            if not visited[v] and distance[v] < min_distance:
                min_distance = distance[v]
                min_index = v
                
        return min_index
    
n, m = map(int, input().split())
graph = Graph(n)

for _ in range(m):
    u, v, w = map(int, input().split())
    graph.add_edge(u, v, w)

start, end = map(int, input().split())
print(graph.shortest_path(start, end))        