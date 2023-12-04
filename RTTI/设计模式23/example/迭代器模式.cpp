#include <iostream>
using namespace std;

class Iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool is_done() = 0;
	virtual int current_item() = 0;
};

class Aggregate
{
public:
	virtual Iterator* create_iterator() = 0;
	virtual int get_item(int index) = 0;
	virtual int get_size() = 0;
}; 

class IntIterator : public Iterator
{
private:
	Aggregate* age;
	int index;
public:
	IntIterator(Aggregate* age) //迭代器应该持有一个创建迭代器的容器的引用，这样才能通过迭代器访问容器
	{							//谁创建迭代器就把谁的引用传递给迭代器
		this->age = age;
		this->index = 0;
	}
	virtual void first()
	{
		index = 0;
	}
	virtual void next()
	{
		if (index < age->get_size())
		{
			index++;
		}
	}
	virtual bool is_done()
	{
		if (index == age->get_size())
		{
			return true;
		}
		return false;
	}
	virtual int current_item()
	{
		return age->get_item(index);
	}
};

class IntArray : Aggregate
{
private:
	int size;
	int* array;
public:
	IntArray(int size)
	{
		this->size = size;
		array = new int[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = i + 1;
		}
	}
	~IntArray()
	{
		if (array != NULL)
		{
			delete array;
			array = NULL;
		}
		this->size = 0;
	}
	virtual Iterator* create_iterator()
	{
		return new IntIterator(this); //把自己的引用传给迭代器
	}
	virtual int get_item(int index)
	{
		return array[index];
	}
	virtual int get_size()
	{
		return this->size;
	}
};

int main()
{
	Iterator* it = NULL;
	IntArray* array = NULL;

	array = new IntArray(10);
	it = array->create_iterator();
	cout << "遍历数组：";
	for (; !(it->is_done()); it->next())
	{
		cout << it->current_item() << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}