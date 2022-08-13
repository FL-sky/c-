// 1.3.31 说说什么是虚基类，可否被实例化？
// 参考回答

// 在被继承的类前面加上virtual关键字，这时被继承的类称为虚基类，代码如下：

class A
{
};
class B1 : public virtual A
{
};
class B2 : public virtual A
{
};
class D : public B1, public B2
{
};
// 虚继承的类可以被实例化，举例如下：

class Animal
{
    int weight;

public:
    int getWeight() { return weight; }
};
class Tiger : virtual public Animal
{ /* ... */
};
class Lion : virtual public Animal
{ /* ... */
};
class Liger : public Tiger, public Lion
{ /* ... */
};

int main()
{
    Liger lg;

    /*既然我们已经在Tiger和Lion类的定义中声明了"virtual"关键字，于是下面的代码编译OK */
    int weight = lg.getWeight();
}