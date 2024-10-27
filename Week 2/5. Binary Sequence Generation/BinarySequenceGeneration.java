//JAVA 
import java.util.*; 

public class BinarySequenceGeneration { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        
        int[] sequence = new int[size];
        
        generateBinarySequence(size, sequence, 0);
        input.close();
    }
    
    public static void generateBinarySequence(int size, int[] sequence, int index) {
        if (index == size) {
            for (int num : sequence) {
                System.out.print(num);
            }
            System.out.println();
            return;
        }
        
        sequence[index] = 0;
        generateBinarySequence(size, sequence, index + 1);
        
        sequence[index] = 1;
        generateBinarySequence(size, sequence, index + 1);
    }
}

