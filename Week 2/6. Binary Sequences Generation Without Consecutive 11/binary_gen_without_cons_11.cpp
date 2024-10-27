#include <iostream> 

using namespace std; 

void generateSequence(int size, string sequence = "", char prev = '0') {
    if (sequence.length() == size) {
        cout << sequence << endl;
        return;
    }
    
    generateSequence(size, sequence + '0', '0');
    
    if (prev != '1') {
        generateSequence(size, sequence + '1', '1');
    }
}

int main() 
{ 
    int size;
    cin >> size;
    
    string sequence = "";
    generateSequence(size, sequence, '0');
}
