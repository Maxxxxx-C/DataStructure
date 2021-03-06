/*
 * 插入排序(Insertion Sort)
 * */

#include "stdio.h"

typedef double DataType;

//插入排序一个数组，改变原数组
void insertion_sort(DataType array[], int length) {
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
    DataType test_array[50] = {-36.369, 85.803, -167.095, -110.182, 76.797, 196.661, 111.586, -162.629, -186.281,
                               -99.451, 23.562, -175.460, -30.084, 66.448, -99.617, 188.470, -85.186, 17.844, 189.978,
                               -154.840, 45.021, -134.597, 144.222, -15.050, -93.513, 134.867, -73.930, 137.829,
                               -112.125, 178.082, 192.470, -158.801, 69.293, 69.950, 37.793, 28.266, 12.389, -141.038,
                               15.295, 68.120, -8.053, 134.254, -101.804, 80.599, -93.530, -49.859, -109.548, -96.868,
                               87.334, -100.866};
    insertion_sort(test_array, 50);

    int i;
    for (i = 0; i < 50; i++) {
        if (i != 0 && i % 10 == 0) {
            printf("\n");
        }
        printf("%.3f, ", test_array[i]);
    }
}

//int main() {
//    test();
//    return 0;
//}
