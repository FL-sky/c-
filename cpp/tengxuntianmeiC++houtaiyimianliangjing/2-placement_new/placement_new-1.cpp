/// https://blog.csdn.net/linuxheik/article/details/80449059

#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A's constructor" << endl;
        n2 = 100;
    }

    ~A()
    {
        cout << "A's destructor" << endl;
    }

    void show()
    {
        cout << "num:" << num << endl;
    }

private:
    int num;
    int n2;
};

int main()
{
    char mem[100];
    for (int i = 0; i < 100; i++)
    {
        mem[i] = 'A' + i % 52;
    }
    cout << (void *)mem << endl;
    A *p = new (mem) A;
    cout << p << endl;
    p->show();
    cout << "mem[4]=" << mem[4] << endl;
    //
    char *q = (char *)p;
    for (int i = 0; i < 100; i++)
    {
        putchar(q[i]);
    }
    //
    p->~A();

    return 0;
}