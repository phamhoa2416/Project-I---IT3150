import java.util.*; 

public class FibonacciSequence { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int num = input.nextInt();
        
        System.out.print(fibonacci(num - 1));
        input.close();
    }
    
    public static int fibonacci(int n) {
        if (n == 0) return 0;
        if (n <= 2) return 1;
        else return fibonacci(n - 1) + fibonacci(n - 2);
    }
}
