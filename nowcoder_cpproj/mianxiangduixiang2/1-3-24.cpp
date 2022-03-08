// 1.3.24 说说 C++ 中什么是菱形继承问题，如何解决
// 参考回答

// 1.下面的图表可以用来解释菱形继承问题。1-3-24_菱形继承.png

// 假设我们有类B和类C，它们都继承了相同的类A。另外我们还有类D，类D通过多重继承机制继承了类B和类C。因为上述图表的形状类似于菱形，因此这个问题被形象地称为菱形继承问题。
// 现在，我们将上面的图表翻译成具体的代码：

/*  *Animal类对应于图表的类A* */
class Animal //{ /* ... */ } // 基类
{
    int weight;

public:
    int getWeight() { return weight; }
};
class Tiger : public Animal
{ /* ... */
};
class Lion : public Animal
{ /* ... */
};
class Liger : public Tiger, public Lion
{ /* ... */
};

// 在上面的代码中，我们给出了一个具体的菱形继承问题例子。Animal类对应于最顶层类（图表中的A），Tiger和Lion分别对应于图表的B和C，Liger类（狮虎兽，即老虎和狮子的杂交种)对应于D。

// 现在，问题是如果我们有这种继承结构会出现什么样的问题。

// 看看下面的代码后再来回答问题吧。

int main()
{
    Liger lg;                    /*编译错误，下面的代码不会被任何C++编译器通过 */
    int weight = lg.getWeight(); ///"Liger::getWeight" 不明确C/C++(266)
    // int weight = lg.Tiger::getWeight();
}

// 在我们的继承结构中，我们可以看出Tiger和Lion类都继承自Animal基类。所以问题是：因为Liger多重继承了Tiger和Lion类，
// 因此Liger类会有两份Animal类的成员（数据和方法），Liger对象"lg"会包含Animal基类的两个子对象。

// 所以，你会问Liger对象有两个Animal基类的子对象会出现什么问题？再看看上面的代码-调用"lg.getWeight()"将会导致一个编译错误。
// 这是因为编译器并不知道是调用Tiger类的getWeight()还是调用Lion类的getWeight()。所以，调用getWeight方法是不明确的，因此不能通过编译。

// 1.我们给出了菱形继承问题的解释，但是现在我们要给出一个菱形继承问题的解决方案。
// 如果Lion类和Tiger类在分别继承Animal类时都用virtual来标注，对于每一个Liger对象，C++会保证只有一个Animal类的子对象会被创建。看看下面的代码:

// class Tiger : virtual public Animal
// { /* ... */
// };
// class Lion : virtual public Animal
// { /* ... */
// };

// // 你可以看出唯一的变化就是我们在类Tiger和类Lion的声明中增加了"virtual"关键字。现在类Liger对象将会只有一个Animal子对象，下面的代码编译正常:

// int main()
// {
//     Liger lg; /*既然我们已经在Tiger和Lion类的定义中声明了"virtual"关键字，于是下面的代码编译OK */
//     int weight = lg.getWeight();
// }