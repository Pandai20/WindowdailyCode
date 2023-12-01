#include <iostream>
#include <thread>
#include <chrono>
#define DEBUG
void threadFunction(int& num)
{
	num = 5;
	std::cout << "I'm children sleep 5 seconds" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "I'm children going out" << std::endl;
}
void threadFunction1(){ std::cout << "I'm children two" << std::endl; }
int main()
{
	int number = 10;
	std::thread m_thread(threadFunction, std::ref(number));
	//std::thread m_thread(threadFunction1);   //只能创建一个对象，m_thread重定义，多次初始化
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "first : " << m_thread.joinable() << std::endl;
	std::cout << "number : " << number << std::endl;
#ifdef DEBUG
	m_thread.detach();
	std::cout << "thrid : " << m_thread.joinable() << std::endl;
	return 0;
#endif // DEBUG
	m_thread.join();
	std::cout << "second : " << m_thread.joinable() << std::endl;
	return 0;
}