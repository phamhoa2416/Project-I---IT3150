import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.BufferedWriter;
import java.util.StringTokenizer;
import java.util.Arrays;

class DSU {
    private int[] parent, rank;

    public DSU(int size) {
        parent = new int[size];
        rank = new int[size];

        for (int i = 0; i < size; ++i) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    public int find(int i) {
        if (parent[i] == -1)
            return i;
        return parent[i] = find(parent[i]);
    }

    public void unite(int u, int v) {
        int s1 = find(u);
        int s2 = find(v);

        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            } else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            } else {
                parent[s2] = s1;
                rank[s1]++;
            }
        }
    }
}

class Edge implements Comparable<Edge> {
    int u, v, w;

    public Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }

    @Override
    public int compareTo(Edge other) {
        return Integer.compare(this.w, other.w);
    }
}

public class MSTKruskal {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

        StringTokenizer st = new StringTokenizer(reader.readLine());
        int n = Integer.parseInt(st.nextToken());  
        int m = Integer.parseInt(st.nextToken());  

        Edge[] edges = new Edge[m];

        for (int i = 0; i < m; ++i) {
            st = new StringTokenizer(reader.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());
            edges[i] = new Edge(u - 1, v - 1, w); 
        }

        writer.write(kruskalMST(n, edges)+ "\n");
        writer.flush();
        reader.close();
        writer.close();
    }

    public static long kruskalMST(int n, Edge[] edges) {
        Arrays.sort(edges); 

        DSU dsu = new DSU(n);
        long result = 0;

        for (Edge edge : edges) {
            int u = edge.u;
            int v = edge.v;

            if (dsu.find(u) != dsu.find(v)) { 
                dsu.unite(u, v);
                result += edge.w;
            }
        }
        return result;
    }
}

