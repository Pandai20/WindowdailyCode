#include <iostream>
using namespace std;
#pragma pack(2)
struct example1
{
    int sd;
    char a;
    long b;  //long是4字节
    double ac;
};
struct example2 {
    char c;
    example1 struct1;
    short e;
};
union U1
{
    char a[9];
    int b;
    example1 ad;
    double c;
};
struct MyStruct {
    char a[9];
    int b;
    double c;
};
int main(int argc, char* argv[])
{
    example2 struct2;
    cout << sizeof(example1) << endl;
    cout << sizeof(example2) << endl;
    cout << (unsigned int)(&struct2.struct1) - (unsigned int)(&struct2) << endl;

    cout << "union U1:" << sizeof(U1) << endl;
    cout << "MyStruct U2:" << sizeof(MyStruct) << endl;

    return 0;
}