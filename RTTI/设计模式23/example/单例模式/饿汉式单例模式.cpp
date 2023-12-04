#include <iostream>
using namespace std;

#include <windows.h> //Sleep 函数
#include <process.h> //进程、线程相关

class SingletonPattern
{
private:
	SingletonPattern()
	{
		count++;
		Sleep(1000); //加入这里有一个延迟函数，第一个线程在new的时候，如果延时还没结束
					   //第二个线程又过来new一个对象，这时候因为第一个对象还没有new出来
					   //所以single还是NULL，这样又会进入构造函数，最后总共new了两个对象
						//这样返回的两个对象是两次new出来的，就不是单例模式了
		printf("私有的构造函数\n");
	}
public:
	static int get_count()
	{
		return count;
	}
public: //构造函数被私有化了，所以应该提供一个对外访问的方法，来创建对象
	/*
	static SingletonPattern* get_single() //只有在调用该函数的时候才会new一个对象，懒汉式
			//懒汉式优点：用到的时候才去new节省资源
			//缺点：C++构造函数不能保证线程安全
	{
		if (single == NULL) //为保证单例，只new一次
		{					//如果不加这个判断，每次创建对象都会new一个single，这就不是单例了
			single = new SingletonPattern;
		}
		//return this->single;
		return single; //静态成员属于整个类，没有this指针
	}
	*/
	static SingletonPattern* get_single() 
	{
		return single; 
	}
private: //static 成员，类定义的所有对象共有static成员
	static SingletonPattern* single; //指针，不能是变量，否则编译器不知道如何分配内存
	static int count;
};

//SingletonPattern* SingletonPattern::single = NULL; //告诉编译器分配内存
SingletonPattern* SingletonPattern::single = new SingletonPattern; //饿汉式单例，一开始就new了一个对象
															       //占用了资源
int SingletonPattern::count = 0;

void thread_func1(void* arc)
{
	DWORD id = GetCurrentThreadId();
	int num = SingletonPattern::get_single()->get_count();
	printf("构造函数调用次数：%d\n", num); //调用了3次构造函数 --- 不是单例
	printf("当前线程是：%d\n", id);
	//cout << "当前线程是：" << id << endl; //会有问题
}

int main() 
{
	/*
	//SingletonPattern* s1 = new SingletonPattern;
	//SingletonPattern* s2 = new SingletonPattern;
	//希望定义的两个对象是一模一样的 ------- 单例
	//方法：让构造函数私有化，这样创建的所有对象都是一样的了，因为我们不能显示调用构造函数
	//既然构造函数私有化了（我们不希望显示调用构造函数），那么就不能使用new来创建对象了

	SingletonPattern* s1 = SingletonPattern::get_single(); //在get_single中会new一个对象
	SingletonPattern* s2 = SingletonPattern::get_single(); //因为创建s1的时候已经new了一个对象，
														   //为保证单例，不再重新new，而是直接把new好的对象返回出来
	if (s1 == s2)
	{
		cout << "单例" << endl;
	}
	else
	{
		cout << "不是单例" << endl;
	}
	*/

	/*
typedef void     (__cdecl*   _beginthread_proc_type  )(void*);
typedef unsigned (__stdcall* _beginthreadex_proc_type)(void*);

_ACRTIMP uintptr_t __cdecl _beginthread(
	_In_     _beginthread_proc_type _StartAddress,
	_In_     unsigned               _StackSize,
	_In_opt_ void*                  _ArgList
);
	*/
	int i = 0, ThreadNum = 3;
	//uintptr_t h_thread[3];
	HANDLE h_thread[3];

	for (i = 0; i < ThreadNum; i++)
	{
		h_thread[i] = (HANDLE)_beginthread(thread_func1, 0, NULL);
		/*主进程消失，在主进程中创建的线程都会消息，因为线程的内存四区依附于进程的内存四区
		*主进程中创建的其他子进程不会消失，因为每个进程有自己的内存四区，每个进程有自己的运行空间，
		*这时候，这些子进程没有父进程，操作系统会把这些进程给0号进程管理
		*/
	}

	for (i = 0; i < ThreadNum; i++)
	{
		WaitForSingleObject(h_thread[i], INFINITE); //windows 下的等待
		//thread_join  //Linux 下的等待函数
		//等待子线程结束，如果不等待子线程结束主进程就死掉的话，子线程也会随之死掉，所以主进程挂起等待
	}

	cout << "子线程已结束" << endl;

	system("pause");
	return 0;
}