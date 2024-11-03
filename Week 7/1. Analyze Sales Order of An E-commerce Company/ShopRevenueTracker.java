import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.io.IOException;

public class ShopRevenueTracker {
    static class TimeOrder {
        int time;
        int price;

        TimeOrder(int time, int price) {
            this.time = time;
            this.price = price;
        }
    }

    static class CustomerConsumption {
        String customerID;
        int price;

        CustomerConsumption(String customerID, int price) {
            this.customerID = customerID;
            this.price = price;
        }
    }

    static class ShopRevenue {
        String shopID;
        int revenue = 0;
        Map<String, CustomerConsumption> customers = new HashMap<>();

        ShopRevenue(String shopID) {
            this.shopID = shopID;
        }

        void addRevenue(int price) {
            this.revenue += price;
        }

        void addCustomerConsumption(String customerID, int price) {
            customers.putIfAbsent(customerID, new CustomerConsumption(customerID, 0));
            customers.get(customerID).price += price;
        }

        int getCustomerConsumption(String customerID) {
            return customers.getOrDefault(customerID, new CustomerConsumption(customerID, 0)).price;
        }
    }

    static int timeToSeconds(String timestamp) {
        String[] parts = timestamp.split(":");
        int hour = Integer.parseInt(parts[0]);
        int minute = Integer.parseInt(parts[1]);
        int second = Integer.parseInt(parts[2]);
        return hour * 3600 + minute * 60 + second;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        int totalOrders = 0;
        int totalRevenue = 0;
        Map<String, ShopRevenue> shopRevenueMap = new HashMap<>();
        List<TimeOrder> timeOrders = new ArrayList<>();

        String line;
        while (!(line = reader.readLine()).equals("#")) {
                String parts[] = line.split(" ");
                String customerID = parts[0];
                @SuppressWarnings("unused")
                String productID = parts[1];
                int price = Integer.parseInt(parts[2]);
                String shopID = parts[3];
                String timestamp = parts[4];

                totalOrders++;
                totalRevenue += price;

                shopRevenueMap.putIfAbsent(shopID, new ShopRevenue(shopID));
                ShopRevenue shop = shopRevenueMap.get(shopID);
                shop.addRevenue(price);
                shop.addCustomerConsumption(customerID, price);

                timeOrders.add(new TimeOrder(timeToSeconds(timestamp), price));
        }

        timeOrders.sort(Comparator.comparing(o -> o.time));

        int[] prefixSum = new int[timeOrders.size()];
        prefixSum[0] = timeOrders.get(0).price;
        for (int i = 1; i < timeOrders.size(); ++i) {
            prefixSum[i] = prefixSum[i - 1] + timeOrders.get(i).price;
        }

        while (!(line = reader.readLine()).equals("#")) {
            String[] parts = line.split(" ");
            String query = parts[0];

            switch (query) {
                case "?total_number_orders":
                    System.out.println(totalOrders);
                    break;
        
                case "?total_revenue":
                    System.out.println(totalRevenue);
                    break;

                case "?revenue_of_shop":
                    String shopID = parts[1];
                    ShopRevenue shop = shopRevenueMap.getOrDefault(shopID, new ShopRevenue(shopID));
                    System.out.println(shop.revenue);
                    break;

                case "?total_consume_of_customer_shop":
                    String customerID = parts[1];
                    shopID = parts[2];
                    shop = shopRevenueMap.getOrDefault(shopID, new ShopRevenue(shopID));
                    System.out.println(shop.getCustomerConsumption(customerID));
                    break;
                    
                case "?total_revenue_in_period":
                    String fromTime = parts[1];
                    String toTime = parts[2];
                    int fromSeconds = timeToSeconds(fromTime);
                    int toSeconds = timeToSeconds(toTime);

                    int startIndex = -1, endIndex = -1;
                    for (int i = 0; i < timeOrders.size(); ++i) {
                        if (timeOrders.get(i).time >= fromSeconds) {
                            startIndex = i;
                            break;
                        }
                    }

                    for (int i = timeOrders.size() - 1; i >= 0; --i) {
                        if (timeOrders.get(i).time <= toSeconds) {
                            endIndex = i;
                            break;
                        }
                    } 

                    if (startIndex != -1 && endIndex != -1 && startIndex <= endIndex) {
                        int periodRevenue = prefixSum[endIndex] - (startIndex > 0 ? prefixSum[startIndex - 1] : 0);
                        System.out.println(periodRevenue);
                    } else {
                        System.out.println(0);
                    }
                    break;
            }
        }
    }
}