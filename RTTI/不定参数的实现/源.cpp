#include <iostream>

void print()
{
}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n'; // print first argument
   
    print(args...); // call print() for remaining arguments
}
int main()
{
    print(7.5, "hello", 5);



    return 0;
}