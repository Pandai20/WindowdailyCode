#include <iostream>
using namespace std;

class Strategy //策略
{
public:
	virtual void sort() = 0;
};

class SelectSort : public Strategy
{
public:
	virtual void sort()
	{
		cout << "选择排序算法" << endl;
	}
};

class InsertSort : public Strategy
{
public:
	virtual void sort()
	{
		cout << "插入排序算法" << endl;
	}
};

class Context
{
private:
	Strategy* m_strategy;
public:
	void set_strategy(Strategy* m_strategy)
	{
		this->m_strategy = m_strategy;
	}
	void execute_strategy()
	{
		this->m_strategy->sort();
	}
};

int main()
{
	Strategy* s1 = NULL;
	Context* c = NULL;

	c = new Context;

	cout << "========================" << endl;
	//使用选择排序算法进行排序
	cout << "使用选择排序算法进行排序" << endl;
	s1 = new SelectSort;
	c->set_strategy(s1);
	c->execute_strategy();
	delete s1;
	cout << "========================" << endl;

	cout << "使用插入排序算法进行排序" << endl;
	s1 = new InsertSort;
	c->set_strategy(s1);
	c->execute_strategy();
	delete s1;
	delete c;
	cout << "========================" << endl;
	
	system("pause");
	return 0;
}