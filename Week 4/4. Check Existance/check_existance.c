#include <stdio.h>
#include <stdlib.h>

int binarySearch(int sequece[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sequece[mid] == target) {
            return 1; 
        } else if (sequece[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0; 
}

void insertSorted(int sequence[], int *size, int target) {
    int i;
    for (i = *size - 1; (i >= 0 && sequence[i] > target); i--) {
        sequence[i + 1] = sequence[i];
    }
    sequence[i + 1] = target;
    (*size)++;
}

int main() {
    int size;
    scanf("%d", &size);

    int *sequence = (int*)malloc(size * sizeof(int));
    int *visited = (int*)malloc(size * sizeof(int));  
    int visited_size = 0;  

    for (int i = 0; i < size; i++) {
        scanf("%d", &sequence[i]);

        if (binarySearch(visited, visited_size, sequence[i])) {
            printf("1\n");
        } else {
            printf("0\n");
            insertSorted(visited, &visited_size, sequence[i]);  
        }
    }

    return 0;
}
