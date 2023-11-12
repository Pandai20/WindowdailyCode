#include <iostream>
#include <typeinfo>

class Base { virtual void dummy() {} };
class Derived : public Base { /* ... */ };

int main1() {
    Base* base_ptr = new Derived;
    Base number;
    // Using typeid to get the type of the object
    std::cout << "Type: " << typeid(*base_ptr).name() << '\n';
    std::cout << "Type2: " << typeid(number).name() << '\n';
    delete base_ptr;
    return 0;
}