#include <iostream>
#include <string>
#include <chrono>
#include <deque>
#include <mutex>
#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
class CallBack
{
public:
	CallBack();
	~CallBack() = default;
	typedef std::function<void(std::string param)> MyFunc;
public:
	void SetBackCall(MyFunc cb);
	void CallbackRegistry();
private:
	MyFunc callback;
};
CallBack::CallBack() {};
void CallBack::CallbackRegistry()
{
	std::chrono::steady_clock::time_point timeout = std::chrono::steady_clock().now();
	int count = 0;
	std::string name;
	do
	{
		name = "panda" + std::to_string(count);
		callback(name);
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (std::chrono::steady_clock().now() < timeout + std::chrono::seconds(10));

}

void CallBack::SetBackCall(MyFunc cb)
{
	callback = cb;
}

class MyClass
{
public:
	MyClass() :ptrMyclass(new CallBack()),cvthing(false) {
	};
	~MyClass() {};
	void Regist();
	void CallBcak(std::string param);
	void SolveParam();
	void ShowName();
	std::unique_ptr<CallBack> ptrMyclass;
private:
	std::deque<std::string> m_strParam;
	std::mutex m_lock;
	std::condition_variable m_Cdtion;
	bool cvthing;
};
//ע��Ϊ�ص�����
void MyClass::CallBcak(std::string param)
{
	std::unique_lock<std::mutex> ml(m_lock);
	m_strParam.push_back(param);
	cvthing = true;
	m_Cdtion.notify_one();
}
void MyClass::SolveParam()
{
	auto timeout = std::chrono::steady_clock().now() + std::chrono::seconds(4);
	while (true)
	{
		std::unique_lock<std::mutex> ml(m_lock);
		//m_Cdtion.wait(ml, [this]() {return cvthing; });
		//���ó�ʱ�˳�

		if (m_Cdtion.wait_until(ml, timeout, [this]() { return cvthing; }))
		{
			if (!m_strParam.empty()) {
				std::string strName = m_strParam.front();
				m_strParam.pop_front();
				std::cout << "pop name:" << strName << std::endl;
			}
			else {
				// �������Ϊ�յ����
				std::cout << "Queue is empty." << std::endl;
			}
			cvthing = false();
		}
		else
		{
			std::cout << "tiemout and quit" << std::endl;
			cvthing = false();
			return;
		}
	}
	
}
void MyClass::ShowName()
{
	for (auto name : m_strParam)
	{
		std::cout << name << std::endl;
	}
}
void MyClass::Regist()
{
	ptrMyclass->SetBackCall(std::bind(&MyClass::CallBcak, this, std::placeholders::_1));
	std::cout << "regist success " << std::endl;
}



int main()
{
	MyClass myPanda;
	myPanda.Regist();

	// �����̲߳���������
	std::thread m_thread([&]() {
		// �����߳���ִ�� CallbackRegistry
		myPanda.ptrMyclass->CallbackRegistry();
		});

	// ���߳�ִ�� SolveParam����������������
	myPanda.SolveParam();

	// �ȴ� m_thread ���
	m_thread.join();

	// �����߳���ִ�� ShowName
	myPanda.ShowName();

	return 0;
}