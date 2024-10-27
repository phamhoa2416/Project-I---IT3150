#include <stdio.h>
#include <stdlib.h>

void merge(int sequence[], int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;
    
    int* left_sequence = (int*)malloc(left_size * sizeof(int));
    int* right_sequence = (int*)malloc(right_size * sizeof(int));
    
    for (int i = 0; i < left_size; ++i) 
        left_sequence[i] = sequence[left + i];
    
    for (int j = 0; j < right_size; ++j) 
        right_sequence[j] = sequence[mid + 1 + j];
        
    int i = 0, j = 0, k = left;
    while (i < left_size && j <right_size) {
        if (left_sequence[i] < right_sequence[j]) {
            sequence[k] = left_sequence[i];
            i++;
        } else {
            sequence[k] = right_sequence[j];
            j++;
        }
        k++;
    }
    
    while (i < left_size) {
        sequence[k] = left_sequence[i];
        i++; k++;
    }
    
    while (j < right_size) {
        sequence[k] = right_sequence[j];
        j++; k++;
    }
}

void merge_sort(int sequence[], int left, int right) {
    if (left < right) {
        int mid = (right - left) / 2 + left;
        
        merge_sort(sequence, left, mid);
        merge_sort(sequence, mid + 1, right);
        
        merge(sequence, left, mid, right);
    }
}

int countTwoSum(int sequence[], int size, int target) {
    int left = 0, right = size - 1, temp = 0;
    int count = 0;
    
    while (left < right) {
        temp = sequence[right] + sequence[left];
        if (temp == target) 
            count++;
        
        if (temp < target) 
            left++;
        else right--;
        
    }
    return count;
}

int main() {
    int size, target;
    scanf("%d%d", &size, &target);
    
    int* sequence = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; ++i) {
        int value;
        scanf("%d", &value);
        sequence[i] = value;
    }
    
    merge_sort(sequence, 0, size - 1);
    
    printf("%d", countTwoSum(sequence, size, target));
    
    return 0;
}
