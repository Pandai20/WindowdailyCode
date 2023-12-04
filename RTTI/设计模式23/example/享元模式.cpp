#include <iostream>
using namespace std;
#include <map>
#include <string>

class MyStr
{
protected:
	string str;
public:
	MyStr(string str)
	{
		this->str = str;
	}
	virtual void get_str() = 0;
};

class Hello : public MyStr
{
private:
	int id;
public:
	Hello(string str, int id) : MyStr(str)
	{
		this->id = id;
	}
	virtual void get_str()
	{
		cout << "id: " << id << "  对应的str:  " << str << endl;
	}
};

class Factory
{
private:
	map<int, Hello*> m;
public:
	~Factory()
	{
		while (!m.empty())
		{
			Hello* tmp = NULL;
			map<int, Hello*>::iterator it = m.begin();
			tmp = it->second;
			m.erase(it); 
			delete tmp;
		}
	}
	Hello* get_str(int id)
	{
		Hello* mtemp;
		map<int, Hello*>::iterator it;
		it = m.find(id);
		if (it == m.end())
		{
			string temp;
			cout << "该字符串未找到，请输入字符串：";
			cin >> temp;
			mtemp = new Hello(temp, id);
			m.insert(make_pair(id, mtemp));
			return mtemp;
		}
		else
		{
			return it->second;
		}
	}
};

int main()
{
	Hello* h1 = NULL, * h2 = NULL;
	Factory* f = NULL;

	f = new Factory;

	h1 = f->get_str(1);
	h1->get_str();

	h2 = f->get_str(1);
	h2->get_str();

	delete h2;
	delete h1;
	delete f;

	system("pause");
	return 0;
}