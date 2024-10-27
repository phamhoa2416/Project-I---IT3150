from collections import deque

def add_edge(adj, u, v):
    adj[u - 1].append(v - 1)
    adj[v - 1].append(u - 1)
    
    adj[u - 1].sort()
    adj[v - 1].sort()
    
def bfs(adj, visited, u):
    queue = deque()
    
    visited[u] = True;
    queue.append(u)
    
    while queue:
        current = queue.popleft()
        print(current + 1, end = " ")
        
        for v in adj[current]:
            if not visited[v]:
                visited[v] = True
                queue.append(v)
                
def bfs_extend(adj, n):
    visited = [False] * n;
    for i in range(n):
        if not visited[i]:
            bfs(adj, visited, i)
            
n, m = map(int, input().split())
adj = [[] for _ in range(n)]

for _ in range(m):
    u, v = map(int, input().split())
    add_edge(adj, u, v)
bfs_extend(adj, n)
