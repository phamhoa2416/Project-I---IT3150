import java.util.*; 

public class ToUpperCase { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        StringBuilder message = new StringBuilder();
        
        while (input.hasNextLine()) {
            String line = input.nextLine();
            for (int i = 0; i < line.length(); ++i) {
                char c = line.charAt(i);
                if (c >= 97 && c <= 122) c-= 32;
                message.append(c);
            }
            message.append("\n");
        }
        System.out.print(message);
        input.close();
    }
}