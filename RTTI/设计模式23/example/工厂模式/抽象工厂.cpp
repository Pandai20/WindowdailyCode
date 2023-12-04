#include <iostream>
using namespace std;

//抽象产品
class PhoneInterface
{
public:
	virtual void print_brand() = 0;
};

//抽象工厂
class FactoryInterface
{
public:
	//产品线1：苹果手机
	virtual PhoneInterface* production_apple() = 0;
	//产品线2：小米手机
	virtual PhoneInterface* production_xiaomi() = 0;
};

//大陆版苹果手机
class ChinaApple : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "大陆版本的苹果手机" << endl;
	}
};

//美版的苹果手机
class UsApple : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "美版的苹果手机" << endl;
	}
};

//大陆版小米手机
class ChinaXiaomi : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "大陆版本的小米手机" << endl;
	}
};

//美版的小米手机
class UsXiaomi : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "美版的小米手机" << endl;
	}
};

//生产大陆版本手机的工厂
class ChinaFactory : public FactoryInterface
{
public:
	//产品线1：苹果手机
	virtual PhoneInterface* production_apple()
	{
		return new ChinaApple;
	}
	//产品线2：小米手机
	virtual PhoneInterface* production_xiaomi()
	{
		return new ChinaXiaomi;
	}
};

//生产美版手机的工厂
class UsFactory : public FactoryInterface
{
public:
	//产品线1：苹果手机
	virtual PhoneInterface* production_apple()
	{
		return new UsApple;
	}
	//产品线2：小米手机
	virtual PhoneInterface* production_xiaomi()
	{
		return new UsXiaomi;
	}
};

int main()
{
	FactoryInterface* pFactory = NULL;
	PhoneInterface* pPhone = NULL;

	//使用大陆版手机的工厂
	cout << "======大陆版手机工厂======" << endl;
	pFactory = new ChinaFactory;
	//生产大陆版苹果手机
	pPhone = pFactory->production_apple();
	pPhone->print_brand();
	delete pPhone;
	//生产大陆版小米手机
	pPhone = pFactory->production_xiaomi();
	pPhone->print_brand();
	delete pPhone;
	delete pFactory;

	//使用美版手机的工厂
	cout << "======美版手机工厂======" << endl;
	pFactory = new UsFactory;
	pPhone = pFactory->production_apple();
	pPhone->print_brand();
	delete pPhone;
	pPhone = pFactory->production_xiaomi();
	pPhone->print_brand();
	delete pPhone;
	delete pFactory;

	system("pause");
	return 0;
}