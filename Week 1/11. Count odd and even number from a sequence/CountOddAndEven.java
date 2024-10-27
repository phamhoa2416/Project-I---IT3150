import java.util.*; 

public class CountOddAndEven { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        
        int countOdd = 0;
        int countEven = 0;
        
        for (int i = 0; i < size; ++i) {
            int value = input.nextInt();
            if (value % 2 == 0) countEven++;
            else countOdd++;
        }
        
        System.out.println(countOdd + " " + countEven);
        input.close();
    }
}

