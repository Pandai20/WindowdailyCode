#include <iostream>

#include <cstdarg>
void exampleFunction() {
    // �ֲ���̬����
    static int count = 0;

    // ��� count ��ֵ
    std::cout << "Count: " << count << std::endl;

    // �� count ֵ����
    count++;
}

int main() {
    // ��ε��� exampleFunction
    exampleFunction();
    exampleFunction();
    exampleFunction();

    return 0;
}
