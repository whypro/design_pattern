#include <iostream>

class Duck
{
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};


class MallardDuck : public Duck
{
public:
    void quack()
    {
        std::cout << "Quack" << std::endl;
    }

    void fly()
    {
        std::cout << "I'm flying" << std::endl;
    }
};


class Turkey
{
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey
{
public:
    void gobble()
    {
        std::cout << "Gobble gobble" << std::endl;
    }

    void fly()
    {
        std::cout << "I'm flying a short distance" << std::endl;
    }
};


class TurkeyAdapter : public Duck
{
    Turkey* turkey;
public:
    TurkeyAdapter(Turkey* turkey)
    {
        this->turkey = turkey;
    }
    
    void quack()
    {
        turkey->gobble();
    }

    void fly()
    {
        for (int i = 0; i < 5; i++)
        {
            turkey->fly();
        }
    }
};


int main(int argc, char const *argv[])
{
    MallardDuck* duck = new MallardDuck;
    WildTurkey* turkey = new WildTurkey;
    Duck* turkeyAdapter = new TurkeyAdapter(turkey);

    duck->quack();
    duck->fly();

    turkeyAdapter->quack();
    turkeyAdapter->fly();

    return 0;
}
