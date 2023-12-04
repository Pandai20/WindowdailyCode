#include <iostream>
using namespace std;

class Color
{
public:
	virtual void get_color() = 0; 
};

class Red : public Color
{
public:
	virtual void get_color()
	{
		cout << "红色" << endl;
	}
};

class Blue : public Color
{
public:
	virtual void get_color()
	{
		cout << "蓝色" << endl;
	}
};

class Yellow : public Color
{
public:
	virtual void get_color()
	{
		cout << "黄色" << endl;
	}
};

class Graph
{
protected:
	Color* mGraphColor;
public:
	Graph(Color* mGraphColor)
	{
		this->mGraphColor = mGraphColor;
	}
	virtual void smear_color() = 0; //给图形上色
};

class Circle : public Graph
{
public:
	Circle(Color* mGraphColor) : Graph(mGraphColor) {};
	virtual void smear_color()
	{
		cout << "圆形 + ";
		mGraphColor->get_color();
	}
};

class Triangle : public Graph
{
public:
	Triangle(Color* mGraphColor) : Graph(mGraphColor) {};
	virtual void smear_color()
	{
		cout << "三角形 + ";
		mGraphColor->get_color();
	}
};

int main()
{
	Color* m_color = NULL;

	m_color = new Red;
	Circle* m_circle = new Circle(m_color);
	m_circle->smear_color();

	delete m_color;
	m_color = new Blue;
	Triangle* m_triangle = new Triangle(m_color);
	m_triangle->smear_color();

	delete m_color;
	delete m_triangle;
	delete m_circle;
	
	system("pause");
	return 0;
}