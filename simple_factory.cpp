#include <iostream>



class Pizza 
{
public:
    virtual void prepare() {}
    virtual void bake() {}
    virtual void cut() {}
    virtual void box() {}
};

class CheesePizza : public Pizza 
{
public:
    void prepare() 
    {
        std::cout << "prepare cheese" << std::endl;
    }
};

class PepperoniPizza : public Pizza 
{

};

class ClamPizza : public Pizza 
{

};

class VeggiePizza : public Pizza 
{

};

class SimplePizzaFactory
{
public:
    Pizza* createPizza(std::string type)
    {
        Pizza* pizza = NULL;
        if (type == "cheese")
        {
            pizza = new CheesePizza;
        }
        else if (type == "pepperoni")
        {
            pizza = new PepperoniPizza;
        }
        else if (type == "clam")
        {
            pizza = new ClamPizza;
        }
        else if (type == "veggie")
        {
            pizza = new VeggiePizza;
        }

        return pizza;
    }
};

class PizzaStore
{
    SimplePizzaFactory* factory;

public:
    PizzaStore(SimplePizzaFactory* factory)
    {
        this->factory = factory;
    }

    Pizza* orderPizza(std::string type)
    {
        Pizza* pizza = factory->createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};


int main(int argc, char const *argv[])
{
    SimplePizzaFactory spf;
    PizzaStore ps(&spf);
    ps.orderPizza("cheese");

    return 0;
}
