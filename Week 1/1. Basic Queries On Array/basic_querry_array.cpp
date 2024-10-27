#include <iostream>
#include <vector>

using namespace std;

int findMax(const vector<int>& sequence) {
    int max_value = INT_MIN;
    for (int num : sequence) max_value = max_value > num ? max_value : num;
    return max_value;
}

int findMin(const vector<int>& sequence) {
    int min_value = INT_MAX;
    for (int num : sequence) min_value = min_value < num ? min_value : num;
    return min_value;
}

int sumOfAllElements(const vector<int>& sequence) {
    int sum = 0;
    for (int num : sequence) sum += num;
    return sum;
}

int findMaxSegement(const vector<int>& sequence, int i, int j) {
    int max_value = sequence[i - 1];
    for (int k = i - 1; k < j; ++k) {
        if (sequence[k] > max_value) 
            max_value = sequence[k];
    }
    return max_value;
}

int main() 
{ 
    int size, value;
    cin >> size;
    
    vector<int> sequence;
    for (int i = 0; i < size; ++i) {
        cin >> value;
        sequence.push_back(value);
    }
    
    string command;
    while (cin >> command) {
        if (command == "***") {
            break;
        } 
        
        if (command == "find-max") {
            cout << findMax(sequence) << endl;
        } else if (command == "find-min") {
            cout << findMin(sequence) << endl;
        } else if (command == "sum") {
            cout << sumOfAllElements(sequence) << endl;
        } else if (command == "find-max-segment") {
            int i, j;
            cin >> i >> j;
            cout << findMaxSegement(sequence, i, j) << endl;
        }
    }
    
    return 0;
}
