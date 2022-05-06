/*
 * 乘方分治算法
 * */

#include "stdio.h"

typedef double DataType;


//分治法求乘方
DataType recursive_pow(DataType base, int power) {
    DataType medium;
    DataType result = base;
    if (power != 1) {
        if (power % 2 == 0) {
            medium = recursive_pow(base, power / 2);
            result = medium * medium;
        } else if (power % 2 == 1) {
            medium = recursive_pow(base, (power - 1) / 2);
            result = medium * medium * base;
        }
    }
    return result;
}

static void test(){
    printf("%.16f", recursive_pow(3.1, 7));
}

//int main(){
//    test();
//    return 0;
//}