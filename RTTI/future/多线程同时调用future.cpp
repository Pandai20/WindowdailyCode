#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
//验证future是一个独享的对象，在多个线程访问下只有一个返回

int future_function()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "called again" << std::endl; //如果使用shared_future的话实际上调用了一次（也说的通，毕竟这个async也只是调用一次）
	return 8;
}



int main()
{
	//std::future<int> future_result = std::async(future_function);
	std::shared_future<int> future_result = std::async(future_function);

	std::mutex myMutex;

	std::thread thread1([&]() {
		try
		{
			std::lock_guard<std::mutex> lm(myMutex);
			int a = future_result.get();
			std::cout << std::this_thread::get_id() << "get1 result ： " << a << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Caught exception: " << e.what() << std::endl;
		}
	});
	std::thread thread2([&]() {
		try
		{
			std::lock_guard<std::mutex> lm(myMutex);
			int a = future_result.get();//这里会抛出异常，unique future对象只能被一个线程get
			std::cout << std::this_thread::get_id() << "get222 result ： " << a << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Caught222 exception: " << e.what() << std::endl;
		}
	});

	thread1.join();
	thread2.join();
	return 0;
}