#include <stdio.h> 

int gcd(int a, int b) {
    if (a == 0) return b;
    else return gcd(b % a, a);
}

int min_value(int a, int b) {
    return (a < b) ? a : b;
}
int pourWater(int firstCap, int secondCap, int required) {
    int x = 0, y = 0;
    int steps = 0;
    while (x != required && y != required) {
        if (x == 0) x = firstCap;  
        else if (y == secondCap) y = 0;  
        else {
            int temp = min_value(secondCap - y, x);
            x -= temp;
            y += temp;
        }
        steps++;
    }
    return steps;
}

int main() 
{ 
    int firstCap, secondCap, required;
    scanf("%d %d %d", &firstCap, &secondCap, &required);
    
    if (required % gcd(firstCap, secondCap) != 0 || (required > firstCap && required > secondCap)) {
        printf("-1");
        return 0;
    }

    int result = min_value(pourWater(firstCap, secondCap, required), pourWater(secondCap, firstCap, required));
    printf("%d", result);
}
