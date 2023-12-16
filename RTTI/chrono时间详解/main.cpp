#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <iomanip>//put_time
#include <string>
#include <sstream> //stringstream
using namespace std;
void test1()//- ��ȡ��ǰʱ��
{
    chrono::system_clock::time_point now = chrono::system_clock::now();//��ǰʱ��time_point��ʽ

    std::time_t oldTime = time(nullptr);//c������ȡ��ǰʱ��
    cout << "oldTime = " << oldTime << endl;
    chrono::system_clock::time_point timePoint = chrono::system_clock::now();//stl���ȡ��ǰʱ��
    std::time_t newTime = chrono::system_clock::to_time_t(timePoint);//ת��Ϊ��ʽ�ӿڣ���λ:��
    cout << "newTime = " << newTime << endl;// oldTime == timeT
}
void test2() //- ��ʽ����ӡ��ǰʱ��
{
    chrono::system_clock::time_point now = chrono::system_clock::now();//��ǰʱ��time_point��ʽ
    std::time_t nowTime = chrono::system_clock::to_time_t(now);//ת��Ϊ std::time_t ��ʽ 
    
    std::cout << std::put_time(localtime(&nowTime), "%Y-%m-%d %X") << std::endl;; // 2019-06-18 14:25:56

    //ת��Ϊ�ַ���
    std::stringstream ss;
    ss << std::put_time(std::localtime(&nowTime), "%F %T");
    std::string str = ss.str();
    std::cout << str << endl;
}

void test3()//ʱ��֮���ת��
{
    std::chrono::milliseconds mil_mytime(54999);
    std::chrono::seconds sec_time = std::chrono::duration_cast<std::chrono::seconds>(mil_mytime);
    std::cout<<sec_time.count() << endl; //54 ,�������ݻ�ض�
}


int main() {
    test1();
    test2();
    test3();
    return 0;
}
