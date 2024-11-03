#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 1000
#define MAX_NAME_LEN 21
#define MAX_TRANSACTIONS 10000

typedef struct Node {
    char account[MAX_NAME_LEN];
    struct Node* next;
} Node;

typedef struct {
    char from_account[MAX_NAME_LEN];
    char to_account[MAX_NAME_LEN];
    int money;
} Transaction;

int total_transactions = 0;
int total_money_transaction = 0;
Transaction transactions[MAX_TRANSACTIONS];
char unique_accounts[MAX_ACCOUNTS][MAX_NAME_LEN];
int account_count = 0;

Node* graph[MAX_ACCOUNTS];

int find_account_index(const char* account) {
    for (int i = 0; i < account_count; ++i) {
        if (strcmp(unique_accounts[i], account) == 0) {
            return i;
        }
    }
    return -1;
}

void add_account(const char* account) {
    if (find_account_index(account) == -1) {
        strcpy(unique_accounts[account_count++], account);
    }
}

void add_edge(const char* from, const char* to) {
    int from_index = find_account_index(from);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->account, to);
    newNode->next = graph[from_index];
    graph[from_index] = newNode;
}

int has_cycle_of_length_k(int start, int current, int k, int length, int visited[], int* path) {
    if (length == k) {
        return current == start;
    }
    
    if (length > k) return 0;
    
    for (Node* neighbor = graph[current]; neighbor != NULL; neighbor = neighbor->next) {
        int neighbor_index = find_account_index(neighbor->account);
        
        if (visited[neighbor_index] && (neighbor_index != start || length != k-1)) 
            continue;
            
        visited[neighbor_index] = 1;
        path[length] = neighbor_index;
        
        if (has_cycle_of_length_k(start, neighbor_index, k, length + 1, visited, path)) {
            return 1;
        }
        
        if (neighbor_index != start)
            visited[neighbor_index] = 0;
    }
    
    return 0;
}

void clear_graph() {
    for (int i = 0; i < account_count; ++i) {
        Node* current = graph[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        graph[i] = NULL;  
    }
}

int main() {
    memset(graph, 0, sizeof(graph));
    
    char line[256];
    
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        
        Transaction transaction;
        char time_point[10], atm[11];
        
        sscanf(line, "%s %s %d %s %s", transaction.from_account, transaction.to_account, 
               &transaction.money, time_point, atm);
        
        transactions[total_transactions++] = transaction;
        total_money_transaction += transaction.money;
        
        add_account(transaction.from_account);
        add_account(transaction.to_account);
        add_edge(transaction.from_account, transaction.to_account);
    }
    
    while(fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        
        char query[MAX_NAME_LEN];
        sscanf(line, "%s", query);
        
        if (strcmp(query, "?number_transactions") == 0) {
            printf("%d\n", total_transactions);
        } else if (strcmp(query, "?total_money_transaction") == 0) {
            printf("%d\n", total_money_transaction);
        } else if (strcmp(query, "?list_sorted_accounts") == 0) {
            qsort(unique_accounts, account_count, MAX_NAME_LEN, 
                  (int (*)(const void*, const void*))strcmp);
            for (int i = 0; i < account_count; ++i) {
                printf("%s ", unique_accounts[i]);
            }
            printf("\n");
        } else if (strcmp(query, "?total_money_transaction_from") == 0) {
            char from_account[MAX_NAME_LEN];
            sscanf(line, "%s %s", query, from_account);
            int total_from = 0;
            
            for (int i = 0; i < total_transactions; ++i) {
                if (strcmp(transactions[i].from_account, from_account) == 0) {
                    total_from += transactions[i].money;
                }
            }
            
            printf("%d\n", total_from);
        } else if (strcmp(query, "?inspect_cycle") == 0) {
            char inspect_cycle_account[MAX_NAME_LEN];
            int k;
            sscanf(line, "%s %s %d", query, inspect_cycle_account, &k);
            
            int account_index = find_account_index(inspect_cycle_account);
            if (account_index == -1) {
                printf("0\n");
                continue;
            }
            
            int visited[MAX_ACCOUNTS] = {0};
            int path[MAX_ACCOUNTS] = {0};
            visited[account_index] = 1;  
            path[0] = account_index;     
            
            int has_cycle = has_cycle_of_length_k(account_index, account_index, k, 0, 
                                                 visited, path);
            printf("%d\n", has_cycle ? 1 : 0);
        }
    }
    
    clear_graph();
    return 0;
}
