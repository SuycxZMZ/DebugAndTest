/// 这个程序包含两个计算斐波那契数列的函数：
/// 一个是递归版本（fibonacci），
/// 另一个是优化版本（fibonacci_optimized，使用动态规划）。
/// 在编译时，优化器可能会对递归版本进行尾调用优化，而对优化版本进行循环展开等优化。

#include <iostream>
#include <vector>

// 递归计算斐波那契数列
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 优化版本的斐波那契数列计算（使用动态规划）
int fibonacci_optimized(int n) {
    if (n <= 1) return n;
    std::vector<int> fib(n + 1);
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}

int main() {

    int n = 40;

    // 未优化的递归版本
    std::cout << "Fibonacci (" << n << ") = " << fibonacci(n) << " (递归版本)" << std::endl;

    // 优化版本
    std::cout << "Fibonacci (" << n << ") = " << fibonacci_optimized(n) << " (优化版本)" << std::endl;

    return 0;
}
