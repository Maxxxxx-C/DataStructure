
# 第二章 分治法

## 1.1 整体思想

### 1.1.1 分治法的三步骤

1. **分解**：将大的问题规模分解成1个或更多的小的子问题
2. **递归**：递归地解决所有子问题
3. **合并**：合并所有子问题

> 虽然分治法是递归的，但并不意味着实际代码的实现必须使用递归

### 1.1.2 复习归并排序

1. 将数组分成左半部分和右半部分；
2. 递归地排序左半部分和右半部分；
3. 合并两个子数组

归并排序的时间复杂度的递归表达式为 $$T(n)=2T(n/2)+\Theta(n)$$

其中，$n/2$ 是子问题的规模，$T(n/2)$ 是子问题所需要的时间，其系数 $2$ 是子问题的数量，$\Theta(n)$ 是分解步骤和合并步骤所需要的时间

依靠主方法，得出 $$T(n)=\Theta(n\log n)$$

### 1.1.3 二分查找

二分查找算法应用于在一个已排序的序列中找到元素 $x$

1. 将x于序列中间的元素相比较，若x更小，则子序列为左半序列，反之为右半序列（分解）
2. 递归地在子序列中二分查找x（递归）
3. 无

二分查找的特点是，子问题的数目只有1个，我们只需要讨论有x的子序列，而不需要讨论另一个。并且由于子序列只有一个，所以无需合并

因此二分查找的时间复杂度的递归表达式为 $$T(n)=T(n/2)+\Theta(1)$$

易得 $$T(n)=\Theta(\log n)$$

**[递归型二分查找C语言实现](./binary_search.c)**

```c
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
```

### 1.1.4 乘方问题

给一个有理数 $x$，和一个非负整数 $n$，求 $x^n$

1. 当 $n$ 为偶数时，$x^n=x^{n/2}x^{n/2}$，当 $n$ 为奇数时，$x^n=x^{(n-1)/2}x^{(n-1)/2}x$，我们只需求1次 $x^{n/2}$ 或者 $x^{(n-1)/2}$，即分解成了1个子乘方问题
2. 递归地解决子乘方问题
3. 当 $n$ 为偶数时，求1次乘法，当 $n$ 为奇数时，求2次乘法

归并排序的时间复杂度的递归表达式为 $$T(n)=T(n/2)+\Theta(1)$$

易得 $$T(n)=\Theta(\log n)$$

**[乘方分治法C语言实现](./power.c)**

```c
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
```

## 1.2 斐波那契数列 (Fibonacci sequence)

### 1.2.1 斐波那契数列的直观递归

斐波那契数列的数学定义就是递归的

`催更mathjax3扩展作者快快更新大括号的渲染`

![公式](https://latex.codecogs.com/svg.image?F(n)=\left\\{\begin{array}{l}0,\&space;n=0&space;\\\\1,\&space;n=1&space;\\\\F(n-1)&plus;F(n-2),\&space;n\geqslant2\end{array}\right.)

我们可以非常简单地从数学定义中得出递归表达式 $$T(n)=T(n-1)+T(n-2)+\Theta(1)$$

这个结果是指数级的，$$T(n)=\Omega((\frac{1+\sqrt{5}}{2})^n)$$

我们发现，此时使用分治法的效果似乎并不太行儿，原因是我们在分解的步骤中，两个子问题的子问题出现了重复，导致我们做了大量的非必要重复计算。分治法的精髓在于减小问题的规模，而我们在这里却增大了问题的规模。

**[糟糕的斐波那契数列算法](./poor_fibonacci.c)**

```c
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
```

`我们想要多项式时间的算法。`

### 1.2.2 更好的算法——自下而上的解法

依次计算 $F(0)$, $F(1)$, $F(2)$...分别用两个变量缓存 $F(k-1)$ 和 $F(k)$，并相加得出 $F(k+1)$，再将 $F(k)$ 和 $F(k+1)$ 缓存到下一次的 $F(k-1)$ 和 $F(k)$，直到计算出 $F(n)$

`动态规划的思想`

显然，我们需要 $n-1$ 次加法和 $2(n-2)$ 次赋值运算

因此这个算法的时间消耗为 $$T(n)=\Theta(n)$$

**[自下而上的斐波那契数列算法](./dynamic_fibonacci.c)**

```c
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
```

### 1.2.3 最快的算法——朴素平方递归式（计算机难以实现）

斐波那契数列的一个重要结论

$$F(n)=\left \lfloor \frac{\varphi ^n}{\sqrt{5} }  +\frac{1}{2} \right \rfloor $$

$\left \lfloor \frac{\varphi ^n}{\sqrt{5} }  +\frac{1}{2} \right \rfloor $ 的意思是最接近 $\frac{\varphi ^n}{\sqrt{5}}$ 的整数

乘方递归的时间消耗为 $\Theta(\log n)$

但是由于计算机在运算高精度数据过程中总是会丢失一些位，因此这个算法在计算机中难以实现，并且事实上，计算高精度浮点数的乘法并不是常数级的，因此实际计算的时间消耗总是要更久。

### 1.2.4 另辟蹊径——矩阵平方递归式

**定理一** $$\begin{bmatrix}F(n+1)&F(n)\\\\ F(n)&F(n-1)\end{bmatrix}=\begin{bmatrix}1&1\\\\1&0\end{bmatrix}^n$$

乘方递归的时间消耗为 $\Theta(\log n)$

---

**数学归纳法**证明

当 $n=1$ 时，$$\begin{bmatrix}F(2)&F(1)\\\\ F(1)&F(0)\end{bmatrix}=\begin{bmatrix}1&1\\\\1&0\end{bmatrix}^1$$显然成立

假设 $$\begin{bmatrix}F(k+1)&F(k)\\\\ F(k)&F(k-1)\end{bmatrix}=\begin{bmatrix}1&1\\\\1&0\end{bmatrix}^k$$成立

则对于 $k+1$ $$\begin{bmatrix}F(k+2)&F(k+1)\\\\ F(k+1)&F(k)\end{bmatrix}=\begin{bmatrix}1&1\\\\1&0\end{bmatrix}^{k+1}$$

$$=\begin{bmatrix}F(k+1)&F(k)\\\\ F(k)&F(k-1)\end{bmatrix}\begin{bmatrix}1&1\\\\1&0\end{bmatrix}=\begin{bmatrix}F(k+1)+F(k)&F(k+1)\\\\ F(k)+F(k-1)&F(k)\end{bmatrix}$$

显然成立

因此 $$\begin{bmatrix}F(n+1)&F(n)\\\\ F(n)&F(n-1)\end{bmatrix}=\begin{bmatrix}1&1\\\\1&0\end{bmatrix}^n$$ 成立

---

两个 $2\times 2$ 的矩阵的乘法只需要 $12$ 次计算，是常数级的，因此整个算法的时间消耗为

$$T(n)=\Theta(\log n)$$

**[使用矩阵乘方的斐波那契数列算法](./matrix_power_fibonacci.c)**

```c
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
```

```c
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
```

```c
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
```

那对于一般的矩阵乘法，时间消耗还是常数级的吗？

## 1.3 矩阵乘法
