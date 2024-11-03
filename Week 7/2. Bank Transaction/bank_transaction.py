from collections import defaultdict
from typing import List, Set 

total_transactions = 0
total_money_transaction = 0
from_transactions = defaultdict(int)
unique_accounts = set()
graph = defaultdict(list)

def has_cycle_of_length_k(start: str, current: str, k: int, depth: int, visited: Set[str]) -> bool:
    if depth == k:
        return current == start
        
    visited.add(current)
    
    for neighbor in graph[current]:
        if neighbor == start and depth + 1 == k:
            return True
        if neighbor not in visited:
            if has_cycle_of_length_k(start, neighbor, k, depth + 1, visited):
                return True
                
    visited.remove(current)
    return False
    
while True:
    line = input().strip()
    if line == "#":
        break
    
    parts = line.split()
    from_account, to_account, money, time_point, atm = parts[0], parts[1], int(parts[2]), parts[3], parts[4]
    
    total_transactions += 1 
    total_money_transaction += money
    
    from_transactions[from_account] += money
    
    unique_accounts.add(from_account)
    unique_accounts.add(to_account)
    graph[from_account].append(to_account)
    
while True:
    line = input().strip()
    if line == "#":
        break
    
    parts = line.split()
    query = parts[0]
    
    if query == "?number_transactions":
        print(total_transactions)
    elif query == "?total_money_transaction":
        print(total_money_transaction)
    elif query == "?list_sorted_accounts":
        print(" ".join(sorted(unique_accounts)))
    elif query == "?total_money_transaction_from":
        transaction_from_account = parts[1]
        print(from_transactions[transaction_from_account])
    elif query == "?inspect_cycle":
        inspect_cycle_account = parts[1]
        k = int(parts[2])
        
        visited = set()
        has_cycle = has_cycle_of_length_k(inspect_cycle_account, inspect_cycle_account, k, 0, visited)
        print(1 if has_cycle else 0)
