/*
 * 糟糕的斐波那契数列算法
 * */

#include "stdio.h"

long poor_fibonacci(int n) {
    long result = 0;
    if (n != 0 && n != 1) {
        result = poor_fibonacci(n - 1) + poor_fibonacci(n - 2);
    } else if (n == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

static void test() {
    printf("%d\n", poor_fibonacci(5));
    printf("%d\n", poor_fibonacci(23));
    printf("%d\n", poor_fibonacci(156));
}

//int main() {
//    test();
//    return 0;
//}