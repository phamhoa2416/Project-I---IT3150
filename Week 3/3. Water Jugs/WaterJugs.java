//JAVA 
import java.util.*; 

public class WaterJugs { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in);
        int firstCapacity = sc.nextInt();
        int secondCapacity = sc.nextInt();
        int requiredAmount = sc.nextInt();
        
        if (requiredAmount % gcd(firstCapacity, secondCapacity) != 0 || requiredAmount > Math.max(firstCapacity, secondCapacity)) 
            System.out.println(-1);
        else {
            System.out.println(Math.min(pourWater(firstCapacity, secondCapacity, requiredAmount), pourWater(secondCapacity, firstCapacity, requiredAmount)));
        }

        sc.close();
    }
    
    public static int gcd(int a, int b) {
        if (a == 0) return b;
        else return gcd(b % a, a);
    }
    
    public static int pourWater(int firstCapacity, int secondCapacity, int requiredAmount) {
        int firstAmount = 0, secondAmount = 0;
        int steps = 0;
        
        while (firstAmount != requiredAmount && secondAmount != requiredAmount) {
            if (firstAmount == 0)
                firstAmount = firstCapacity;
            else if (secondAmount == secondCapacity) 
                secondAmount = 0;
            else {
                int temp = Math.min(secondCapacity - secondAmount, firstAmount);
                firstAmount -= temp;
                secondAmount += temp;
            }
            steps++;
        }
        
        return steps;
    }
}

