def add_edge(adj, u, v):
    adj[u - 1].append(v - 1)
    adj[v - 1].append(u - 1)
    
def dfs_rec(adj, visited, u):
    visited[u] = True
    
    print(u + 1, end = " ")
    
    for i in adj[u]:
        if not visited[i]:
            dfs_rec(adj, visited, i)

def dfs(adj, u):
    visited = [False] * len(adj)
    dfs_rec(adj, visited, u)
    
if __name__ == "__main__":
    n, m = map(int, input().split())
    adj = [[] for _ in range(n)]
    
    for _ in range(m):
        u, v = map(int, input().split())
        add_edge(adj, u, v)
        
    dfs(adj, 0)
