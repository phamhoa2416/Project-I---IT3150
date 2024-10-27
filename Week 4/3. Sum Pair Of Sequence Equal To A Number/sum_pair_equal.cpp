#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int countTwoSum(vector<int> sequence, int target) {
    int length = sequence.size();
    
    int count = 0;
    unordered_set<int> numberSet;
    
    for (int i = 0; i < length; ++i) {
        if (numberSet.find(target - sequence[i]) != numberSet.end()) {
            count++;
        } else numberSet.insert(sequence[i]);
    }
    
    return count;
}

int main() {
    int size, target;
    cin >> size >> target;
    
    vector<int> sequence(size);
    for (int i = 0; i < size; ++i) {
        int value;
        cin >> value;
        sequence[i] = value;
    }
    
    cout << countTwoSum(sequence, target);
    return 0;
}
