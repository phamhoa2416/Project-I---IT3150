import sys
import bisect

def time_to_seconds(timestamp):
    hour, minute, second = map(int, timestamp.split(':')) 
    return hour * 3600 + minute * 60 + second

if __name__ == "__main__":
    total_orders = 0
    total_revenue = 0
    shop_revenue = {}
    customer_consumption_of_shop = {}
    time_order = []
    
    for line in sys.stdin:
        line = line.strip()
        if line == "#":
            break
        
        customer_id, product_id, price, shop_id, timestamp = line.split(" ")
        price = int(price)
        
        total_orders += 1
        total_revenue += price
        shop_revenue[shop_id] = shop_revenue.get(shop_id, 0) + price
        
        if shop_id not in customer_consumption_of_shop:
            customer_consumption_of_shop[shop_id] = {}
        customer_consumption_of_shop[shop_id][customer_id] = customer_consumption_of_shop[shop_id].get(customer_id, 0) + price
        
        time_order.append((time_to_seconds(timestamp), price))
        
    time_order.sort()
    
    prefix_sum = [0] * len(time_order)
    prefix_sum[0] = time_order[0][1]
    for i in range(1, len(time_order)):
        prefix_sum[i] = prefix_sum[i - 1] + time_order[i][1]
        
    for line in sys.stdin:
        line = line.strip()
        if line == "#":
            break
        
        parts = line.split()
        query = parts[0]
        
        if query == "?total_number_orders":
            print(total_orders)
        elif query == "?total_revenue":
            print(total_revenue)
        elif query == "?revenue_of_shop":
            shop_id = parts[1]
            print(shop_revenue.get(shop_id, 0))
        elif query == "?total_consume_of_customer_shop":
            customer_id, shop_id = parts[1], parts[2]
            print(customer_consumption_of_shop.get(shop_id, {}).get(customer_id, 0))   
        elif query == "?total_revenue_in_period":
            from_time, to_time = parts[1], parts[2]
            from_seconds = time_to_seconds(from_time)
            to_seconds = time_to_seconds(to_time)
            
            lower = bisect.bisect_left(time_order, (from_seconds, 0))
            upper = bisect.bisect_right(time_order, (to_seconds, float("inf"))) - 1
            
            period_revenue = 0
            if lower <= upper:
                period_revenue = prefix_sum[upper] - (prefix_sum[lower - 1] if lower > 0 else 0)
                
            print(period_revenue)
        