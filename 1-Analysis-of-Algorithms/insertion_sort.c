/*
 * 插入排序(Insertion Sort)
 * */

#include "stdio.h"

typedef double DataType;

//插入排序一个数组，改变原数组
void insertion_sort(DataType *array, int length) {
    int i, j;
    DataType key;
    for (i = 1; i < length; i++) {
        //key记录当前要插入的值
        key = array[i];
        for (j = i; j > -1; j--) {
            //如果j为0或者前一位小于等于key，则将key插入到这一位
            if (j == 0 || array[j - 1] <= key) {
                array[j] = key;
                break;
            }   //如果前一位大于key，则将前一位往后移
            else if (array[j - 1] > key) {
                array[j] = array[j - 1];
            }
        }
    }
}

static void test() {
    DataType test_array[10] = {5.4, -6.39, 8.65, 1.45, 63.9, 0.123, -5.269};
    insertion_sort(test_array, 7);

    int i;
    for (i = 0; i < 7; i++) {
        printf("%.3f, ", test_array[i]);
    }
}

//int main() {
//    test();
//    return 0;
//}
