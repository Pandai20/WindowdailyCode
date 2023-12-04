#include <iostream>
using namespace std;

//Target：客户需要一个TTL电平接口
class TTL
{
public:
	virtual void get_ttl() = 0;
};

//Adaptee：现在只有一个RS232接口
class RS232
{
public:
	void get_rs232()
	{
		cout << "RS232接口" << endl;
	}
};

//Adapter：适配器
class adapter : public TTL
{
private:
	RS232* m_232;
public:
	adapter(RS232* m_232)
	{
		this->m_232 = m_232;
	}
	void adapter232_to_ttl()
	{
		cout << "适配器：将RS232转换为TTL" << endl;
	}
	virtual void get_ttl()
	{
		this->m_232->get_rs232();
		adapter232_to_ttl();
		cout << "ttl电平接口" << endl;
	}
};

int main()
{
	RS232* my232 = NULL;

	adapter* ad = NULL;

	//现有一个RS232电平接口
	my232 = new RS232;
	//需求是TTL接口，所以创建一个适配器
	my232->get_rs232();
	cout << "=========" << endl;
	ad = new adapter(my232);
	ad->get_ttl();

	delete my232;
	delete ad;

	system("pause");
	return 0;
}