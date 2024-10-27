import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Arrays;
import java.util.Collections;

class Graph {
    private int numVertices;
    private List<List<Integer>> adj;
    private boolean[] visited;
    
    public Graph(int numVertices) {
        this.numVertices = numVertices;
        this.adj = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            adj.add(new ArrayList<>());
        }
        this.visited = new boolean[numVertices];
    }
    
    public void addEdge(int u, int v) {
        adj.get(u - 1).add(v - 1);
        adj.get(v - 1).add(u - 1);
        
        Collections.sort(adj.get(u - 1));
        Collections.sort(adj.get(v - 1));
    }
    
    public void bfs(int u) {
        Queue<Integer> q = new LinkedList<>();
        visited[u] = true;
        q.add(u);
        
        while (!q.isEmpty()) {
            int current = q.poll();
            System.out.print((current + 1) + " ");
            
            for (int v: adj.get(current)) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.add(v);
                }
            }
        }
    }
    
    public void bfs_extend() {
        Arrays.fill(visited, false);
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i])
                bfs(i);
        }
    }
}

public class BFSListOrderNodes { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int m = sc.nextInt();
        
        Graph g = new Graph(n);
        
        for (int i = 0; i < m; ++i) {
            int u = sc.nextInt();
            int v = sc.nextInt();
            g.addEdge(u, v);
        }
        
        g.bfs_extend();
        sc.close();
    }
}
