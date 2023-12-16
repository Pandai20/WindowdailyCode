#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <iomanip>//put_time
#include <string>
#include <sstream> //stringstream
using namespace std;
void test1()//- 获取当前时间
{
    chrono::system_clock::time_point now = chrono::system_clock::now();//当前时间time_point格式

    std::time_t oldTime = time(nullptr);//c函数获取当前时间
    cout << "oldTime = " << oldTime << endl;
    chrono::system_clock::time_point timePoint = chrono::system_clock::now();//stl库获取当前时间
    std::time_t newTime = chrono::system_clock::to_time_t(timePoint);//转换为旧式接口，单位:秒
    cout << "newTime = " << newTime << endl;// oldTime == timeT
}
void test2() //- 格式化打印当前时间
{
    chrono::system_clock::time_point now = chrono::system_clock::now();//当前时间time_point格式
    std::time_t nowTime = chrono::system_clock::to_time_t(now);//转换为 std::time_t 格式 
    
    std::cout << std::put_time(localtime(&nowTime), "%Y-%m-%d %X") << std::endl;; // 2019-06-18 14:25:56

    //转换为字符串
    std::stringstream ss;
    ss << std::put_time(std::localtime(&nowTime), "%F %T");
    std::string str = ss.str();
    std::cout << str << endl;
}

void test3()//时长之间的转换
{
    std::chrono::milliseconds mil_mytime(54999);
    std::chrono::seconds sec_time = std::chrono::duration_cast<std::chrono::seconds>(mil_mytime);
    std::cout<<sec_time.count() << endl; //54 ,表明数据会截断
}


int main() {
    test1();
    test2();
    test3();
    return 0;
}
