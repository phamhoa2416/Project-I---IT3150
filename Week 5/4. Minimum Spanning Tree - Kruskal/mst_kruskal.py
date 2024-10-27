class DSU:
    def __init__(self, size):
        self.parent = [-1] * size
        self.rank = [1] * size
        
    def find(self, i):
        if self.parent[i] == -1:
            return i
            
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
        
    def unite(self, u, v):
        s1 = self.find(u)
        s2 = self.find(v)
        
        if s1 != s2:
            if self.rank[s1] < self.rank[s2]:
                self.parent[s1] = s2
            elif self.rank[s2] > self.rank[s1]:
                self.parent[s2] = s1
            else:
                self.parent[s2] = s1
                self.rank[s1] += 1 
            
def kruskal_mst(n, edges):
    edges.sort()
    dsu = DSU(n)
    result = 0
    
    for edge in edges:
        w, u, v = edge
        u -= 1 
        v -= 1 
        
        if dsu.find(u) != dsu.find(v):
            dsu.unite(u, v)
            result += w
            
    return result
    
if __name__ == "__main__":
    n, m = map(int, input().split())
    edges = []
    
    for _ in range(m):
        u, v, w = map(int, input().split())
        edges.append((w, u, v))
    print(kruskal_mst(n, edges))
    
