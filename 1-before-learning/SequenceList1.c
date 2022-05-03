#include "stdio.h"

#define MaxSize 10

typedef struct {
    int data[MaxSize];     //静态数组存放数据元素
    int length;
} SqList;

//初始化一个顺序表
void InitList(SqList *L) {
    int i = 0;
    for (i = 0; i < MaxSize; ++i) {
        L->data[i] = 0;
    }
    L->length = 0;
}

int main() {
    SqList L;
    InitList(&L);
    return 0;
}
