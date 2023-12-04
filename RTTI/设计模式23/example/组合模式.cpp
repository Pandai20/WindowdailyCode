#include <iostream>
using namespace std;
#include <string>
#include <vector>

class Component
{
public:
	virtual void display() = 0;
	virtual void add(Component* node) = 0;
	virtual void remove(Component* node) = 0;
	virtual vector<Component*>* get_child() = 0;
};

class Leaf : public Component
{
private:
	string name;
public:
	Leaf(string name)
	{
		this->name = name;
	}
	virtual void display()
	{
		cout << "Leaf: " << this->name << endl;
	}
	virtual void add(Component* node)
	{
		cout << "叶子结点，无法加入" << endl;
	}
	virtual void remove(Component* node)
	{
		cout << "叶子结点，无此操作" << endl;
	}
	virtual vector<Component*>* get_child()
	{
		cout << "叶子结点，无子结点" << endl;
		return NULL;
	}
};

class Composite : public Component
{
private:
	string name;
	vector<Component*>* vec;
public:
	Composite(string name)
	{
		this->name = name;
		vec = new vector<Component*>;
	}
	~Composite()
	{
		if (vec != NULL)
		{
			delete vec;
			vec = NULL;
		}
	}
	virtual void display()
	{
		cout << "Composite: " << this->name << endl;
	}
	virtual void add(Component* node)
	{
		vec->push_back(node);
	}
	virtual void remove(Component* node)
	{
		for (vector<Component*>::iterator it = vec->begin(); it != vec->end(); it++)
		{
			if (*it == node)
			{
				vec->erase(it);
			}
		}
	}
	virtual vector<Component*>* get_child()
	{
		cout << "*" << this->name << " child: " << "*\n";
		for (vector<Component*>::iterator it = vec->begin(); it != vec->end(); it++)
		{
			(*it)->display();
		}
		return vec;
	}
};

int main()
{
	Component* root = NULL;
	Leaf* l1 = NULL;
	Leaf* l2 = NULL;
	Composite* dir = NULL;

	root = new Composite("/root");
	l1 = new Leaf("1.cpp");
	l2 = new Leaf("2.cpp");
	dir = new Composite("/home");

	root->add(dir);
	dir->add(l1);
	dir->add(l2);

	cout << "============" << endl;
	root->display();
	root->get_child();
	dir->get_child();
	cout << "============" << endl;

	delete dir;
	delete l2;
	delete l1;
	delete root;

	system("pause");
	return 0;
}