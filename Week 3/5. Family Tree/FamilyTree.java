//JAVA 
import java.util.Scanner; 
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

class Node {
    String name;
    List<Node> children;
    int descendants;
    int generation;
    
    Node(String name) {
        this.name = name;
        this.children = new ArrayList<>();
        this.descendants = 0;
        this.generation = 0;
    }
}

public class FamilyTree { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in);
        
        List<Map.Entry<String, String>> input = new ArrayList<>();
        
        String child, parent;
        while (true) {
            child = sc.next();
            if (child.equals("***")) break;
            parent = sc.next();
            input.add(Map.entry(child, parent));
        }
        
        Map<String, Node> familyTree = buildFamilyTree(input);
        
        for (Node node : familyTree.values()) {
            if (node.generation == 0) 
                dfs(node, 1);
        }
        
        while (true) {
            child = sc.next();
            if (child.equals("***")) break;
            parent = sc.next();
            if (child.equals("descendants")) {
                System.out.println(descendantCount(familyTree, parent));
            } else if (child.equals("generation")) {
                System.out.println(generationCount(familyTree, parent));
            }
        }

        sc.close();
    }
    
    public static Map<String, Node> buildFamilyTree(List<Map.Entry<String, String>> input) {
        Map<String, Node> familyTree = new HashMap<>();
        
        for (Map.Entry<String, String> pair : input) {
            String child = pair.getKey();
            String parent = pair.getValue();
            
            familyTree.putIfAbsent(child, new Node(child));
            familyTree.putIfAbsent(parent, new Node(parent));
            
            familyTree.get(parent).children.add(familyTree.get(child));
        }
        
        return familyTree;
    }
    
    public static int dfs(Node node, int generation) {
        node.generation = generation;
        node.descendants = 0;
        
        for (Node child : node.children) 
            node.descendants += 1 + dfs(child, generation + 1);
        
        return node.descendants;
    }
    
    public static int descendantCount(Map<String, Node> node, String name) {
        return node.containsKey(name) ? node.get(name).descendants : 0;
    }
    
    public static int generationCount(Map<String, Node> node, String parent) {
        if (node.containsKey(parent)) {
            int max_generation = 0;
            for (Node child : node.get(parent).children) {
                max_generation = Math.max(max_generation, 1 + generationCount(node, child.name));
            }
            return max_generation;
        }
        return 0;
    }
}

