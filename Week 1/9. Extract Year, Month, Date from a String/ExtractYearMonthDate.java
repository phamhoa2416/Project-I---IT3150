import java.util.*; 

public class ExtractYearMonthDate { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        String date = input.nextLine();
        
        if (!isValidDate(date)) {
            System.out.println("INCORRECT"); 
        } else {
            int year = Integer.parseInt(date.substring(0, 4));
            int month = Integer.parseInt(date.substring(5, 7));
            int day = Integer.parseInt(date.substring(8, 10));
            
            System.out.println(year);
            System.out.println(month);
            System.out.println(day);
        }
        input.close();
    }
    
    private static boolean isValidDate(String dateString) {
        if (dateString.length() != 10) {
            return false;
        }
        
        if (dateString.charAt(4) != '-' || dateString.charAt(7) != '-') {
            return false;
        }
        
        for (int i = 0; i < 4; ++i) {
            if (!Character.isDigit(dateString.charAt(i))) {
                return false;
            }
        }
        
        for (int i = 5; i < 7; ++i) {
            if (!Character.isDigit(dateString.charAt(i))) {
                return false;
            }
        } 
        
        for (int i = 8; i < 10; ++i) {
            if (!Character.isDigit(dateString.charAt(i))) {
                return false;
            }
        }        
        
        int month = Integer.parseInt(dateString.substring(5, 7));
        int day = Integer.parseInt(dateString.substring(8, 10));
        
        if (month < 1 || month > 12) {
            return false;
        }
        
        if (day < 1 || day > 31) {
            return false;
        }
        
        return true;
    }
}
