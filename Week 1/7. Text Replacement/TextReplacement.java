import java.util.*; 

public class TextReplacement { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        String target = input.nextLine();
        String replacement = input.nextLine();
        String message = input.nextLine();
        
        String changeMessage = message.replace(target, replacement);
        System.out.println(changeMessage);
        input.close();
    }
}

