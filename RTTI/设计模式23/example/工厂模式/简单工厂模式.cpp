#include <iostream>
using namespace std;

//抽象产品类
class PhoneInterface
{
public:
	virtual void print_brand() = 0;
};

//具体产品类
class apple : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "苹果手机" << endl;
	}
};


class XiaoMi : public PhoneInterface
{
public:
	virtual void print_brand()
	{
		cout << "小米手机" << endl;
	}
};

//工厂类
class Factory
{
public:
	PhoneInterface* production_phone(int flag)
	{
		PhoneInterface* pTemp = NULL;
		switch (flag) //所有的生产都集中在一个工厂中，每次修改都要在类中修改，不符合开闭原则
		{
		case 1:
			pTemp = new apple;
			break;
		case 2:
			pTemp = new XiaoMi;
			break;
		default:
			pTemp = NULL;
			break;
		}
		return pTemp;
	}
};

int main()
{
	Factory* pF = NULL;
	PhoneInterface* pPhone = NULL;

	pF = new Factory;
	pPhone = pF->production_phone(1);
	pPhone->print_brand();
	delete pPhone;
	
	pPhone = pF->production_phone(2);
	pPhone->print_brand();
	delete pF;
	delete pPhone;

	system("pause");
	return 0;
}