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
    //bind绑定函数bindfunction
    auto b = std::bind(&bindfunction<int>, std::placeholders::_1, std::placeholders::_2); //使用占位符_1（表示函数的第一个入参）;_2
    std::cout << "bind_function value: " << b(6, 7) << std::endl;

    //bind绑定函数function
    auto b1 = std::bind(&function, std::placeholders::_1, std::placeholders::_2);
    std::cout << "function value: " << b1(111, 7) << std::endl;
    //------------------------------------------------------------------------------//
    //bind绑定函数对象 ---需要重载operate()
    struct MyStruct struct1 {3 , 2};

    auto c = std::bind(struct1);
    std::cout << "function_obj value: " << c() << std::endl;

    auto c1 = std::bind(struct1, std::placeholders::_1, std::placeholders::_2);
    std::cout << "function_obj value: " << c1(2, 9) << std::endl;
    //------------------------------------------------------------------------------//
    //bind绑定成员函数
    /*
        1._1必须是object的地址。有一个this指针
    */
    struct MyStruct struct2;
    auto d = std::bind(&MyStruct::Fplus, struct2,7,5); //没有占位符调用函数的时候就不加参数
    std::cout << "function_number value: " << d() << std::endl;

    auto d1 = std::bind(&MyStruct::Fplus, std::placeholders::_1, 6, 8); //有占位符就加
    std::cout << "function_number value: " << d1(struct2) << std::endl;//d1(struct2) == d1(&struct2)加不加地址好像都一样

    auto d2 = std::bind(&MyStruct::Fplus,6, 8);
    //d2();  _1(第一个参数)必须是object的地址
    
    //------------------------------------------------------------------------------//
    //bind绑定成员变量
    struct MyStruct struct3 {8,88};
    auto e = std::bind(&MyStruct::b, struct3); //没有占位符就不加
    std::cout << "number_date value: " << e() << std::endl;
    auto e1 = std::bind(&MyStruct::a, std::placeholders::_1); //没有占位符就不加
    std::cout << "number_date value: " << e1(&struct3) << std::endl;
    //------------------------------------------------------------------------------//



    //                  std::function

    void  add_int(int a, int b) {
        return a + b;
    };


    std::function<int,int> = add_int;








    return 0;
}