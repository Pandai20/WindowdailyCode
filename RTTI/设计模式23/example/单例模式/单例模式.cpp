#include <iostream>
using namespace std;

class SingletonPattern
{
private:
	SingletonPattern()
	{
		//Sleep(1000); //加入这里有一个延迟函数，第一个线程在new的时候，如果延时还没结束
					   //第二个线程又过来new一个对象，这时候因为第一个对象还没有new出来
					   //所以single还是NULL，这样又会进入构造函数，最后总共new了两个对象
						//这样返回的两个对象是两次new出来的，就不是单例模式了
		cout << "私有的构造函数" << endl;
	}
public: //构造函数被私有化了，所以应该提供一个对外访问的方法，来创建对象
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
private: //static 成员，类定义的所有对象共有static成员
	static SingletonPattern* single; //指针，不能是变量，否则编译器不知道如何分配内存
};

SingletonPattern* SingletonPattern::single = NULL; //告诉编译器分配内存

int main() 
{
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

	system("pause");
	return 0;
}