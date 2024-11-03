#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

int time_to_seconds(string timestamp)
{
    int hour, minute, second;
    sscanf(timestamp.c_str(), "%d:%d:%d", &hour, &minute, &second);
    return hour * 60 * 60 + minute * 60 + second;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int total_orders = 0;
    int total_revenue = 0;
    unordered_map<string, int> shop_revenue;
    unordered_map<string, unordered_map<string, int>> customer_consumption_of_shop;
    vector<pair<int, int>> time_order;

    string line;

    // Operational data block
    while (getline(cin, line))
    {
        if (line == "#")
            break;

        stringstream ss(line);
        string customer_id, product_id, shop_id, timestamp;
        int price;

        ss >> customer_id >> product_id >> price >> shop_id >> timestamp;

        total_orders++;
        total_revenue += price;
        shop_revenue[shop_id] += price;
        customer_consumption_of_shop[shop_id][customer_id] += price;
        time_order.push_back({time_to_seconds(timestamp), price});
    }

    sort(time_order.begin(), time_order.end());

    // Build prefix sums for total revenue up to each time point
    vector<int> prefix_sum(time_order.size());
    prefix_sum[0] = time_order[0].second;
    for (size_t i = 1; i < time_order.size(); ++i)
        prefix_sum[i] = prefix_sum[i - 1] + time_order[i].second;

    // Query block
    while (getline(cin, line))
    {
        if (line == "#")
            break;

        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?total_number_orders")
            cout << total_orders << endl;
        else if (query == "?total_revenue")
            cout << total_revenue << endl;
        else if (query == "?revenue_of_shop")
        {
            string shop_id;
            ss >> shop_id;
            cout << shop_revenue[shop_id] << endl;
        }
        else if (query == "?total_consume_of_customer_shop")
        {
            string customer_id, shop_id;
            ss >> customer_id >> shop_id;
            cout << customer_consumption_of_shop[shop_id][customer_id] << endl;
        }
        else if (query == "?total_revenue_in_period")
        {
            string from_time, to_time;
            ss >> from_time >> to_time;

            int from_seconds = time_to_seconds(from_time);
            int to_seconds = time_to_seconds(to_time);

            int period_revenue = 0;

            auto lower = lower_bound(time_order.begin(), time_order.end(), make_pair(from_seconds, 0));
            auto upper = upper_bound(time_order.begin(), time_order.end(), make_pair(to_seconds, INT_MAX));

            int start_index = distance(time_order.begin(), lower);
            int end_index = distance(time_order.begin(), upper) - 1;

            if (start_index <= end_index)
            {
                period_revenue = prefix_sum[end_index];
                if (start_index > 0)
                    period_revenue -= prefix_sum[start_index - 1];
            }

            cout << period_revenue << endl;
        }
    }
    return 0;
}
