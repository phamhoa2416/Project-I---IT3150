import java.util.*; 

public class SquareLists { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        
        int number = input.nextInt();
        int i = 1;
        while (i <= number) {
            System.out.println(i + " " + i * i);
            i++;
        }

        input.close();
    }
}


