import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.StringTokenizer;

public class MaxFlow {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(reader.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int source = Integer.parseInt(st.nextToken());
        int sink = Integer.parseInt(st.nextToken());

        int[][] graph = new int[n][n];

        for (int i = 0; i < m; ++i) {
            st = new StringTokenizer(reader.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int w = Integer.parseInt(st.nextToken());
            graph[u - 1][v - 1] = w;
        }

        MaxFlow maxFlow = new MaxFlow();
        System.out.println(maxFlow.edmondsKarp(graph, source, sink));
    }

    boolean bfs(int[][] residualGraph, int source, int sink, int parent[]) {
        int length = residualGraph.length;

        boolean visited[] = new boolean[length];
        for (int i = 0; i < length; ++i) 
            visited[i] = false;

        LinkedList<Integer> queue = new LinkedList<>();
        queue.add(source);
        visited[source] = true;
        parent[source] = -1;

        while (!queue.isEmpty()) {
            int u = queue.poll();

            for (int v = 0; v < length; ++v) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    if (v == sink) {
                        parent[v] = u;
                        return true;
                    }
                    queue.add(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }

        return false;
    }

    int edmondsKarp(int graph[][], int source, int sink) {
        source--;
        sink--;

        int[][] residualGraph = graph;
        int[] parent = new int[graph.length];

        int maxFlow = 0;

        while (bfs(residualGraph, source, sink, parent)) {
            int pathFlow = Integer.MAX_VALUE;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = Math.min(pathFlow, residualGraph[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
}
