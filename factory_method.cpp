#include <iostream>
#include <vector>
#include <string>

/*
变量不可以持有具体类的引用
不要让类派生自具体类
不要覆盖基类中已实现的方法
*/

class Pizza 
{
protected:
    std::string name;
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;
public:
    virtual void prepare() 
    {
        std::cout << "Preparing " << name << std::endl;
        std::cout << "Tossing dough... " << std::endl;
        std::cout << "Adding sauce... " << std::endl;
        std::cout << "Adding toppings: " << std::endl;
        for (std::vector<std::string>::iterator it = toppings.begin(); it != toppings.end(); it++)
        {
            std::cout << "    " << *it << std::endl;
        }

    }
    virtual void bake() 
    {
        std::cout << "Bake for 25 minutes at 350" << std::endl;
    }
    virtual void cut() 
    {
        std::cout << "Cutting the pizza into diagonal slices" << std::endl;
    }
    virtual void box() 
    {
        std::cout << "Place pizza in official PizzaStore box" << std::endl;
    }
    virtual std::string getName()
    {
        return name;
    }
};

class NYStyleCheesePizza : public Pizza 
{
public:
    NYStyleCheesePizza()
    {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";

        toppings.push_back("Grated Reggiano Cheese");
    }
};

class NYStylePepperoniPizza : public Pizza 
{

};

class NYStyleClamPizza : public Pizza 
{

};

class NYStyleVeggiePizza : public Pizza 
{

};


class ChicagoStyleCheesePizza : public Pizza 
{
public:
    ChicagoStyleCheesePizza()
    {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";

        toppings.push_back("Shredded Mozzarella Cheese");
    }

    void cut()
    {
        std::cout << "Cutting the pizza into square slices" << std::endl;
    }
};

class ChicagoStylePepperoniPizza : public Pizza 
{

};

class ChicagoStyleClamPizza : public Pizza 
{

};

class ChicagoStyleVeggiePizza : public Pizza 
{

};


class PizzaStore
{
public:
    Pizza* orderPizza(std::string type)
    {
        Pizza* pizza = createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

    virtual Pizza* createPizza(std::string type) = 0;
};

class NYStylePizzaStore : public PizzaStore
{
public:
    Pizza* createPizza(std::string type)
    {
        Pizza* pizza = NULL;
        if (type == "cheese")
        {
            pizza = new NYStyleCheesePizza;
        }
        else if (type == "pepperoni")
        {
            pizza = new NYStylePepperoniPizza;
        }
        else if (type == "clam")
        {
            pizza = new NYStyleClamPizza;
        }
        else if (type == "veggie")
        {
            pizza = new NYStyleVeggiePizza;
        }

        return pizza;
    }
};


class ChicagoStylePizzaStore : public PizzaStore
{
public:
    Pizza* createPizza(std::string type)
    {
        Pizza* pizza = NULL;
        if (type == "cheese")
        {
            pizza = new ChicagoStyleCheesePizza;
        }
        else if (type == "pepperoni")
        {
            pizza = new ChicagoStylePepperoniPizza;
        }
        else if (type == "clam")
        {
            pizza = new ChicagoStyleClamPizza;
        }
        else if (type == "veggie")
        {
            pizza = new ChicagoStyleVeggiePizza;
        }

        return pizza;
    }
};


int main(int argc, char const *argv[])
{
    PizzaStore* nyps = new NYStylePizzaStore;
    PizzaStore* csps = new ChicagoStylePizzaStore;

    Pizza* pizza = nyps->orderPizza("cheese");

    pizza = csps->orderPizza("cheese");

    return 0;
}
