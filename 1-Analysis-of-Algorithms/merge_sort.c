/*
 * 归并排序(Merge Sort)
 * */

#include "stdio.h"
#include "stdlib.h"

typedef double DataType;

DataType *merge_sort(const DataType *array, int length);

DataType *merge(const DataType *array1, const DataType *array2, int length);

//归并排序一个数组，不破坏原数组，返回新数组
DataType *merge_sort(const DataType *array, int length) {
    int i;
    //复制一份，防止破坏原数组
    DataType *array_copy = (DataType *) malloc(length * sizeof(DataType));
    for (i = 0; i < length; i++) {
        array_copy[i] = array[i];
    }
    //如果长度为1，说明达到终止条件，直接返回复制后的数组
    if (length == 1) {
        return array_copy;
    } else {    //递归主程序
        int mid = length / 2;
        //将原数组分割成array1和array2
        DataType *array1 = (DataType *) malloc(mid * sizeof(DataType));
        DataType *array2 = (DataType *) malloc((length - mid) * sizeof(DataType));
        for (i = 0; i < mid; i++) {
            array1[i] = array_copy[i];
        }
        for (i = mid; i < length; i++) {
            array2[i - mid] = array_copy[i];
        }
        //对array1和array2进行分治排序（递归）
        array1 = merge_sort(array1, mid);
        array2 = merge_sort(array2, length - mid);
        //有序合并两个数组
        array_copy = merge(array1, array2, length);
        //释放内存，节省空间
        free(array1);
        free(array2);
        return array_copy;
    }
}

//有序合并两个数组
DataType *merge(const DataType *array1, const DataType *array2, int length) {
    DataType *array_merged = (DataType *) malloc(length * sizeof(DataType));
    int pointer1 = 0, pointer2 = 0; //标志
    int length1 = length / 2;       //数组1的长度
    int length2 = length - length1; //数组2的长度
    int i;
    for (i = 0; i < length; i++) {
        //两个数组的标志都为达到尽头
        if (pointer1 != length1 && pointer2 != length2) {
            if (array1[pointer1] <= array2[pointer2]) {
                array_merged[i] = array1[pointer1];
                pointer1++;
            } else {
                array_merged[i] = array2[pointer2];
                pointer2++;
            }
        }   //数组1到达尽头，则将数组2剩下部分加到最终数组的后面
        else if (pointer1 == length1) {
            array_merged[i] = array2[pointer2];
            pointer2++;
        }   //数组2到达尽头，则将数组1剩下部分加到最终数组的后面
        else if (pointer2 == length2) {
            array_merged[i] = array1[pointer1];
            pointer1++;
        }
    }
    return array_merged;
}

static void test() {
    DataType test_array[10] = {5.4, -6.39, 8.65, 1.45, 63.9, 0.123, -5.269};
    DataType *new_array = (DataType *) malloc(10 * sizeof(DataType));
    new_array = merge_sort(test_array, 7);

    int i;
    for (i = 0; i < 7; i++) {
        printf("%.3f, ", new_array[i]);
    }

    free(new_array);
}

//int main() {
//    test();
//    return 0;
//}
