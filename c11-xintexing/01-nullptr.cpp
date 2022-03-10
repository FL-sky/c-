#include <iostream>

void foo(char *p)
{
    std::cout << "char*" << std::endl;
}
void foo(int n)
{
    std::cout << "int" << std::endl;
}

int main()
{
    char *p = NULL;
    //foo(NULL);///error: call of overloaded 'foo(NULL)' is ambiguous
    foo((char *)(NULL));
    foo(nullptr);
    return 0;
}
