#include <iostream>
using namespace std;
#include <string>
#include <list>

class Guard;

//观察者
class Soldier //士兵
{
private:
	Guard* guard;
public:
	Soldier(Guard* guard)
	{
		this->guard = guard;
	}
	void recv_infor(string infor)
	{
		cout << infor << ": 收到, 准备战斗" << endl;
	}
};

class Guard //哨兵
{
private:
	list<Soldier*> l;
public:
	void add_observer(Soldier* soldier)
	{
		l.push_back(soldier);
	}
	void send_infor(string infor)
	{
		for (list<Soldier*>::iterator it = l.begin(); it != l.end(); it++)
		{
			(*it)->recv_infor(infor);
		}
	}
};

int main()
{
	Soldier* s1 = NULL, * s2 = NULL, * s3 = NULL;
	Guard* g = NULL;

	g = new Guard;
	s1 = new Soldier(g);
	s2 = new Soldier(g);
	s3 = new Soldier(g);

	g->add_observer(s1);
	g->add_observer(s2);
	g->add_observer(s3);

	string s = "敌人来了";
	g->send_infor(s);
	
	system("pause");
	return 0;
}