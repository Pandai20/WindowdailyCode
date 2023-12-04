#include <iostream>
using namespace std;

class Hero
{
public:
	virtual void show_skill() = 0;
};

//初始的英雄：只能跑
class runHreo : public Hero
{
public:
	void run_skill()
	{
		cout << "只能跑的超人" << endl;
	}
	virtual void show_skill()
	{
		run_skill();
	}
};

//超人升级：新增了飞行技能
class flyHero : public Hero
{
private:
	Hero* m_hero;
public:
	flyHero(Hero* hero)
	{
		this->m_hero = hero;
	}
	void fly_skill()
	{
		cout << "拥有飞行技能" << endl;
	}
	virtual void show_skill()
	{
		this->m_hero->show_skill();
		fly_skill();
	}
};

//超人升级：可以发射激光
class laserHero : public Hero
{
private:
	Hero* m_hero;
public:
	laserHero(Hero* hero)
	{
		this->m_hero = hero;
	}
	void laser_skill()
	{
		cout << "可以发射激光" << endl;
	}
	virtual void show_skill()
	{
		this->m_hero->show_skill();
		laser_skill();
	}
};

int main()
{
	//创建一个超人角色
	Hero* myHero1 = NULL;

	cout << "*********第一个英雄*********" << endl;
	//初始功能只有跑
	cout << "======初始形态======" << endl;
	myHero1 = new runHreo;
	myHero1->show_skill();

	//功能增强：升级飞行技能
	cout << "======第一次升级======" << endl;
	Hero* myHero2 = new flyHero(myHero1);
	myHero2->show_skill();

	//再次升级：可以放大招
	cout << "======第二次升级======" << endl;
	Hero* myHero3 = new laserHero(myHero2);
	myHero3->show_skill();

	delete myHero1;
	delete myHero2;
	delete myHero3;

	cout << "*********第二个英雄*********" << endl;
	cout << "======初始形态======" << endl;
	myHero1 = new runHreo;
	myHero1->show_skill();

	//直接获取激光技能
	cout << "======升级======" << endl;
	myHero3 = new laserHero(myHero1);
	myHero3->show_skill();
	//增强功能可以自由组合
	
	system("pause");
	return 0;
}