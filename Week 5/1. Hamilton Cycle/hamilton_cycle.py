def is_safe(v, graph, path, pos):
    if graph[path[pos - 1]][v] == 0:
        return False
        
    if v in path:
        return False
    return True
    
def hamilton_util(graph, path, pos):
    if pos == len(graph):
        return graph[path[pos - 1]][path[0]] == 1 
        
    for v in range(1, len(graph)):
        if is_safe(v, graph, path, pos):
            path[pos] = v
            
            if hamilton_util(graph, path, pos + 1):
                return True
                
            path[pos] = -1
            
    return False
        
def is_hamilton(graph):
    path = [0] * len(graph)
    path[0] = 0
    
    if not hamilton_util(graph, path, 1):
        return 0
        
    return 1 
    
if __name__ == "__main__":
    T = int(input())
    results = []
    
    for _ in range(T):
        n, m = map(int, input().split())
        graph = [[0 for _ in range(n)] for _ in range(n)]
        
        for _ in range(m):
            u, v = map(int, input().split())
            graph[u-1][v-1] = 1
            graph[v-1][u-1] = 1  

        results.append(is_hamilton(graph))
        
    for result in results:
        print(result)
        
