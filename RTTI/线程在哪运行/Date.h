#pragma once
#include<iostream>
#include<thread>
#include<map>
#include<memory>
class MyClass
{
public:
	MyClass();
	~MyClass();
	static MyClass& getInstance();
	virtual void setCallback();
private:
	static MyClass pand;
	std::map<std::string, std::shared_ptr<MyClass*>> dateMap;
};

MyClass& MyClass::getInstance()
{
	return pand;

}
void MyClass::setCallback()
{
	std::thread(setCallback);

}