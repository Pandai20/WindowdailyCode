#include<iostream>
#include<functional>
template <typename T>
T bindfunction(T a, T b)
{
    return a * b;
}
int function(int a, int b)
{
    return a * b;
}


struct MyStruct
{
    int a, b;
    int operator()() {
        return a * b;
    };
    int operator()(int a ,int b) {
        return a * b;
    };

    int Fplus(int a, int b) {
        return a + b;
    };
};



int main()
{
    //bind�󶨺���bindfunction
    auto b = std::bind(&bindfunction<int>, std::placeholders::_1, std::placeholders::_2); //ʹ��ռλ��_1����ʾ�����ĵ�һ����Σ�;_2
    std::cout << "bind_function value: " << b(6, 7) << std::endl;

    //bind�󶨺���function
    auto b1 = std::bind(&function, std::placeholders::_1, std::placeholders::_2);
    std::cout << "function value: " << b1(111, 7) << std::endl;
    //------------------------------------------------------------------------------//
    //bind�󶨺������� ---��Ҫ����operate()
    struct MyStruct struct1 {3 , 2};

    auto c = std::bind(struct1);
    std::cout << "function_obj value: " << c() << std::endl;

    auto c1 = std::bind(struct1, std::placeholders::_1, std::placeholders::_2);
    std::cout << "function_obj value: " << c1(2, 9) << std::endl;
    //------------------------------------------------------------------------------//
    //bind�󶨳�Ա����
    /*
        1._1������object�ĵ�ַ����һ��thisָ��
    */
    struct MyStruct struct2;
    auto d = std::bind(&MyStruct::Fplus, struct2,7,5); //û��ռλ�����ú�����ʱ��Ͳ��Ӳ���
    std::cout << "function_number value: " << d() << std::endl;

    auto d1 = std::bind(&MyStruct::Fplus, std::placeholders::_1, 6, 8); //��ռλ���ͼ�
    std::cout << "function_number value: " << d1(struct2) << std::endl;//d1(struct2) == d1(&struct2)�Ӳ��ӵ�ַ����һ��

    auto d2 = std::bind(&MyStruct::Fplus,6, 8);
    //d2();  _1(��һ������)������object�ĵ�ַ
    
    //------------------------------------------------------------------------------//
    //bind�󶨳�Ա����
    struct MyStruct struct3 {8,88};
    auto e = std::bind(&MyStruct::b, struct3); //û��ռλ���Ͳ���
    std::cout << "number_date value: " << e() << std::endl;
    auto e1 = std::bind(&MyStruct::a, std::placeholders::_1); //û��ռλ���Ͳ���
    std::cout << "number_date value: " << e1(&struct3) << std::endl;
    //------------------------------------------------------------------------------//



    //                  std::function

    void  add_int(int a, int b) {
        return a + b;
    };


    std::function<int,int> = add_int;








    return 0;
}