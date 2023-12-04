#include <iostream>
using namespace std;

#include <string>

//最终产品类：汽车
class CarProduct
{
public:
	void set_shell(string shell) //建造汽车外壳
	{
		this->shell = shell;
	}
	void set_engine(string engine) //建造汽车发动机
	{
		this->engine = engine;
	}
	void set_whell(string whell) //建造汽车轮子
	{
		this->whell = whell;
	}
	//获取属性
	string get_shell()
	{
		return this->shell;
	}
	string get_engine()
	{
		return this->engine;
	}
	string get_whell()
	{
		return this->whell;
	}
private:
	string shell; //外壳
	string engine; //发动机
	string whell; //轮子
};

//建造者基类：抽象施工单位
class Builder
{
public:
	virtual void builder_shell() = 0; //汽车外壳的建造方式接口
	virtual void builder_engine() = 0; //发动机的建造方式
	virtual void builder_whell() = 0; //车轮的建造方式
	virtual CarProduct* get_car() = 0; //返回建造好的汽车产品
};

//具体的建造者：具体施工单位、具体的建造方式
class TruckBuilder : public Builder //卡车建造商
{
private:
	CarProduct* m_car;
public:
	TruckBuilder()
	{
		this->m_car = new CarProduct; 
	}
	virtual void builder_shell()
	{
		this->m_car->set_shell("卡车外壳");
	}
	virtual void builder_engine()
	{
		this->m_car->set_engine("卡车发动机");
	}
	virtual void builder_whell()
	{
		this->m_car->set_whell("卡车轮子");
	}
	virtual CarProduct* get_car()
	{
		return this->m_car;
	}
};
class TrainBuilder : public Builder //火车建造商
{
private:
	CarProduct* m_car;
public:
	TrainBuilder()
	{
		this->m_car = new CarProduct;
	}
	virtual void builder_shell()
	{
		this->m_car->set_shell("火车外壳");
	}
	virtual void builder_engine()
	{
		this->m_car->set_engine("火车发动机");
	}
	virtual void builder_whell()
	{
		this->m_car->set_whell("火车轮子");
	}
	virtual CarProduct* get_car()
	{
		return this->m_car;
	}
};

//指挥者：设计师，负责设计建造逻辑
class Director
{
public:
	Director(Builder* builder)
	{
		this->m_builder = builder;
	}
	//建造逻辑
	void builder_logic()
	{
		//1.先建造车的外壳
		this->m_builder->builder_shell();
		cout << "先建造车的外壳\t";
		//2.再安装发动机
		this->m_builder->builder_engine();
		cout << "再安装发动机\t";
		//3.最后安装车轮
		this->m_builder->builder_whell();
		cout << "最后安装车轮\n";
	}
private:
	Builder* m_builder;
};

//客户端
int main()
{
	CarProduct* myCar = NULL;
	Builder* tempBuilder = NULL;
	Director* carDector = NULL;

	//需求：建造一辆卡车
	//首先找一个卡车建造商
	tempBuilder = new TruckBuilder;
	//把建造商交给指挥者（设计师）管理
	carDector = new Director(tempBuilder);
	//开始建造
	carDector->builder_logic();
	//获取产品  对象的建造逻辑和产品的表示分离
	myCar = tempBuilder->get_car();
	cout << "======产品信息======" << endl;
	cout << myCar->get_shell() << endl;
	cout << myCar->get_engine() << endl;
	cout << myCar->get_whell() << endl;
	cout << "====================" << endl;
	delete myCar;
	delete carDector;
	delete tempBuilder;

	//新需求：需要一辆火车
	tempBuilder = new TrainBuilder;
	carDector = new Director(tempBuilder);
	carDector->builder_logic();
	myCar = tempBuilder->get_car();
	cout << "======产品信息======" << endl;
	cout << myCar->get_shell() << endl;
	cout << myCar->get_engine() << endl;
	cout << myCar->get_whell() << endl;
	cout << "====================" << endl;
	delete myCar;
	delete carDector;
	delete tempBuilder;

	system("pause");
	return 0;
}