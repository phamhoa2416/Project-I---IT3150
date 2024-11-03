#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ORDERS 10000
#define MAX_SHOPS 100
#define MAX_CUSTOMERS 100

typedef struct {
    int time;
    int price;
} TimeOrder;

typedef struct {
    char customer_id[20];
    int price;
} CustomerConsumption;

typedef struct {
    char shop_id[20];
    int revenue;
    int customer_count;
    CustomerConsumption customers[MAX_CUSTOMERS];
} ShopRevenue;

int total_orders = 0;
int total_revenue = 0;
int shop_count = 0;
ShopRevenue shops[MAX_SHOPS];
TimeOrder time_order[MAX_ORDERS];
int prefix_sum[MAX_ORDERS];

int time_to_seconds(char* timestamp) {
    int hour, minute, second;
    sscanf(timestamp, "%d:%d:%d", &hour, &minute, &second);
    return hour * 3600 + minute * 60 + second;
}

int find_shop_index(const char* shop_id) {
    for (int i = 0; i < shop_count; ++i) {
        if (strcmp(shops[i].shop_id, shop_id) == 0)
            return i;
    }
    return -1;
}

int find_customer_index(ShopRevenue* shop, const char* customer_id) {
    for (int i = 0; i < shop->customer_count; ++i) {
        if (strcmp(shop->customers[i].customer_id, customer_id) == 0)
            return i;
    }
    return -1;
}

int compare_time_order(const void* a, const void* b) {
    return ((TimeOrder*)a)->time - ((TimeOrder*)b)->time;
}

void process_order(char* line) {
    char customer_id[20], product_id[20], shop_id[20], timestamp[20];
    int price, shop_index, customer_index;

    sscanf(line, "%s %s %d %s %s", customer_id, product_id, &price, shop_id, timestamp);

    total_orders++;
    total_revenue += price;

    shop_index = find_shop_index(shop_id);
    if (shop_index == -1) {
        shop_index = shop_count++;
        strcpy(shops[shop_index].shop_id, shop_id);
        shops[shop_index].revenue = 0;
        shops[shop_index].customer_count = 0;
    }
    shops[shop_index].revenue += price;

    customer_index = find_customer_index(&shops[shop_index], customer_id);
    if (customer_index == -1) {
        customer_index = shops[shop_index].customer_count++;
        strcpy(shops[shop_index].customers[customer_index].customer_id, customer_id);
        shops[shop_index].customers[customer_index].price = 0;
    }
    shops[shop_index].customers[customer_index].price += price;

    time_order[total_orders - 1].time = time_to_seconds(timestamp);
    time_order[total_orders - 1].price = price;
}

void calculate_prefix_sum() {
    prefix_sum[0] = time_order[0].price;
    for (int i = 1; i < total_orders; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + time_order[i].price;
    }
}

void handle_query(char* line) {
    char query[50];
    sscanf(line, "%s", query);

    if (strcmp(query, "?total_number_orders") == 0) {
        printf("%d\n", total_orders);
    } else if (strcmp(query, "?total_revenue") == 0) {
        printf("%d\n", total_revenue);
    } else if (strcmp(query, "?revenue_of_shop") == 0) {
        char shop_id[20];
        sscanf(line, "%*s %s", shop_id);
        int shop_index = find_shop_index(shop_id);
        printf("%d\n", shop_index != -1 ? shops[shop_index].revenue : 0);
    } else if (strcmp(query, "?total_consume_of_customer_shop") == 0) {
        char customer_id[20], shop_id[20];
        sscanf(line, "%*s %s %s", customer_id, shop_id);
        int shop_index = find_shop_index(shop_id);
        if (shop_index != -1) {
            int customer_index = find_customer_index(&shops[shop_index], customer_id);
            printf("%d\n", customer_index != -1 ? shops[shop_index].customers[customer_index].price : 0);
        } else {
            printf("0\n");
        }
    } else if (strcmp(query, "?total_revenue_in_period") == 0) {
        char from_time[20], to_time[20];
        sscanf(line, "%*s %s %s", from_time, to_time);
        
        int from_seconds = time_to_seconds(from_time);
        int to_seconds = time_to_seconds(to_time);

        int start_index = -1, end_index = -1;
        for (int i = 0; i < total_orders; ++i) {
            if (time_order[i].time >= from_seconds) {
                start_index = i;
                break;
            }
        }
        for (int i = total_orders - 1; i >= 0; --i) {
            if (time_order[i].time <= to_seconds) {
                end_index = i;
                break;
            }
        }

        if (start_index != -1 && end_index != -1 && start_index <= end_index) {
            int period_revenue = prefix_sum[end_index];
            if (start_index > 0)
                period_revenue -= prefix_sum[start_index - 1];
            printf("%d\n", period_revenue);
        } else {
            printf("0\n");
        }
    }
}

int main() {
    char line[256];
    
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        process_order(line);
    }

    qsort(time_order, total_orders, sizeof(TimeOrder), compare_time_order);

    calculate_prefix_sum();

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        handle_query(line);
    }

    return 0;
}
