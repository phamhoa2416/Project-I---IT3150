import java.util.*; 

public class ListNumbersDivisibleByN { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        
        int start;
        if (100 % n == 0) start = 100/n;
        else start = 100/n + 1;
        int end = 999/n;
        

        for (int i = start; i <= end; ++i) 
            System.out.print(i * n + " ");
        
        input.close();
    }
}

