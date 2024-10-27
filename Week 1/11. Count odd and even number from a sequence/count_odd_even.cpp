#include <iostream>

using namespace std;

int main() 
{ 
    int number;
    cin >> number;
    
    int countOdd = 0;
    int countEven = 0;
    
    for (int i = 0; i < number; ++i) {
        int value;
        cin >> value;
        if (value % 2 == 0) countEven++;
        else countOdd++;
    }
    
    cout << countOdd << " " << countEven;
    return 0;
}
