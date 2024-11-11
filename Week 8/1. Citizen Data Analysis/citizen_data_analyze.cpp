#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

struct Citizen {
    string person_code;
    string date_of_birth;
    string father_code;
    string mother_code;
    char is_alive;
    string region_code;
};

class Database {
private:
    unordered_map<string, Citizen> citizens;
    map<string, vector<string>> date_of_birth_citizens;
    map<string, int> date_of_birth_count;
    map<string, int> prefix_sum;
    unordered_map<string, int> ancestor_cache;
    unordered_map<string, vector<string>> adjacency_list;
    unordered_map<string, bool> visited;
    unordered_map<string, bool> in_dfs;
    unordered_map<string, pair<int, int>> dp;

    int date_to_int(const string& date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        return year * 10000 + month * 100 + day;
    }
    
    void build_graph() {
        for (const auto& [person_code, citizen]: citizens) {
            if (citizen.father_code != "0000000") {
                adjacency_list[person_code].push_back(citizen.father_code);
                adjacency_list[citizen.father_code].push_back(person_code);
            }
            if (citizen.mother_code != "0000000") {
                adjacency_list[person_code].push_back(citizen.mother_code);
                adjacency_list[citizen.father_code].push_back(person_code);
            }
        }
    }
    
    int dfs(const string& person_code) {
        if (in_dfs[person_code]) return dp[person_code].second;
        
        in_dfs[person_code] = true;
        visited[person_code] = true;
        int include = 1;
        int exclude = 0;
        
        for (const string& neighbor: adjacency_list[person_code]) {
            if (!visited[neighbor]) {
                int child_include = dfs(neighbor);
                int child_exclude = dp[neighbor].first;
                
                include += child_exclude; // including this node means we can not include the child;
                exclude += max(child_include, child_exclude); // excluding this node means taking the maximum of including or excluding the child
            }
        }
        
        dp[person_code] = {exclude, include};
        return dp[person_code].second;
    }
public:
    Database() {};

    void add_citizen(const string& line) {
        istringstream ss(line);
        string person_code, date_of_birth, father_code, mother_code, region_code;
        char is_alive;
        ss >> person_code >> date_of_birth >> father_code >> mother_code >> is_alive >> region_code;

        Citizen citizen({person_code, date_of_birth, father_code, mother_code, is_alive, region_code}); 
        citizens[person_code] = citizen;
        date_of_birth_citizens[date_of_birth].push_back(person_code);
        date_of_birth_count[date_of_birth]++;
    }

    void compute_prefix_sum() {
        int cumulative_count = 0;
        for (const auto& [date, count]: date_of_birth_count) {
            cumulative_count += count;
            prefix_sum[date] = cumulative_count;
        }
    }

    int total_citizens() {
        return citizens.size();
    }

    int number_of_people_born_at(const string& date) {
        if (date_of_birth_citizens.find(date) != date_of_birth_citizens.end()) {
            return date_of_birth_citizens[date].size();
        }
        return 0;
    }

    int number_of_people_born_between(const string& from_date, const string& to_date) {
        if (prefix_sum.empty()) {
            compute_prefix_sum();
        }

        auto from_it = prefix_sum.lower_bound(from_date);
        auto to_it = prefix_sum.upper_bound(to_date);

        if (from_it == prefix_sum.end()) return 0;
        if (to_it == prefix_sum.begin()) return 0;

        int to_count = prev(to_it)->second;
        int from_count = (from_it == prefix_sum.begin()) ? 0 : prev(from_it)->second;

        return to_count - from_count;
    }

    int most_alive_ancestor(const string& person_code) {
        if (ancestor_cache.find(person_code) != ancestor_cache.end()) {
            return ancestor_cache[person_code];
        }
        
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        q.push({person_code, 0});
        int max_distance = 0;
        
        while (!q.empty()) {
            auto [person, distance] = q.front();
            q.pop();
            
            if (visited.count(person)) continue;
            visited.insert(person);
            
            max_distance = max(distance, max_distance);
            const auto& citizen = citizens[person];
            
            if (citizen.father_code != "0000000")
                q.push({citizen.father_code, distance + 1});
            if (citizen.mother_code != "0000000")
                q.push({citizen.mother_code, distance + 1});
        }
        
        return ancestor_cache[person_code] = max_distance;
    }
    
    int max_unrelated_people() {
        build_graph();
        
        int max_unrelated = 0;
        
        for (const auto& [person_code, _]: citizens) {
            if (!visited[person_code]) {
                dfs(person_code);
                max_unrelated += max(dp[person_code].first, dp[person_code].second);
            }
        }
        
        return max_unrelated;
    }

    int execute_queries(const string& query) {
        istringstream ss(query);
        string command;
        ss >> command;

        if (command == "NUMBER_PEOPLE") {
            return total_citizens(); 
        } else if (command == "NUMBER_PEOPLE_BORN_AT") {
            string date;
            ss >> date;
            return number_of_people_born_at(date);
        } else if (command == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string from_date, to_date;
            ss >> from_date >> to_date;
            return number_of_people_born_between(from_date, to_date);
        } else if (command == "MOST_ALIVE_ANCESTOR") {
            string person_code;
            ss >> person_code;
            return most_alive_ancestor(person_code);
        } else if (command == "MAX_UNRELATED_PEOPLE") {
            return max_unrelated_people();
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    Database db = Database();

    string line;
    while (getline(cin, line) && line != "*") {
        db.add_citizen(line);
    }

    string query;
    while (getline(cin, line) && line != "***") {
        cout << db.execute_queries(line) << endl;
    }
}
