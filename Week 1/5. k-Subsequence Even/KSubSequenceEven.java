import java.util.*; 

public class KSubSequenceEven { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int k = input.nextInt();
        
        int[] sequence = new int[n];
        for (int i = 0; i < n; ++i) {
            sequence[i] = input.nextInt();
        }
        
        int[] prefix_sum = new int[n + 1];
        int count = 0;
        
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + sequence[i];
        }
        
        for (int i = 0; i < n - k + 1; ++i) {
            if ((prefix_sum[i + k] - prefix_sum[i]) % 2 == 0) {
                count++;
            }
        }
        
        System.out.print(count);
        input.close();
    }
}

