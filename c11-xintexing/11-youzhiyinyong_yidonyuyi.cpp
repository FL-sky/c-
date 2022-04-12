#include <bits/stdc++.h>
using namespace std;

// #### ��3���ƶ�����

// ��ͳ C++ ͨ���������캯���͸�ֵ������Ϊ���������˿���/���Ƶĸ����Ϊ��ʵ�ֶ���Դ���ƶ������������߱���ʹ���ȸ��ơ��������ķ�ʽ���������Ҫ�Լ�ʵ���ƶ�����Ľӿڡ����룬��ҵ�ʱ���ǰѼ���Ķ���ֱ�Ӱᵽ�¼�ȥ�������ǽ����ж�������һ�ݣ������ٷŵ��¼ҡ��ٰ�ԭ���Ķ���ȫ�����٣����Ƿǳ��������һ�����顣

// ��ͳ�� C++ û�����֡��ƶ����͡��������ĸ������˴����������ƶ����˷�ʱ��Ϳռ䡣��ֵ���õĳ���ǡ�þͽ��������������Ļ������⣬���磺

int idx;
#include <iostream>
class A
{
public:
    int *pointer;
    int id;
    A() : pointer(new int(id = ++idx))
    {
        // id = ++idx;
        std::cout << "����" << pointer << std::endl;
    }
    // ������Ķ��󿽱�
    A(A &a) : pointer(new int(*a.pointer))
    {
        std::cout << "����" << pointer << std::endl;
    }

    A(A &&a) : pointer(a.pointer)
    {
        a.pointer = nullptr;
        std::cout << "�ƶ�" << pointer << std::endl;
    }

    ~A()
    {
        std::cout << "����" << pointer << std::endl;
        delete pointer;
    }
};
// ��ֹ�������Ż�
A return_rvalue(bool test)
{
    A a, b;
    if (test)
        return a;
    else
        return b;
}
int main()
{
    {
        // A c;
        // A obj = c;
        A obj = return_rvalue(false);
        std::cout << "obj:" << std::endl;
        std::cout << obj.pointer << std::endl;
        std::cout << *obj.pointer << std::endl;
    }

    // ������Ĵ����У�

    // 1. ���Ȼ��� `return_rvalue` �ڲ��������� `A` �������ǻ���������캯���������
    // 2. �������غ󣬲���һ������ֵ���� `A` ���ƶ����죨`A(A&&)`�����ã��Ӷ��ӳ��������ڣ����������ֵ�е�ָ���õ������浽�� `obj` �У�������ֵ��ָ�뱻����Ϊ `nullptr`����ֹ������ڴ��������١�

    // �Ӷ�������������Ŀ������죬��ǿ�����ܡ����������漰��׼������ӣ�

    {

        std::string str = "Hello world.";
        std::vector<std::string> v;

        // ��ʹ�� push_back(const T&), ������������Ϊ
        v.push_back(str);
        // ����� "str: Hello world."
        std::cout << "str: " << str << std::endl;

        // ��ʹ�� push_back(const T&&), ������ֿ�����Ϊ
        // �������ַ����ᱻ�ƶ��� vector �У�������ʱ�� std::move ���������ٿ������ֵĿ���
        // �ⲽ������, str �е�ֵ���Ϊ��
        v.push_back(std::move(str));
        // ����� "str: "
        std::cout << "str: " << str << std::endl;
    }
    return 0;
}