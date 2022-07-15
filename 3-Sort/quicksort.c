/*
 * 插入排序(Quicksort)
 * */

#include "stdio.h"

typedef double DataType;

void quicksort(DataType array[], int s, int e);

int partition(DataType array[], int s, int e);

//改变原数组，参数：array（原数组），s（start），e（end）
void quicksort(DataType array[], int s, int e) {
    if (s < e) {
        int m = partition(array, s, e);
        quicksort(array, s, m - 1);
        quicksort(array, m + 1, e);
    }
}

// 选择第一个元素为主元，将小于等于主元的放到主元左边，其余放到右边
int partition(DataType array[], int s, int e) {
    DataType key = array[s];
    int i = s;
    DataType tmp;
    int j;
    for (j = i + 1; j <= e; j++) {
        if (array[j] <= key) {
            tmp = array[j];
            array[j] = array[i + 1];
            array[i + 1] = tmp;
            i++;
        }
    }
    tmp = array[s];
    array[s] = array[i];
    array[i] = tmp;
    return i;
}

static void test() {
    DataType test_array[50] = {-36.369, 85.803, -167.095, -110.182, 76.797, 196.661, 111.586, -162.629, -186.281,
                               -99.451, 23.562, -175.460, -30.084, 66.448, -99.617, 188.470, -85.186, 17.844, 189.978,
                               -154.840, 45.021, -134.597, 144.222, -15.050, -93.513, 134.867, -73.930, 137.829,
                               -112.125, 178.082, 192.470, -158.801, 69.293, 69.950, 37.793, 28.266, 12.389, -141.038,
                               15.295, 68.120, -8.053, 134.254, -101.804, 80.599, -93.530, -49.859, -109.548, -96.868,
                               87.334, -100.866};
    quicksort(test_array, 0, 49);

    int i;
    for (i = 0; i < 50; i++) {
        if (i != 0 && i % 10 == 0) {
            printf("\n");
        }
        printf("%.3f, ", test_array[i]);
    }
}

int main() {
    test();
    return 0;
}