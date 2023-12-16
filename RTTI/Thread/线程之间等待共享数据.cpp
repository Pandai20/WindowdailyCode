#include <iostream>
#include <string>
#include <chrono>
#include <deque>
#include <mutex>
#include <thread>
#include <memory>
#include <functional>
#include <condition_variable>
class Call;
class MyClass
{
public:
	MyClass() :ptrMyclass(new Call()) {
	};
	~MyClass() {};
	void Regist();
	void CallBcak(std::string param);
	void SolveParam();
	void ShowName();
	std::unique_ptr<Call> ptrMyclass;
private:
	std::deque<std::string> m_strParam;
	std::mutex m_lock;
	std::condition_variable m_Cdtion;
};
//注册为回调函数
void MyClass::CallBcak(std::string param)
{
	std::unique_lock<std::mutex> ml(m_lock);
	m_strParam.push_back(param);
	m_Cdtion.notify_one();
}
void MyClass::SolveParam()
{
	std::unique_lock<std::mutex> ml(m_lock);
	//m_Cdtion.wait(ml, [this]() {!m_strParam.empty();});
	auto timeout = std::chrono::steady_clock().now() + std::chrono::seconds(4);
	m_Cdtion.wait_until(ml, timeout, [this]() {return !m_strParam.empty(); });
	std::string strName = m_strParam.front();
	m_strParam.pop_front();
	std::cout <<"pop name:" << strName << std::endl;
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
}

class Call
{
public:
	Call();
	~Call()=default;
	typedef std::function<void(std::string param)> MyFunc;
public:
	void SetBackCall(MyFunc cb);
	void CallbackRegistry();
private:
	MyFunc callback;
};

void Call::CallbackRegistry()
{
	std::chrono::steady_clock::time_point timeout;
	int count = 0;
	std::string name;
	do
	{
		timeout = std::chrono::steady_clock().now();
		name = "panda" + std::to_string(count);
		callback(name);
		count++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (std::chrono::steady_clock().now() < timeout + std::chrono::seconds(10));

}

void Call::SetBackCall(MyFunc cb)
{
	callback = cb;
}

int main()
{
	MyClass myPanda;
	myPanda.Regist();
	myPanda.SolveParam();
	std::thread thread1([&]() { myPanda.ptrMyclass->CallbackRegistry(); });
	myPanda.ShowName();

	thread1.join();
	return 0;
}