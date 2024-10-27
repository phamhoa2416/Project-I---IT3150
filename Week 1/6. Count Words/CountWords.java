import java.util.*; 

public class CountWords { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        
        int countWord = 0;
        while (input.hasNextLine()) {
            String line = input.nextLine();
            String formattedLine = line.trim().replaceAll("\\s+", " ");
            if (!formattedLine.isEmpty()) {
                countWord += formattedLine.split("\\s").length;
            }
        }
        System.out.print(countWord);
        input.close();
    }
}
