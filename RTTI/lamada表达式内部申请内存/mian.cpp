#include <iostream>

class MyFatherClass
{
public:
	MyFatherClass() {};
	~MyFatherClass() {};
	virtual void SetDate(int number)=0;
	virtual void GetDate() = 0;
};

class SonClass :public MyFatherClass
{
public:
	SonClass():date(0) {};
	~SonClass() {};
	void SetDate(int number) { date = number; };
	void GetDate() { std::cout << date << std::endl;};
private:
	int date;
};
#include <map>
#include <functional>
class GirlClass :public MyFatherClass
{
public:
	GirlClass() :date(0) {};
	~GirlClass() {};
	void SetDate(int number) { date = number; };
	void GetDate() { std::cout << date << std::endl; };
private:
	int date;
};
typedef struct MyDate
{
	MyDate() :name("son"), date(9527) {};
	std::string name;
	int date;
}Mydate;
std::map < std::string, std::function<void(MyFatherClass*& , Mydate&)>> funMap;
int main()
{
	MyFatherClass* ptrMyclass = nullptr;
	//形参如果是指针，那么传入的需得是二级指针或者引用
	auto function1 = [](MyFatherClass*& myclass, Mydate& mydate) {
		myclass = new SonClass();
		myclass->SetDate(mydate.date);
	};
	auto function2= [](MyFatherClass*& myclass, Mydate& mydate) {
		myclass = new GirlClass();
		myclass->SetDate(mydate.date);
	};
	funMap.insert(std::make_pair("son", function1));
	funMap.insert(std::make_pair("girl", function1));
	//获取消息
	Mydate GetMsg;
	for (auto i : funMap){
		if (i.first == GetMsg.name){
			i.second(ptrMyclass, GetMsg); break;
		}
	}
	ptrMyclass->GetDate(); 
	if (nullptr != ptrMyclass)
		delete ptrMyclass;
	return 0;
}