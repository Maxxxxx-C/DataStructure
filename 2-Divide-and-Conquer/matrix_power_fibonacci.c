/*
 * 矩阵乘方递归式
 * */

#include "stdio.h"
#include "stdlib.h"

long matrix_power_fibonacci(int n);

long **matrix_pow(long **base_matrix, int power);

long **two_by_two_matrix_multiple(long **matrix1, long **matrix2);

//利用斐波那契数列的矩阵表达式，二分地求出斐波那契数
long matrix_power_fibonacci(int n) {
    long **result_matrix = (long **) malloc(2 * sizeof(long *));
    int i;
    for (i = 0; i < 2; i++) {
        result_matrix[i] = (long *) malloc(2 * sizeof(long));
    }
    result_matrix[0][0] = 1;
    result_matrix[0][1] = 1;
    result_matrix[1][0] = 1;
    result_matrix[1][1] = 0;
    result_matrix = matrix_pow(result_matrix, n);
    return result_matrix[0][1];
}

//矩阵乘方
long **matrix_pow(long **base_matrix, int power){
    long **medium;
    long **result = base_matrix;
    if (power != 1) {
        if (power % 2 == 0) {
            medium = matrix_pow(base_matrix, power / 2);
            result = two_by_two_matrix_multiple(medium, medium);
        } else if (power % 2 == 1) {
            medium = matrix_pow(base_matrix, (power - 1) / 2);
            result = two_by_two_matrix_multiple(two_by_two_matrix_multiple(medium, medium), base_matrix);
        }
    }
    return result;
}

//2X2的矩阵乘法
long **two_by_two_matrix_multiple(long **matrix1, long **matrix2) {
    long **result = (long **) malloc(2 * sizeof(long *));
    int i;
    for (i = 0; i < 2; i++) {
        result[i] = (long *) malloc(2 * sizeof(long));
    }
    result[0][0] = matrix1[0][0] * matrix2[0][0] + matrix1[0][1] * matrix2[1][0];
    result[0][1] = matrix1[0][0] * matrix2[0][1] + matrix1[0][1] * matrix2[1][1];
    result[1][0] = matrix1[1][0] * matrix2[0][0] + matrix1[1][1] * matrix2[1][0];
    result[1][1] = matrix1[1][0] * matrix2[0][1] + matrix1[1][1] * matrix2[1][1];
    return result;
}

static void test() {
    printf("%d\n", matrix_power_fibonacci(5));
    printf("%d\n", matrix_power_fibonacci(17));
    printf("%d\n", matrix_power_fibonacci(31));
}

//int main() {
//    test();
//    return 0;
//}