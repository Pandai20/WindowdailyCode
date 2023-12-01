#include <iostream>

#include <cstdarg>
void exampleFunction() {
    // 局部静态变量
    static int count = 0;

    // 输出 count 的值
    std::cout << "Count: " << count << std::endl;

    // 将 count 值递增
    count++;
}

int main() {
    // 多次调用 exampleFunction
    exampleFunction();
    exampleFunction();
    exampleFunction();

    return 0;
}
