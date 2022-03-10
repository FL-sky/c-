#include <bits/stdc++.h>
using namespace std;

////https://zhuanlan.zhihu.com/p/335994370
//һ�Ķ���C++��ֵ���ú�std::move

// #### ��2����ֵ���ú���ֵ����

// ��Ҫ�õ�һ������ֵ������Ҫ�õ���ֵ���õ�������`T &&`������ `T` �����͡���ֵ���õ������������ʱֵ���������ڵ����ӳ���ֻҪ���������ţ���ô����ֵ��������

// C++11 �ṩ�� `std::move` �����������ֵ������������ת��Ϊ��ֵ�����������Ǿ��ܹ�����Ļ��һ����ֵ��ʱ�������磺

void reference(std::string &str)
{
    std::cout << "��ֵ" << std::endl;
}
void reference(std::string &&str)
{
    std::cout << "��ֵ" << std::endl;
}

int main()
{
    std::string lv1 = "string,"; // lv1 ��һ����ֵ
    //std::string &&r1 = s1;                   // �Ƿ�, s1 ��ȫ����������û������
    //string &&ts = lv1;                       // �Ƿ�, �޷�����ֵ���ð󶨵���ֵC/C++(1768) std::string lv1 lv1 ��һ����ֵ
    std::string &&rv1 = std::move(lv1);        // �Ϸ�, std::move ���Խ���ֵת��Ϊ��ֵ
    std::cout << "rv1 = " << rv1 << std::endl; // string,

    const std::string &lv2 = lv1 + lv1; // �Ϸ�, ������ֵ�����ܹ��ӳ���ʱ��������������
    // lv2 += "Test";                   // �Ƿ�, ���õ���ֵ�޷����޸�
    std::cout << "lv2 = " << lv2 << std::endl; // string,string

    std::string &&rv2 = lv1 + lv2;             // �Ϸ�, ��ֵ�����ӳ���ʱ�������������
    rv2 += "string";                           // �Ϸ�, �ǳ��������ܹ��޸���ʱ����
    std::cout << "rv2 = " << rv2 << std::endl; // string,string,string,
    int a = 1, b = 2;
    const int &x = a + b;
    //int &y = a + b; //���Ϸ����ǳ������õĳ�ʼֵ����Ϊ��ֵ
    reference(rv2); // �����ֵ

    return 0;
}