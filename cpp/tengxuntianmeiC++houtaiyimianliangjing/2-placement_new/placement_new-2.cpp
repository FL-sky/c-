#include <iostream>
using namespace std;

class B
{
public:
    B()
    {
        cout << "B's constructor" << endl;
    }

    ~B()
    {
        cout << "B's destructor" << endl;
    }

    void SetNum(int n)
    {
        num = n;
    }

    int GetNum()
    {
        return num;
    }

private:
    int num;
};

int main()
{
    int szb = sizeof(B);
    char *mem = new char[10 * sizeof(B)];
    cout << (void *)mem << endl;
    B *p = new (mem) B;
    cout << p << endl;
    p->SetNum(280);
    cout << p->GetNum() << endl;
    for (int i = 0; i < 10 * sizeof(B); i++)
        printf("%4d", mem[i]);
    puts("");
    p->~B();
    delete[] mem;
    return 0;
}