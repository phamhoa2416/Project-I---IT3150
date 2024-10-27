#include <stdio.h>
#include <stdlib.h>

void generate_permutation(int* permutation, int* elements, int* positions, int size, int index) {
    if (index == size) {
        for (int i = 0; i < size; ++i) {
            printf("%d ", permutation[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < size; ++i) {
            if (positions[i])
                continue;
        
        positions[i] = 1;
        permutation[index] = elements[i];
        
        generate_permutation(permutation, elements, positions, size, index + 1);
        
        permutation[index] = 0;
        positions[i] = 0;
        }
    }
}

int main() {
    int size, num;
    scanf("%d", &size);
    
    int *permutation = (int*)malloc(size * sizeof(int));
    int *elements = (int*)malloc(size * sizeof(int));
    int *positions = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; ++i) { 
        elements[i] = i + 1;
        positions[i] = 0;
    }
    
    generate_permutation(permutation, elements, positions, size, 0);
    
    free(permutation);
    free(elements);
    free(positions);
    
    return 0;
}
