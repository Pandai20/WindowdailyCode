#include <iostream>
using namespace std;
#include <string>

class Memento //备忘录
{
private:
	string str;
public:
	Memento(string str)
	{
		this->str = str;
	}
	string get_str()
	{
		return this->str;
	}
};

class Originator
{
private:
	string str;
public:
	void set_str(string str)
	{
		this->str = str;
	}
	Memento* get_memo()
	{
		return new Memento(this->str);
	}
	void print_str()
	{
		cout << this->str << endl;
	}
	void recover(Memento* memo)
	{
		this->str = memo->get_str();
	}
};

class Caretaker
{
private:
	Memento* memo;
public:
	void set_memo(Memento* memo)
	{
		this->memo = memo;
	}
	Memento* get_memo()
	{
		return this->memo;
	}
};

int main()
{
	Originator* ori = NULL;
	Caretaker* care = NULL;

	care = new Caretaker;

	//原始状态
	ori = new Originator;
	ori->set_str("原始状态");
	ori->print_str();
	care->set_memo(ori->get_memo());

	//修改状态
	ori->set_str("状态改变");
	ori->print_str();

	//恢复状态
	ori->recover(care->get_memo());
	ori->print_str();

	delete care;
	delete ori;
	
	system("pause");
	return 0;
}