/*
 * 二分查找(Binary Search)
 * */

#include "stdio.h"

typedef double DataType;

//二分查找一个数在序列中的位置，存在则返回该元素的下标，如果不存在返回-1
int binary_search(DataType array[], int start, int end, DataType value) {
    int key = -1;
    int length = end - start + 1;
    int mid = (end + start) / 2;
    //长度为2时表示剩余只有两个元素，两边一定都找过了，递归结束，该数并不在序列中
    if(length != 2){
        if (value == array[mid]) {
            key = mid;
        } else if (value < array[mid]) {
            key = binary_search(array, start, mid, value);
        } else if (value > array[mid]) {
            key = binary_search(array, mid, end, value);
        }
    }
    return key;
}

static void test() {
    DataType test_array[20] = {-9, -5, 1, 2, 7, 24, 25, 87, 693};
    int key1 = binary_search(test_array, 0, 8, 24);
    int key2 = binary_search(test_array, 0, 8, 37);
    printf("%d\n", key1);
    printf("%d\n", key2);
}

//int main() {
//    test();
//    return 0;
//}