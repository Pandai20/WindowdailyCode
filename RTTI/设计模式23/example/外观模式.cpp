#include <iostream>
using namespace std;

class Screen //子系统1
{
public:
	void get_attr()
	{
		cout << "显示屏子系统" << endl;
	}
};

class Host //子系统2
{
public:
	void get_attr()
	{
		cout << "主机子系统" << endl;
	}
};

class Keyboard //子系统3
{
public:
	void get_attr()
	{
		cout << "键盘子系统" << endl;
	}
};

class Facade
{
private:
	Screen* mScreen;
	Host* mHost;
	Keyboard* mKeyboard;
public:
	Facade()
	{
		mScreen = new Screen;
		mHost = new Host;
		mKeyboard = new Keyboard;
	}
	~Facade()
	{
		if (mScreen != NULL)
		{
			delete mScreen;
		}
		if (mHost != NULL)
		{
			delete mHost;
		}
		if (mKeyboard != NULL)
		{
			delete mKeyboard;
		}
	}
	void get_attr()
	{
		this->mScreen->get_attr();
		this->mHost->get_attr();
		this->mKeyboard->get_attr();
	}
};

void Func1()
{
	Screen* mScreen;
	Host* mHost;
	Keyboard* mKeyboard;

	mScreen = new Screen;
	mHost = new Host;
	mKeyboard = new Keyboard;

	mScreen->get_attr();
	mHost->get_attr();
	mKeyboard->get_attr();
}

int main()
{
	//传统方法
	Func1();
	
	//外观模式
	Facade* f = new Facade;
	f->get_attr();
	delete f;

	system("pause");
	return 0;
}