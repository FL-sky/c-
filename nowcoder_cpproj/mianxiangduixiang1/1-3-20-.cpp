#include <iostream>

using namespace std;

class X
{
protected:
    int m_i;
};

class Y : virtual public X
{
};

class Z : virtual public X
{
};

class A : public Y, public Z
{
};

int main(void)
{
    cout << "X size: " << sizeof(X) << endl;
    cout << "Y size: " << sizeof(Y) << endl;
    cout << "Z size: " << sizeof(Z) << endl;
    cout << "A size: " << sizeof(A) << endl;

    return 0;
}

/// https://blog.csdn.net/m0_38014304/article/details/84286266