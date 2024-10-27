#include <stdio.h> 
#include <stdlib.h>

void generateBinarySequence(int size, int* sequence, int index) {
    if (index == size) {
        for (int i = 0; i < size; ++i) {
            printf("%d", *(sequence + i));
        }
        printf("\n");
        return;
    }
    
    *(sequence + index) = 0;
    generateBinarySequence(size, sequence, index + 1);
    
    *(sequence + index) = 1;
    generateBinarySequence(size, sequence, index + 1);
}

int main() 
{ 
    int size;
    scanf("%d", &size);
    
    int* sequence = (int*)malloc(size * sizeof(int));
    generateBinarySequence(size, sequence, 0);
}
