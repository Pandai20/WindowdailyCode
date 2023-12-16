#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Number
{
    void operator()(int a,string b)
    {
        cout << "here is operator create" << endl;
        id = a;
        name = b;
    };

    Number(Number&& num):id(num.id),name(num.name)
    {
        cout << "here's create" << endl;
    };

    Number(int a, string b) :id(a), name(b)
    {
        cout << "构造函数" << endl;
    };

    int id;
    string name;
};



int main()
{
    vector<Number> m_myClass;
    m_myClass.emplace_back(Number(3, "panda"));
    std::cout << (m_myClass.empty() ? "ture" : "false") << endl;
    cout << m_myClass[0].id << endl;
    cout << m_myClass[0].name << endl;

    vector<Number> m_twoClass;
    m_twoClass.push_back(Number(4, "fuck"));
    std::cout << (m_twoClass.empty() ? "ture" : "false") << endl;
    cout << m_twoClass[0].id << endl;
    cout << m_twoClass[0].name << endl;

    Number m_example(6, "wilson");
    m_twoClass.push_back(move(m_example));
    cout << m_twoClass[1].id << endl;
    cout << m_twoClass[1].name << endl;
    cout << m_example.id << endl;

}
