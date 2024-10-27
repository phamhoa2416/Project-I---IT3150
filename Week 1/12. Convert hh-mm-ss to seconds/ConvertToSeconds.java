import java.util.*; 

public class ConvertToSeconds { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        String hourString = input.nextLine();
        
        if (!isValidHour(hourString)) {
            System.out.println("INCORRECT"); 
        } else {
            int hour = Integer.parseInt(hourString.substring(0, 2));
            int minute = Integer.parseInt(hourString.substring(3, 5));
            int second = Integer.parseInt(hourString.substring(6, 8));
            
            int secondCount = hour * 3600 + minute * 60 + second;
            System.out.println(secondCount);
        }

        input.close();
    }
    
    private static boolean isValidHour(String hourString) {
        if (hourString.length() != 8 || hourString.charAt(2) != ':' || hourString.charAt(5) != ':' || !hourString.matches("\\d{2}:\\d{2}:\\d{2}")) {
            return false;
        }       
        
        int hour = Integer.parseInt(hourString.substring(0, 2));
        int minute = Integer.parseInt(hourString.substring(3, 5));
        int second = Integer.parseInt(hourString.substring(6, 8));
        
        if (hour > 23 || hour < 0 || minute > 59 || minute < 0 || second > 59 || second < 0) {
            return false;
        }
        
        return true;
    }
}

