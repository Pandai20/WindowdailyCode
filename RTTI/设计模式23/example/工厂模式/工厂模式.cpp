#include <iostream>
using namespace std;

//抽象产品类
class PhoneInterface
{
public:
	virtual void print_brand() = 0;
};

//抽象工厂类
class FactoryInterface
{
public:
	virtual PhoneInterface* production_phone() = 0;
};

//苹果手机产品实现
class apple : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "苹果手机" << endl;
	}
};

//小米手机产品实现
class XiaoMi : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "小米手机" << endl;
	}
};

//苹果手机工厂
class AppleFactory : public FactoryInterface
{
public:
	virtual PhoneInterface* production_phone()
	{
		return new apple;
	}
};

//小米手机工厂
class XiaomiFactory : public FactoryInterface
{
public:
	virtual PhoneInterface* production_phone()
	{
		return new XiaoMi;
	}
};

int main()
{
	FactoryInterface* pFactory = NULL;
	PhoneInterface* pPhone = NULL;

	//要生产一台苹果手机
	//先创建一个苹果手机工厂
	pFactory = new AppleFactory;
	pPhone = pFactory->production_phone();
	pPhone->print_brand();
	delete pPhone;
	delete pFactory;

	//生产一个小米手机
	pFactory = new XiaomiFactory;
	pPhone = pFactory->production_phone();
	pPhone->print_brand();
	delete pPhone;
	delete pFactory;

	//工厂模式只能生产一种/一个苹果手机，我现在想生产国行、美版、港版的苹果手机
	//就需要三个苹果手机工厂才行

	system("pause");
	return 0;
}