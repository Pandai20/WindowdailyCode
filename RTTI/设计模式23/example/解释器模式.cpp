#include <iostream>
using namespace std;

class Context
{
private:
	int data;
	int ret;
public:
	void set_data(int data)
	{
		this->data = data;
	}
	void set_ret(int ret)
	{
		this->ret = ret;
	}
	int get_data()
	{
		return this->data;
	}
	int get_ret()
	{
		return this->ret;
	}
};

class Expression
{
protected:
	Context* context;
public:
	virtual void interpret(Context* context) = 0;
};

class PlusExpression : public Expression
{
	virtual void interpret(Context* context)
	{
		int temp = context->get_data();
		temp++;
		context->set_ret(temp);
	}
};

int main()
{
	Expression* e = NULL;
	Context* data = NULL;

	e = new PlusExpression;
	data = new Context;

	data->set_data(1);
	cout << "原始数据：" << data->get_data() << endl;
	e->interpret(data);
	data->get_ret();
	cout << "经加法解释器处理后：" << data->get_ret() << endl;

	delete data;
	delete e;
	
	system("pause");
	return 0;
}