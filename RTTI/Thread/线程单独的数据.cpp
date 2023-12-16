//验证thread_local

#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
thread_local int panda = 0; //每个线程都具有自己单独的数据

using myfunc = void (*)();

void Function1() {
	panda += 1;
	cout << "I am :" << this_thread::get_id() << ", and myname is: " << panda << endl;
	std::this_thread::sleep_for(chrono::seconds(1));
}

void Function2() {
	panda += 10;
	cout << "I am :" << this_thread::get_id() << ", and myname is: " << panda << endl;
	std::this_thread::sleep_for(chrono::seconds(2));
}

void myFunction(int a , myfunc myFuc)
{
	std::chrono::seconds m_time(a);
	auto time_now = chrono::system_clock::now();
	while (true)
	{
		auto time_next = chrono::system_clock::now();

		auto interval = chrono::duration_cast<std::chrono::seconds>(time_next - time_now);

		if (interval >= m_time)
		{
			myFuc();
			time_now = chrono::system_clock::now();
		}
	}

}


int main2()
{
	thread m_thread1(myFunction,1, Function1);
	thread m_thread2(myFunction, 2, Function2);

	m_thread1.join();
	m_thread2.join();
	return 0;
}