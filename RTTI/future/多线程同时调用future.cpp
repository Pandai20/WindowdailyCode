#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
//��֤future��һ������Ķ����ڶ���̷߳�����ֻ��һ������

int future_function()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "called again" << std::endl; //���ʹ��shared_future�Ļ�ʵ���ϵ�����һ�Σ�Ҳ˵��ͨ���Ͼ����asyncҲֻ�ǵ���һ�Σ�
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
			std::cout << std::this_thread::get_id() << "get1 result �� " << a << std::endl;
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
			int a = future_result.get();//������׳��쳣��unique future����ֻ�ܱ�һ���߳�get
			std::cout << std::this_thread::get_id() << "get222 result �� " << a << std::endl;
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