import sys
import bisect

def time_to_seconds(time_point):
    hour, minute, second = map(int, time_point.split(':'))
    return hour * 3600 + minute * 60 + second

if __name__ == "__main__":
    total_submissions = 0
    error_submissions = 0
    error_submissions_user = {}
    total_point_of_user = {}
    submission_time = []
    
    for line in sys.stdin:
        line = line.strip()
        if line == "#":
            break
        
        user_id, problem_id, time_point, status, point = line.split(" ")
        point = int(point)
        
        total_submissions += 1
        
        if status == "ERR":
            error_submissions += 1
            error_submissions_user[user_id] = error_submissions_user.get(user_id, 0) + 1
            
        if status == "OK":
            if user_id not in total_point_of_user:
                total_point_of_user[user_id] = {}
            total_point_of_user[user_id][problem_id] = max(total_point_of_user[user_id].get(problem_id, 0), point)
            
        submission_time.append(time_to_seconds(time_point)) 
        
    submission_time.sort()
    
    for line in sys.stdin:
        line = line.strip()
        if line == "#":
            break
        
        parts = line.split()
        query = parts[0]
        
        if query == "?total_number_submissions":
            print(total_submissions)
        elif query == "?number_error_submision":
            print(error_submissions)
        elif query == "?number_error_submision_of_user":
            user_id = parts[1]
            if user_id in error_submissions_user:
                print(error_submissions_user[user_id])
            else:
                print(0)
        elif query == "?total_point_of_user":
            user_id = parts[1]
            if user_id in total_point_of_user:
                print(sum(total_point_of_user[user_id].values()))
            else:
                print(0)
        elif query == "?number_submission_period":
            start_time, end_time = parts[1], parts[2]
            
            start_time_seconds = time_to_seconds(start_time)
            end_time_seconds = time_to_seconds(end_time)
            
            lower = bisect.bisect_left(submission_time, start_time_seconds)
            upper = bisect.bisect_right(submission_time, end_time_seconds)
            print(upper - lower)