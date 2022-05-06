/*
 * 动态规划的思想——斐波那契数列算法
 * */

#include "stdio.h"

//动态规划的思想，自上而下地求出斐波那契数
long dynamic_fibonacci(int n) {
    long result = 1;
    if (n != 0 && n != 1) {
        int key;
        long tmp;
        long pre_pre_number = 0;
        long pre_number = 1;

        for (key = 1; key != n; key++) {
            result = pre_number + pre_pre_number;

            tmp = result;
            pre_pre_number = pre_number;
            pre_number = tmp;
        }
    } else if (n == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

static void test() {
    printf("%d\n", dynamic_fibonacci(5));
    printf("%d\n", dynamic_fibonacci(17));
    printf("%d\n", dynamic_fibonacci(31));
}

//int main() {
//    test();
//    return 0;
//}