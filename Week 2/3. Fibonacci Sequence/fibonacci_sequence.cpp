#include <iostream>

using namespace std;

int fibonacci(int n) {
    if (n == 0) return 0;
    else if (n <= 2) return 1;
    else return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() 
{ 
    int num;
    cin >> num;
    cout << fibonacci(num - 1);
}
