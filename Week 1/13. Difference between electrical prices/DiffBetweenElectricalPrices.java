import java.util.*; 

public class DiffBetweenElectricalPrices { 
    public static void main(String[] args) { 
        Scanner input = new Scanner(System.in);
        int consumption = input.nextInt();
        
        float currentBill = calculateCurrentBill(consumption);
        float newBill = calculateNewBill(consumption);
        float difference = (newBill - currentBill) * 1.1f;
        
        System.out.printf("%.2f", difference);
        input.close();
    }
    
    private static float calculateCurrentBill(int consumption) {
        double bill = 0;
        
        if (consumption <= 50) {
            bill = consumption * 1728;
        } else if (consumption <= 100) {
            bill = 50 * 1728 + (consumption - 50) * 1786;
        } else if (consumption <= 200) {
            bill = 50 * 1728 + 50 * 1786 + (consumption - 100) * 2074;
        } else if (consumption <= 300) {
            bill = 50 * 1728 + 50 * 1786 + 100 * 2074 + (consumption - 200) * 2612;
        } else if (consumption <= 400) {
            bill = 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + (consumption - 300) * 2919;
        } else {
            bill = 50 * 1728 + 50 * 1786 + 100 * 2074 + 100 * 2612 + 100 * 2919 + (consumption - 400) * 3015;
        }
        
        return (float) bill;
    }
    
    private static float calculateNewBill(int consumption) {
        double bill = 0;
        
        if (consumption <= 100) {
            bill = consumption * 1728;
        } else if (consumption <= 200) {
            bill = 100 * 1728 + (consumption - 100) * 2074;
        } else if (consumption <= 400) {
            bill = 100 * 1728 + 100 * 2074 + (consumption - 200) * 2612;
        } else if (consumption <= 700) {
            bill = 100 * 1728 + 100 * 2074 + 200 * 2612 + (consumption - 400) * 3111;
        } else {
            bill = 100 * 1728 + 100 * 2074 + 200 * 2612 + 300 * 3111 + (consumption - 700) * 3457;
        }
        
        return (float) bill;
    }
}

