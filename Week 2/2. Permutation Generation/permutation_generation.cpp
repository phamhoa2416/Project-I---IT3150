#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool nextPermutation(vector<int> &sequence) {
    int length = sequence.size();
    
    int pivot = -1;
    for (int i = length - 2; i >= 0; --i) {
        if (sequence[i] < sequence[i + 1]) {
            pivot = i;
            break;
        }
    }
    
    if (pivot == -1) {
        reverse(sequence.begin(), sequence.end());
        return false;
    }
    
    for (int i = length - 1; i > pivot; i--) {
        if (sequence[i] > sequence[pivot]) {
            swap(sequence[i], sequence[pivot]);
            break;
        }
    }
    
    reverse(sequence.begin() + pivot + 1, sequence.end());
    return true;
}

void permutationGeneration(vector<int> &sequence) {
    sort(sequence.begin(), sequence.end());
    do {
        for (int i = 0; i < sequence.size(); ++i) {
            cout << sequence[i] << " ";
        }
        cout << endl;
    } while (nextPermutation(sequence));
}

int main() {
    int size;
    cin >> size;
    
    vector<int> sequence(size);
    for (int i = 0; i < size; ++i) {
        sequence[i] = i + 1;
    }
    
    permutationGeneration(sequence);
    
    return 0;
}
