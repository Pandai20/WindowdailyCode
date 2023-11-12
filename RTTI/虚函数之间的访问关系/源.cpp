#include <iostream>

class Parent {
public:
    virtual void a() {
        std::cout << "Parent::a()" << std::endl;
        b();
    }

    virtual void b() {
        std::cout << "Parent::b()" << std::endl;
    }
};

class Child : public Parent {
public:
    void a() override {
        std::cout << "Child::a()" << std::endl;
        b();
    }
    virtual void b() {
        std::cout << "Child::b()" << std::endl;
    }
};

int main() {
    Parent* obj = new Child(); // ʹ�ø���ָ��ָ���������

    ((Parent*) obj)->a();
    delete obj;





    return 0;
}
