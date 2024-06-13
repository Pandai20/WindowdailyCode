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

	//读取值
	string name = config["name"].as<string>();
	cout << "读取name的值是： " <<name<< endl;
	//读取空值
	string name1 = config["name11"].as<string>();
	cout << "读取name11的值是： " << name1<< endl;
	//读取的值不存在
	try
	{
		string name2 = config["name2"].as<string>();
		cout << "读取name2的值是： " << name2 << endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "捕获错误类型是: " << typeid(ex).name() << std::endl;
	}
	

	return 0;
}
