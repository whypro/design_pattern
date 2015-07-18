#include <iostream>
#include <cstring>


class Beverage 
{
protected:
    std::string description;
public:
    virtual std::string getDescription()
    {
        return description;
    }

    virtual double cost() = 0;

};

class HouseBlend : public Beverage
{
public:
    HouseBlend()
    {
        description = "HouseBlend";
    }
    double cost()
    {
        return 0.89;
    }
};

class DarkRoast : public Beverage
{
public:
    DarkRoast()
    {
        description = "DarkRoast";
    }
    double cost()
    {
        return 0.99;
    }
};

class Decaf : public Beverage
{
public:
    Decaf()
    {
        description = "Decaf";
    }
    double cost()
    {
        return 1.05;
    }
};

class Espresso : public Beverage
{
public:
    Espresso()
    {
        description = "Espresso";
    }
    double cost()
    {
        return 1.99;
    }
};

class CondimentDecorator : public Beverage
{

};

class Mocha : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Mocha(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    std::string getDescription()
    {
        return beverage->getDescription() + ", Mocha";
    }

    double cost()
    {
        return beverage->cost() + 0.20;
    }
    
};


class Soy : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Soy(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    std::string getDescription()
    {
        return beverage->getDescription() + ", Soy";
    }

    double cost()
    {
        return beverage->cost() + 0.15;
    }
    
};


class Whip : public CondimentDecorator
{
private:
    Beverage* beverage;

public:
    Whip(Beverage* beverage)
    {
        this->beverage = beverage;
    }

    std::string getDescription()
    {
        return beverage->getDescription() + ", Whip";
    }

    double cost()
    {
        return beverage->cost() + 0.10;
    }
    
};


int main(int argc, char const *argv[])
{
    Beverage* beverage = new Espresso;
    std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

    Beverage* beverage2 = new DarkRoast;
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout << beverage2->getDescription() << " $" << beverage2->cost() << std::endl;

    Beverage* beverage3 = new HouseBlend;
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new Whip(beverage3);
    std::cout << beverage3->getDescription() << " $" << beverage3->cost() << std::endl;

    return 0;
}
