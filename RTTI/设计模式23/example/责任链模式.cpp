#include <iostream>
using namespace std;

class Handler
{
protected: //供子类使用
	Handler* next;
public:
	virtual void perform_task() = 0; //统一的任务接口
	Handler* set_next(Handler* next) //设置下一个要执行的任务
	{
		this->next = next;
		return this->next;
	}
};

class Task1 : public Handler
{
public:
	virtual void perform_task()
	{
		cout << "任务 1 执行" << endl;
		if (next != NULL) //如果有下一个任务，则执行
		{
			next->perform_task();
		}
	}
};

class Task2 : public Handler
{
public:
	virtual void perform_task()
	{
		cout << "任务 2 执行" << endl;
		if (next != NULL)
		{
			next->perform_task();
		}
	}
};

class Task3 : public Handler
{
public:
	virtual void perform_task()
	{
		cout << "任务 3 执行" << endl;
		if (next != NULL)
		{
			next->perform_task();
		}
	}
};

int main()
{
	Handler* task1 = NULL;
	Handler* task2 = NULL;
	Handler* task3 = NULL;

	task1 = new Task1;
	task2 = new Task2;
	task3 = new Task3;

	//任务流程：task1 -> task2 -> task3 -> 结束
	cout << "任务流程：task1 -> task2 -> task3 -> 结束" << endl;
	task1->set_next(task2);
	task2->set_next(task3);
	task3->set_next(NULL);

	task1->perform_task();
	cout << "===================================" << endl;

	//改变流程
	cout << "任务流程：task3 -> task2 -> task1 -> 结束" << endl;
	task1->set_next(NULL);
	task2->set_next(task1);
	task3->set_next(task2);
	
	task3->perform_task();
	cout << "===================================" << endl;

	delete task3;
	delete task2;
	delete task1;
	
	system("pause");
	return 0;
}