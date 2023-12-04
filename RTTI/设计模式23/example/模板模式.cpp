#include <iostream>
using namespace std;

class WearClothes //穿衣服
{
public:
	virtual void wear_coat() = 0;
	virtual void wear_pants() = 0;
	virtual void wear_shoe() = 0;
public:
	void wear_order() //穿衣服的顺序已经提前确定好了---模板
	{
		wear_coat(); //先穿外套
		wear_pants(); //再穿裤子
		wear_shoe(); //最后穿鞋
	}	
};		

class WearSuit : public WearClothes //穿西装
{
	virtual void wear_coat()
	{
		cout << "穿西服外套" << endl;
	}
	virtual void wear_pants()
	{
		cout << "穿西服裤子" << endl;
	}
	virtual void wear_shoe()
	{
		cout << "穿小皮鞋" << endl;
	}
};

class WearPajamas : public WearClothes //穿睡衣
{
	virtual void wear_coat()
	{
		cout << "穿睡衣" << endl;
	}
	virtual void wear_pants()
	{
		cout << "穿睡裤" << endl;
	}
	virtual void wear_shoe()
	{
		cout << "穿拖鞋" << endl;
	}
};

int main()
{
	WearClothes* wear = NULL;

	//穿西装应酬
	wear = new WearSuit;
	wear->wear_order();
	delete wear;

	//穿睡衣睡觉
	wear = new WearPajamas;
	wear->wear_order();
	delete wear;

	system("pause");
	return 0;
}