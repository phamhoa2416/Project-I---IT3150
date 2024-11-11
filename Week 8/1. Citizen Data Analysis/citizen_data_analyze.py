from collections import defaultdict, deque
from bisect import bisect_left
from bisect import bisect_right
import sys

citizens = {}
date_of_birth_citizens = defaultdict(list)
date_of_birth_count = defaultdict(int)
prefix_sum = {}   
ancestor_cache = {}  
adjacency_list = defaultdict(list)
visited = {}
dp = {}

def compute_prefix_sum():
    cumulative_count = 0
    for date, count in sorted(date_of_birth_count.items()):
        cumulative_count += count
        prefix_sum[date] = cumulative_count

def build_graph():
    for person_code, citizen in citizens.items():
        if citizen['father_code'] != "0000000":
            adjacency_list[person_code].append(citizen['father_code'])
            adjacency_list[citizen['father_code']].append(person_code)
        if citizen['mother_code'] != "0000000":
            adjacency_list[person_code].append(citizen['mother_code'])
            adjacency_list[citizen['mother_code']].append(person_code)
            
def dfs(person_code):
    visited[person_code] = True
    include = 1
    exclude = 0

    for neighbor in adjacency_list[person_code]:
        if not visited.get(neighbor, False):
            child_include = dfs(neighbor)
            child_exclude = dp[neighbor][0]
            include += child_exclude
            exclude += max(child_include, child_exclude)

    dp[person_code] = (exclude, include)
    return dp[person_code][1]     

def number_of_people_born_between(from_date, to_date):
    if not prefix_sum:
        compute_prefix_sum()
        
    from_date_index = bisect_left(sorted(prefix_sum.keys()), from_date)
    to_date_index = bisect_right(sorted(prefix_sum.keys()), to_date)
    
    if from_date_index == len(prefix_sum):
        return 0
    
    if to_date_index == 0:
        return 0
    
    to_count = prefix_sum[sorted(prefix_sum.keys())[to_date_index - 1]]
    from_count = prefix_sum[sorted(prefix_sum.keys())[from_date_index - 1]] if from_date_index > 0 else 0
    
    return to_count - from_count
    

def max_unrelated_people():
    build_graph()
    max_unrelated = 0

    for person_code in citizens:
        if not visited.get(person_code, False):
            dfs(person_code)
            max_unrelated += max(dp[person_code])

    return max_unrelated

def most_alive_ancestor(person_code):
    if person_code in ancestor_cache:
        return ancestor_cache[person_code]
    
    queue = deque([(person_code, 0)])
    visited_local = set()
    max_distance = 0
    
    while queue:
        person, distance = queue.popleft()
        if person in visited_local:
            continue
        visited_local.add(person)
        
        max_distance = max(max_distance, distance)
        citizen = citizens[person]
        
        if citizen["father_code"] != "0000000":
            queue.append((citizen["father_code"], distance + 1))
        if citizen["mother_code"] != "0000000":
            queue.append((citizen["mother_code"], distance + 1))
            
    ancestor_cache[person_code] = max_distance
    return max_distance
    
if __name__ == "__main__":
    total_citizens = 0
   
    for line in sys.stdin:
        line = line.strip()
        if line == "*":
            break
        
        person_code, date_of_birth, father_code, mother_code, is_alive, region_code = line.split()
        
        citizens[person_code] = {
            "person_code": person_code,
            "date_of_birth": date_of_birth,
            "father_code": father_code,
            "mother_code": mother_code,
            "is_alive": is_alive,
            "region_code": region_code
        }
        
        total_citizens += 1
        date_of_birth_citizens[date_of_birth].append(person_code)
        date_of_birth_count[date_of_birth] += 1
        
    for line in sys.stdin:
        line = line.strip()
        if line == "***":
            break
        
        parts = line.split()
        query = parts[0]
        
        if query == "NUMBER_PEOPLE":
            print(total_citizens)
        elif query == "NUMBER_PEOPLE_BORN_AT":
            date = parts[1]
            print(len(date_of_birth_citizens[date]))
        elif query == "NUMBER_PEOPLE_BORN_BETWEEN":
            from_date, to_date = parts[1], parts[2]
            print(number_of_people_born_between(from_date, to_date))
        elif query == "MOST_ALIVE_ANCESTOR":
            person_code = parts[1]
            print(most_alive_ancestor(person_code))
        elif query == "MAX_UNRELATED_PEOPLE":
            print(max_unrelated_people())
            