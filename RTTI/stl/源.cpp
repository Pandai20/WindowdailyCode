#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
    //�������˼�Ǹ�vector����10���ռ�
    std::vector<int> numbers(10);

    // Ϊ��СΪ10��vector���������ֵ
    for (int i = 0; i < 10; ++i) {
        numbers[i] = rand();
    }
    //ʹ����������ʽ�������ʱ�򿿿���ȫ��
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
    //�����num����ֵ���ڹ��캯���б��ʼ��Ҳ��ʹ��operator()���г�ʼ��
    int num1(10);
    std::cout << num1 << std::endl;
    return 0;
}
