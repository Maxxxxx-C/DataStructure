/*
 * 计数排序(Counting Sort)
 * */

#include "stdio.h"
#include "stdlib.h"

int *counting_sort(const int array[], int length, int max) {
    int i;
    int *side_array = (int *) malloc((max + 1) * sizeof(int));
    int *sorted_array = (int *) malloc(length * sizeof(int));
    for (i = 0; i < (max + 1); i++) {
        side_array[i] = 0;
    }
    for (i = 0; i < length; i++) {
        side_array[array[i]]++;
    }
    for (i = 1; i < (max + 1); i++) {
        side_array[i] += side_array[i - 1];
    }
    for (i = length - 1; i >= 0; i--){
        sorted_array[side_array[array[i]] - 1] = array[i];
        side_array[array[i]]--;
    }
    return sorted_array;
}

static void test() {
    int test_array[] = {4, 5, 1, 5, 8, 0, 11, 2, 4, 3, 8, 6, 9, 10};
    int *sorted_array = (int *) malloc(13 * sizeof(int));
    sorted_array = counting_sort(test_array, 14, 11);

    int i;
    for (i = 0; i < 14; i++) {
        printf("%d, ", sorted_array[i]);
    }
}

int main() {
    test();
    return 0;
}