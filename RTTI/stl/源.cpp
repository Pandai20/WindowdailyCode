#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
    //这里的意思是给vector分配10个空间
    std::vector<int> numbers(10);

    // 为大小为10的vector分配随机数值
    for (int i = 0; i < 10; ++i) {
        numbers[i] = rand();
    }
    //使用拉曼达表达式，定义的时候靠考虑全面
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        if (a % 2 == 0 && b % 2 != 0) {
            return true;
        }
        else if (b % 2 == 0 && a % 2 != 0) {
            return false;
        }
        else
        {
            return a<b;
        }
        });

    for (int num : numbers) {
        std::cout << num << " "<<std::endl;
    }
    //这里给num赋初值。在构造函数列表初始化也是使用operator()进行初始化
    int num1(10);
    std::cout << num1 << std::endl;
    return 0;
}
