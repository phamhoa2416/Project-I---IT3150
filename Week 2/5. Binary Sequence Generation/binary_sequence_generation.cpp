#include <iostream>
#include <vector>

using namespace std;

void generateBinarySequence(int size, vector<int> sequence, int index) {
    if (index == size) {
        for (int i = 0; i < size; ++i) {
            cout << sequence[i];
        }
        cout << endl;
        return;
    }
    
    sequence[index] = 0;
    generateBinarySequence(size, sequence, index + 1);
    
    sequence[index] = 1;
    generateBinarySequence(size, sequence, index + 1);
}

int main() 
{ 
    int size;
    cin >> size;
    
    vector<int> sequence(size);
    generateBinarySequence(size, sequence, 0);
    return 0;
}
