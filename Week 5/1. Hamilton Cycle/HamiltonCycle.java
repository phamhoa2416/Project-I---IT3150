import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

class Graph {
    private int[][] graph;
    private int[] path;
    
    public Graph(int size) {
        this.graph = new int[size][size];
        this.path = new int[size];
    }
    
    public int[][] getGraph() {
        return graph;
    }
    
    public void setGraph(int[][] graph) {
        this.graph = graph;
    }
    
    boolean isSafe(int v, int pos) {
        if (graph[path[pos - 1]][v] == 0)
            return false;
        
        for (int i = 0; i < pos; ++i) {
            if (path[i] == v) 
                return false;
        }
        
        return true;
    }
    
    boolean hamiltonianUtil(int pos) {
        if (pos == graph.length)
            return graph[path[pos - 1]][path[0]] == 1;
            
        for (int v = 0; v < graph.length; ++v) {
            if (isSafe(v, pos)) {
                path[pos] = v;
                
                if (hamiltonianUtil(pos + 1))
                    return true;
                    
                path[pos] = -1;
            }
        }
        return false;
    }
    
    boolean isHamilton() {
        Arrays.fill(path, -1);
        
        path[0] = 0;
        return hamiltonianUtil(1);
    }
}

public class HamiltonCycle { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in);
        
        int T = sc.nextInt();
        
        List<Integer> results = new ArrayList<>();
        
        for (int t = 0; t < T; ++t) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            
            Graph g = new Graph(n);
            int[][] tempGraph = new int[n][n];
            
            for (int i = 0; i < m; ++i) {
                int u = sc.nextInt();
                int v = sc.nextInt();
                tempGraph[u - 1][v - 1] = 1;
                tempGraph[v - 1][u - 1] = 1;
            }
            g.setGraph(tempGraph);
            
            results.add(g.isHamilton() ? 1 : 0);
        }
        
        for (int result : results) {
            System.out.println(result);
        }
        
        sc.close();
    }
}
