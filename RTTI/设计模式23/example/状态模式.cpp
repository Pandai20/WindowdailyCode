#include <iostream>
using namespace std;

class State;
class Machine;

class State
{
public:
	virtual void get_state(Machine* m) = 0;
};

class Machine
{
private:
	State* current; //当前状态
	int flag; //状态标志
public:
	State* get_current()
	{
		return this->current;
	}
	void set_current(State* s)
	{
		this->current = s;
	}
	void set_flag(int flag)
	{
		this->flag = flag;
	}
	void execute_state()
	{
		current->get_state(this);
	}
	int get_flag()
	{
		return flag;
	}
};

class State1 : public State
{
public:
	virtual void get_state(Machine* m);
};

class State2 : public State //状态2
{
public:
	virtual void get_state(Machine* m);
};

void State1::get_state(Machine* m)
{
	if (m->get_flag() == 1)
	{
		//当前状态标志是1，则执行状态1
		cout << "执行状态1" << endl;
	}
	else
	{
		//当前状态标志不是1，则切换为状态2

		//删除原来的状态
		delete m->get_current();
		//把当前状态设置为状态2
		m->set_flag(2);
		m->set_current(new State2);
		//执行状态
		m->get_current()->get_state(m);
	}
}

void State2::get_state(Machine* m)
{
	if (m->get_flag() == 2)
	{
		cout << "执行状态2" << endl;
	}
	else
	{
		//删除原状态
		delete m->get_current();
		//设置新的当前状态
		m->set_flag(1);
		m->set_current(new State1);
		//执行当前状态
		m->get_current()->get_state(m);
	}
}

int main()
{
	Machine* m = NULL;
	State* s = NULL;

	m = new Machine;

	cout << "======初始状态======" << endl;
	//初始化为状态1
	s = new State1;
	m->set_flag(1);
	m->set_current(s);
	m->execute_state();

	cout << "======切换为状态2======" << endl;
	//切换为状态2
	m->set_flag(2);
	m->execute_state();

	cout << "======切换为状态1======" << endl;
	//切换为状态1
	m->set_flag(1);
	m->execute_state();

	delete s;
	delete m;

	system("pause");
	return 0;
}