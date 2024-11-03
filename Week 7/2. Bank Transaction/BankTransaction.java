import java.io.*;
import java.util.*;

public class BankTransaction {
    static int totalTransactions = 0;
    static int totalMoneyTransactions = 0;
    static Map<String, Integer> fromTransactions = new HashMap<>();
    static Set<String> uniqueAccounts = new TreeSet<>();
    static Map<String, List<String>> graph = new HashMap<>();
    
    public static boolean hasCycleOfLengthK(String start, String current, int k, int depth, Set<String> visited) {
        if (depth == k) 
            return current == start;
        visited.add(current);
        
        if (graph.containsKey(current)) {
            for (String neighbor: graph.get(current)) {
                if (neighbor.equals(start) && depth + 1 == k)
                    return true;
                    
                if (!visited.contains(neighbor)) {
                    if (hasCycleOfLengthK(start, neighbor, k, depth + 1, visited))
                        return true;
                }
            }
        }
        visited.remove(current);
        return false;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        while (true) {
            String line = reader.readLine().trim();
            if (line.equals("#")) break;
            
            String[] parts = line.split(" ");
            String fromAccount = parts[0];
            String toAccount = parts[1];
            int money = Integer.parseInt(parts[2]);
            
            totalTransactions++;
            totalMoneyTransactions += money;
            
            fromTransactions.put(fromAccount, fromTransactions.getOrDefault(fromAccount, 0) + money);
            
            uniqueAccounts.add(fromAccount);
            uniqueAccounts.add(toAccount);
            
            graph.computeIfAbsent(fromAccount, k -> new ArrayList<>()).add(toAccount);
        }
        
        while (true) {
            String line = reader.readLine().trim();
            if (line.equals("#")) break;
            
            String[] parts = line.split(" ");
            String query = parts[0];
            
            switch(query) {
                case ("?number_transactions"):
                    System.out.println(totalTransactions);
                    break;
                
                case ("?total_money_transaction"):
                    System.out.println(totalMoneyTransactions);
                    break;
                
                case ("?list_sorted_accounts"):
                    System.out.println(String.join(" ", uniqueAccounts));
                    break;
                    
                case("?total_money_transaction_from"):
                    String transactionFromAccount = parts[1];
                    System.out.println(fromTransactions.getOrDefault(transactionFromAccount, 0));
                    break;
                    
                case("?inspect_cycle"):
                    String inspectCycleAccount = parts[1];
                    int k = Integer.parseInt(parts[2]);
                    
                    Set<String> visited = new HashSet<>();
                    boolean hasCycle = hasCycleOfLengthK(inspectCycleAccount, inspectCycleAccount, k, 0, visited);
                    System.out.println(hasCycle ? 1 : 0);
            }
        }
    }
}
