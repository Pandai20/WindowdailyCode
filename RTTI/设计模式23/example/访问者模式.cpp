#include <iostream>
using namespace std;
#include <list>
#include <string>

class Element;

class Visitor //抽象访问者
{
public:
	virtual void visit(Element* e) = 0;
};

class Element //抽象元素
{
public:
	virtual void reception(Visitor* v) = 0;
	virtual string get_name() = 0;
};

class Group : public Element //整个集团
{
private:
	list<Element*> l;
public:
	virtual void reception(Visitor* v)
	{
		for (list<Element*>::iterator it = l.begin(); it != l.end(); it++)
		{
			(*it)->reception(v);
		}
	}
	void add_element(Element* e)
	{
		l.push_back(e);
	}
	virtual string get_name()
	{
		return "整个集团公司";
	}
};

class Department1 : public Element //部门1
{
public:
	virtual void reception(Visitor* v)
	{
		v->visit(this);
	}
	virtual string get_name()
	{
		return "第一事业部";
	}
};

class Department2 : public Element //部门2
{
public:
	virtual void reception(Visitor* v)
	{
		v->visit(this);
	}
	string get_name()
	{
		return "第二事业部";
	}
};

class President : public Visitor //董事长
{
public:
	virtual void visit(Element* e)
	{
		cout << "董事长访问：" << e->get_name() << endl;
	}
};

class Leader1 : public Visitor //分管领导1
{
public:
	virtual void visit(Element* e)
	{
		cout << "第一分管领导访问：" << e->get_name() << endl;
	}
};

class Leader2 : public Visitor //分管领导2
{
public:
	virtual void visit(Element* e)
	{
		cout << "第二分管领导访问：" << e->get_name() << endl;
	}
};

int main()
{
	Visitor* v = NULL, * v1 = NULL, * v2 = NULL;
	Group* e = NULL;
	Element* e1 = NULL, * e2 = NULL;

	v = new President;
	v1 = new Leader1;
	v2 = new Leader2;
	e = new Group;
	e1 = new Department1;
	e2 = new Department2;

	//组织集团架构
	e->add_element(e1);
	e->add_element(e2);
	e->reception(v);

	e1->reception(v1);
	e2->reception(v2);

	delete e2;
	delete e1;
	delete e;
	delete v2;
	delete v1;
	delete v;
	
	system("pause");
	return 0;
}