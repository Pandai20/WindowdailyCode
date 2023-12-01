#include <iostream>
#include <cstring>
#include <string>
class Name
{
public:
	~Name();
	//同时定义有参构造函数和默认函数
	Name(const char* num= "");
	Name(const Name& m_name);//非引用类型会造成拷贝构造无穷递归
	//打印参数
	inline void printf_name()
	{
		std::cout << "name:" << name << std::endl;
	}
private:
	char* name;
};

//有参构造函数
Name::Name(const char* tmp_name)
{
	std::cout << "有参构造函数"<< std::endl;
	if (tmp_name  == nullptr)
	{
		name = new char[1];
		strcpy(name, '\0');
	}
	else
	{
		name = new char[strlen(tmp_name) + 1];
		memcpy(name, tmp_name, strlen(tmp_name) + 1);
	}
}

//拷贝构造函数
Name::Name(const Name& m_name)
{
	
}

Name::~Name()
{
	delete[] name;
}

int main()
{
	Name name="pand";
	name.printf_name();





	return 0;
}