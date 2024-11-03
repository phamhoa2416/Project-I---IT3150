#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

int total_transactions = 0;
int total_money_transaction = 0;
map<string, int> from_transactions;
set<string> unique_accounts;
unordered_map<string, vector<string>> graph;

bool has_cycle_of_length_k(const string& start, const string& current, int k, int depth, set<string> visited) {
    if (depth == k) {
        return current == start;
    }
    visited.insert(current);
    
    for (const auto& neighbor: graph[current]) {
        if (neighbor == start && depth + 1 == k) 
            return true;
            
        if (visited.find(neighbor) == visited.end()) 
            if (has_cycle_of_length_k(start, neighbor, k, depth + 1, visited))
                return true;
    }
    
    visited.erase(current);
    return false;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line == "#")
            break;
            
        stringstream ss(line);
        string from_account, to_account, time_point, atm;
        int money;
        ss >> from_account >> to_account >> money >> time_point >> atm;
        
        total_transactions++;
        total_money_transaction += money;
        
        from_transactions[from_account] += money;
        
        unique_accounts.insert(from_account);
        unique_accounts.insert(to_account);
        graph[from_account].push_back(to_account);
    }
    
    while (getline(cin, line)) {
        if (line == "#")
            break;
            
        stringstream ss(line);
        string query;
        ss >> query;    
        if (query == "?number_transactions") {
            cout << total_transactions << endl;
        } else if (query == "?total_money_transaction") {
            cout << total_money_transaction << endl;
        } else if (query == "?list_sorted_accounts") {
            for (const auto& account: unique_accounts) 
                cout << account << " ";
            cout << endl;
        } else if (query == "?total_money_transaction_from") {
            string transaction_from_account;
            ss >> transaction_from_account;
            cout << from_transactions[transaction_from_account] << endl;
        } else if (query == "?inspect_cycle") {
            string inspect_cycle_account;
            int k;
            ss >> inspect_cycle_account >> k;
            
            set<string> visited;
            bool has_cycle = has_cycle_of_length_k(inspect_cycle_account, inspect_cycle_account, k, 0, visited);
            cout << (has_cycle ? 1 : 0) << endl;
        }
    }
    
    return 0;
}
