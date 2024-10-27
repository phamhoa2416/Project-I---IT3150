#include <iostream>
#include <set>

using namespace std;

int main() {
    int size;
    cin >> size;
    
    int* sequence = new int[size];
    set<int> visited;
    
    for (int i = 0; i < size; ++i) {
        cin >> sequence[i];
        
        if (visited.find(sequence[i]) != visited.end()) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
            visited.insert(sequence[i]);
        }
    }
    
    return 0;
}
