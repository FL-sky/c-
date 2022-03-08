/*  *Animal类对应于图表的类A* */
class Animal //{ /* ... */ } // 基类
{
    int weight;

public:
    int getWeight() { return weight; }
};

// 1.我们给出了菱形继承问题的解释，但是现在我们要给出一个菱形继承问题的解决方案。
// 如果Lion类和Tiger类在分别继承Animal类时都用virtual来标注，对于每一个Liger对象，C++会保证只有一个Animal类的子对象会被创建。看看下面的代码:

class Tiger : virtual public Animal
{ /* ... */
};
class Lion : virtual public Animal
{ /* ... */
};

// 你可以看出唯一的变化就是我们在类Tiger和类Lion的声明中增加了"virtual"关键字。现在类Liger对象将会只有一个Animal子对象，下面的代码编译正常:
class Liger : public Tiger, public Lion
{ /* ... */
};
int main()
{
    Liger lg; /*既然我们已经在Tiger和Lion类的定义中声明了"virtual"关键字，于是下面的代码编译OK */
    int weight = lg.getWeight();
}