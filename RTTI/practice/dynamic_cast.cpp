#include <iostream>
#include <typeinfo>
class Base { virtual void dummy() {} };
class Derived1 : public Base { /* ... */ };
class Derived2 : public Base { /* ... */ };

//dynamic_cast是一个类型转换运算符
//它执行运行时类型检查并安全地将基指针或引用向下转换为派生指针或引用

int main() {
    Base* base_ptr = new Derived1;

    // Using dynamic_cast to safely downcast the pointer
    Derived1* derived1_ptr = dynamic_cast<Derived1*>(base_ptr);
    if (derived1_ptr) {
        std::cout << "Downcast to Derived1 successful\n";
    }
    else {
        std::cout << "Downcast to Derived1 failed\n";
    }

    std::cout <<typeid(*base_ptr).name()<<"  \n";
    
    Derived2* derived2_ptr = dynamic_cast<Derived2*>(base_ptr);
    if (derived2_ptr) {
        std::cout << "Downcast to Derived2 successful\n";
    }
    else {
        std::cout << "Downcast to Derived2 failed\n";
        
    }
    std::cout << typeid(*base_ptr).name() << "  \n";


    delete base_ptr;
    return 0;
}