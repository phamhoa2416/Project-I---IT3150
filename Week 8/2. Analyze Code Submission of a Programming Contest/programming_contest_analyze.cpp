#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int time_to_seconds(string timestamp)
{
    int hour, minute, second;
    sscanf(timestamp.c_str(), "%d:%d:%d", &hour, &minute, &second);
    return hour * 60 * 60 + minute * 60 + second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int total_submissions = 0;
    int error_submissions = 0;
    unordered_map<string, int> error_submissions_user;
    unordered_map<string, unordered_map<string, int>> total_point_of_user;
    vector<int> submission_time;

    string line;

    while(getline(cin, line) && line != "#") {
        stringstream ss(line);
        string user_id, problem_id, time_point, status;
        int point;

        ss >> user_id >> problem_id >> time_point >> status >> point;

        total_submissions++;
        if (status == "ERR") {
            error_submissions_user[user_id]++;
            error_submissions++;
        }    

        if (status == "OK")
            total_point_of_user[user_id][problem_id] = max(total_point_of_user[user_id][problem_id], point);
        
        submission_time.push_back(time_to_seconds(time_point));
    }
    
    sort(submission_time.begin(), submission_time.end());

    while (getline(cin, line) && line != "#") {
        stringstream ss(line); 
        string query;
        ss >> query;

        if (query == "?total_number_submissions")
            cout << total_submissions << endl;
        else if (query == "?number_error_submision")
            cout << error_submissions << endl;
        else if (query == "?number_error_submision_of_user") {
            string user_id;
            ss >> user_id;
            cout << error_submissions_user[user_id] << endl;
        } else if (query == "?total_point_of_user") {
            string user_id;
            ss >> user_id;
            int total_point = 0;
            for (const auto& [problem_id, point]: total_point_of_user[user_id]) {
                total_point += point;
            }
            cout << total_point << endl;
        } else if (query == "?number_submission_period") {
            string start_time, end_time;
            ss >> start_time >> end_time;

            int start_time_seconds = time_to_seconds(start_time);
            int end_time_seconds = time_to_seconds(end_time);

            auto lower = lower_bound(submission_time.begin(), submission_time.end(), start_time_seconds);
            auto upper = upper_bound(submission_time.begin(), submission_time.end(), end_time_seconds);
            cout << upper - lower << endl;
        }
    }
}