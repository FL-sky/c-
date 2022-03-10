#include <iostream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

int num_gouzao;
class B
{
public:
    B()
    {
        p = NULL;
        len = 0;
        num_gouzao++;
        cout << "B()" << endl;
    }
    void print()
    {
        cout << "print" << endl;
        p = NULL;
        len = 0;
    }
    B(const B &b) //push_back调用
    {
        cout << "copy B()" << endl;
        if (p)
        {
            len = b.len;
            p = new char[len + 1];
            memcpy(p, b.p, len);
            p[len] = 0;
            //delete b.p;
        }
    }
    B(const B &&)
    {
    }
    ~B()
    {
        cout << "~B()" << endl;
        if (p)
        {
            delete[] p;
            p = NULL;
            len = 0;
        }
    }
    char *p;
    int len;
};

void t1()
{
    printf("%s--------START--------\n", __func__);
    list<B> ls;
    B b;
    char str[] = "hello t1";
    b.p = new char[sizeof(str) + 1];
    strcpy(b.p, str);
    b.len = strlen(b.p);
    for (int i = 0; i < 3; i++)
        ls.push_back(b);
    printf("num_gouzao=%d\n", num_gouzao);
    printf("%s--------END--------\n", __func__);
}

void t2()
{
    printf("%s--------START--------\n", __func__);
    vector<B> vec;
    B b;
    char str[] = "hello t1";
    b.p = new char[sizeof(str) + 1];
    strcpy(b.p, str);
    b.len = strlen(b.p);
    for (int i = 0; i < 3; i++)
        vec.push_back(b);
    printf("num_gouzao=%d\n", num_gouzao);
    printf("%s--------END--------\n", __func__);
}
int main()
{
    printf("%s--------START--------\n", __func__);
    t1();
    t2();
    printf("%s--------END--------\n", __func__);
    return 0;
}