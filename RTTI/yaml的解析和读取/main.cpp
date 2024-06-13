#include<iostream>
#include<string>

#include "yaml-cpp/yaml.h"
using namespace std;
int main()
{
	YAML::Node config;
	try
	{
		config = YAML::LoadFile(".\\config.yml");
	}
	catch (const std::exception&)
	{
		std::cout << "read error" << std::endl;

	}

#define OUT_TYPY(x,y) cout<<x<<y<<endl;

	cout << "node type: " << config.Type()<<endl;
	OUT_TYPY("name type: ", config["name"].Type());

	cout << "age type: " << config["age"].Type() << endl;

	cout << "spouse type: " << config["spouse"].Type() << endl;
	cout << "spouse->name type: " << config["spouse"]["name"].Type() << endl;


	cout << "children type: " << config["children"].Type() << endl;

	cout << "children->name type: " << config["children"][0]["name"].Type() << endl;
	cout << "children->name type: " << config["children"]["age"].Type() << endl;

	//��ȡֵ
	string name = config["name"].as<string>();
	cout << "��ȡname��ֵ�ǣ� " <<name<< endl;
	//��ȡ��ֵ
	string name1 = config["name11"].as<string>();
	cout << "��ȡname11��ֵ�ǣ� " << name1<< endl;
	//��ȡ��ֵ������
	try
	{
		string name2 = config["name2"].as<string>();
		cout << "��ȡname2��ֵ�ǣ� " << name2 << endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "�������������: " << typeid(ex).name() << std::endl;
	}
	

	return 0;
}
