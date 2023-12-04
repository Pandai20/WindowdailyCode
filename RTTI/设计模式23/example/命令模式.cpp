#include <iostream>
using namespace std;

class Banker
{
public:
	void saving_money()
	{
		cout << "办理存款业务" << endl;
	}
	void withdraw_money()
	{
		cout << "办理取款业务" << endl;
	}
};

class Command
{
public:
	virtual void conduct_business() = 0;
};

class SaveCommand : public Command 
{
private:
	Banker* bker;
public:
	SaveCommand(Banker* bker)
	{
		this->bker = bker;
	}
	virtual void conduct_business()
	{
		this->bker->saving_money();
	}
};

class WithdrowCommand : public Command
{
private:
	Banker* bker;
public:
	WithdrowCommand(Banker* bker)
	{
		this->bker = bker;
	}
	virtual void conduct_business()
	{
		this->bker->withdraw_money();
	}
};

class Manager
{
private:
	Command* com;
public:
	Manager(Command* com)
	{
		this->com = com;
	}
	void order()
	{
		com->conduct_business();
	}
};

int main()
{
	Manager* m = NULL;
	Command* com = NULL;
	Banker* bker = NULL;

	bker = new Banker;
	com = new SaveCommand(bker); //存款命令
	m = new Manager(com);
	m->order();

	delete com;
	delete m;
	com = new WithdrowCommand(bker); //取款命令
	m = new Manager(com);
	m->order();

	delete m;
	delete com;
	delete bker;
	
	system("pause");
	return 0;
}