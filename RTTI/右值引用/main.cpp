#include <iostream>
#include <cstring>
#include <string>
class Name
{
public:
	~Name();
	//ͬʱ�����вι��캯����Ĭ�Ϻ���
	Name(const char* num= "");
	Name(const Name& m_name);//���������ͻ���ɿ�����������ݹ�
	//��ӡ����
	inline void printf_name()
	{
		std::cout << "name:" << name << std::endl;
	}
private:
	char* name;
};

//�вι��캯��
Name::Name(const char* tmp_name)
{
	std::cout << "�вι��캯��"<< std::endl;
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

//�������캯��
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