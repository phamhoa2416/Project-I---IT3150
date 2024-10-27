import java.util.*; 

public class SolveDegree2PolynomialEquation { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        
        int a = input.nextInt();
        int b = input.nextInt();
        int c = input.nextInt();
        

        if (a == 0) {
            if (b == 0) {
                System.out.print("NO SOLUTION");
            } else {
                float result = (float) (-c) / b;
                System.out.printf("%.2f", result);
            }
        } else {
            float delta = b * b - 4 * a * c;
            if (delta < 0) {
                System.out.print("NO SOLUTION");
            } else if (delta > 0) {
                float val1 = (float) (-b - Math.sqrt(delta)) / (2 * a);
                float val2 = (float) (-b + Math.sqrt(delta)) / (2 * a);
                System.out.printf("%.2f %.2f", val1, val2);
            } else {
                float result = (float) -b / (2 * a);
                System.out.printf("%.2f", result);
            }
        }

        input.close();
    }
}
