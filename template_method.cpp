#include <iostream>

/*
策略模式：组合
模板方法：继承
*/

class CaffeineBeverageWithHook
{
public:
    void prepareRecipe()
    {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments())
        {
            addCondiments();
        }
    }

    void boilWater()
    {
        std::cout << "Boiling water" << std::endl;
    }

    virtual void brew() 
    {
        std::cout << "Brew" << std::endl;
    }

    void pourInCup()
    {
        std::cout << "Pouring into cup" << std::endl;
    }

    virtual void addCondiments() 
    {
        std::cout << "Add condiments" << std::endl;
    }

    virtual bool customerWantsCondiments()
    {
        return true;
    }
};


class CoffeeWithHook : public CaffeineBeverageWithHook
{
public:
    void brew()
    {
        std::cout << "Dripping Coffee through filter" << std::endl;
    }

    void addCondiments()
    {
        std::cout << "Add Sugar and Milk" << std::endl;
    }

    bool customerWantsCondiments()
    {
        std::string answer;
        std::cout << "Would you like milk and sugar with your coffee (y/n)? ";
        std::cin >> answer;

        if (answer.find('y') == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};


class TeaWithHook : public CaffeineBeverageWithHook
{
public:
    void brew()
    {
        std::cout << "Steeping the tea" << std::endl;
    }

    void addCondiments()
    {
        std::cout << "Adding Lemon" << std::endl;
    }

    bool customerWantsCondiments()
    {
        std::string answer;
        std::cout << "Would you like lemon with your tea (y/n)? ";
        std::cin >> answer;

        if (answer.find('y') == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};


int main(int argc, char const *argv[])
{
    CaffeineBeverageWithHook* coffee = new CoffeeWithHook;
    coffee->prepareRecipe();
    CaffeineBeverageWithHook* tea = new TeaWithHook;
    tea->prepareRecipe();

    return 0;
}
