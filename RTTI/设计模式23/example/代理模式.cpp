#include <iostream>
using namespace std;

//抽象主题角色
class CarStore
{
public:
	virtual void sail_Car() = 0;
};

//真实主题角色
class ReilCarStore : CarStore //实际汽车销售店铺
{
public:
	virtual void sail_Car()
	{
		cout << "实体店铺直接卖出汽车" << endl;
	}
};

//代理
class GZproxy : public CarStore //瓜子二手车是一个代理商
{
public:
	/*
	virtual void sail_Car()
	{
		cout << "瓜子二手车直营（自己卖）" << endl;
	}
	*/
	virtual void sail_Car()
	{
		ReilCarStore cartore;
		cartore.sail_Car(); //表面是瓜子二手车卖车，实际上销售的是实体店的车
		discount(); //扩充了实体店卖车的形式和功能
	}
	void discount()
	{
		cout << "双11活动打折" << endl;
	}
};

int main()
{
	GZproxy dd;
	dd.sail_Car();

	system("pause");
	return 0;
}