import java.util.*; 

public class SumArray { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += input.nextInt();
        }
        
        System.out.println(sum);
        input.close();
    }
}

