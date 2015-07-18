#include <iostream>
#include <vector>
#include <string>

/*
工厂方法是根据 具体工厂 分类
抽象工厂是根据 产品家族 分类
*/

class Veggies {};
class Garlic : public Veggies {};
class Onion : public Veggies {};
class Mushroom : public Veggies {};
class RedPepper : public Veggies {};
class BlackOlives : public Veggies {};
class Spinach : public Veggies {};
class Eggplant : public Veggies {};


class Clams {};
class Sauce {};
class Dough {};
class Cheese {};

class FrozenClams : public Clams {};
class PlumTomatoSauce : public Sauce {};
class ThickCrustDough : public Dough {};
class MozzarellaCheese : public Cheese {};

class FreshClams : public Clams {};
class MarinaraSauce : public Sauce {};
class ThinCrustDough : public Dough {};
class ReggianoCheese : public Cheese {};

class Calamari : public Clams {};
class BruschettaSauce : public Sauce {};
class VeryThinCrust : public Dough {};
class GoatCheese : public Cheese {};

class Pepperoni {};
class SlicedPepperoni: public Pepperoni {};


class Pizza 
{
protected:
    std::string name;
    Dough* dough;
    Sauce* sauce;
    Cheese* cheese;
    Pepperoni* pepperoni;
    Clams* clam;
    std::vector<Veggies*> veggies;
    std::vector<std::string> toppings;
public:
    virtual void prepare() = 0;
    
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

    virtual void setName(std::string name)
    {
        this->name = name;
    }

    virtual std::string getName()
    {
        return name;
    }
};


class PizzaIngredientFactory
{
public:
    virtual Dough* cerateDough() = 0;
    virtual Sauce* createSauce() = 0;
    virtual Cheese* createCheese() = 0;
    virtual std::vector<Veggies*> createVeggies() = 0;
    virtual Pepperoni* createPepperoni() = 0;
    virtual Clams* createClam() = 0;
};


class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    Dough* cerateDough()
    {
        std::cout << "    Thin Crust Dough" << std::endl;
        return new ThinCrustDough;
    }
    Sauce* createSauce()
    {
        std::cout << "    Marinara Sauce" << std::endl;
        return new MarinaraSauce;
    }
    Cheese* createCheese()
    {
        std::cout << "    Reggiano Cheese" << std::endl;
        return new ReggianoCheese;
    }
    std::vector<Veggies*> createVeggies()
    {
        std::cout << "    Veggies" << std::endl;
        std::vector<Veggies*> veggies;
        veggies.push_back(new Garlic);
        veggies.push_back(new Onion);
        veggies.push_back(new Mushroom);
        veggies.push_back(new RedPepper);
        return veggies;
    }
    Pepperoni* createPepperoni()
    {
        std::cout << "    Sliced Pepperoni" << std::endl;
        return new SlicedPepperoni;
    }
    Clams* createClam()
    {
        std::cout << "    Fresh Clams" << std::endl;
        return new FreshClams;
    }
};


class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    Dough* cerateDough()
    {
        std::cout << "    Thick Crust Dough" << std::endl;
        return new ThickCrustDough;
    }
    Sauce* createSauce()
    {
        std::cout << "    Plum Tomato Sauce" << std::endl;
        return new PlumTomatoSauce;
    }
    Cheese* createCheese()
    {
        std::cout << "    Mozzarella Cheese" << std::endl;
        return new MozzarellaCheese;
    }
    std::vector<Veggies*> createVeggies()
    {
        std::cout << "    Veggies" << std::endl;
        std::vector<Veggies*> veggies;
        veggies.push_back(new BlackOlives);
        veggies.push_back(new Spinach);
        veggies.push_back(new Eggplant);
        return veggies;
    }
    Pepperoni* createPepperoni()
    {
        std::cout << "    Sliced Pepperoni" << std::endl;
        return new SlicedPepperoni;
    }
    Clams* createClam()
    {
        std::cout << "    Frozen Clams" << std::endl;
        return new FrozenClams;
    }
};


class CheesePizza : public Pizza 
{
    PizzaIngredientFactory* ingredientFactory;
public:
    CheesePizza(PizzaIngredientFactory* ingredientFactory)
    {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare()
    {
        std::cout << "Preparing " << name << std::endl;
        dough = ingredientFactory->cerateDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
    }
};


class ClamPizza : public Pizza 
{
    PizzaIngredientFactory* ingredientFactory;
public:
    ClamPizza(PizzaIngredientFactory* ingredientFactory)
    {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare()
    {
        std::cout << "Preparing " << name << std::endl;
        dough = ingredientFactory->cerateDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        clam = ingredientFactory->createClam();
    }
};

class VeggiePizza : public Pizza 
{
    PizzaIngredientFactory* ingredientFactory;
public:
    VeggiePizza(PizzaIngredientFactory* ingredientFactory)
    {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare()
    {
        std::cout << "Preparing " << name << std::endl;
        dough = ingredientFactory->cerateDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        veggies = ingredientFactory->createVeggies();
    }
};


class PepperoniPizza : public Pizza 
{
    PizzaIngredientFactory* ingredientFactory;
public:
    PepperoniPizza(PizzaIngredientFactory* ingredientFactory)
    {
        this->ingredientFactory = ingredientFactory;
    }
    void prepare()
    {
        std::cout << "Preparing " << name << std::endl;
        dough = ingredientFactory->cerateDough();
        sauce = ingredientFactory->createSauce();
        cheese = ingredientFactory->createCheese();
        pepperoni = ingredientFactory->createPepperoni();
    }
};


class PizzaStore
{
public:
    virtual Pizza* orderPizza(std::string type)
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
        PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory;

        if (type == "cheese")
        {
            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("New York Style Cheese Pizza");
        }
        else if (type == "pepperoni")
        {
            pizza = new PepperoniPizza(ingredientFactory);
            pizza->setName("New York Style Pepperoni Pizza");
        }
        else if (type == "clam")
        {
            pizza = new ClamPizza(ingredientFactory);
            pizza->setName("New York Style Clam Pizza");
        }
        else if (type == "veggie")
        {
            pizza = new VeggiePizza(ingredientFactory);
            pizza->setName("New York Style Veggie Pizza");
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
        PizzaIngredientFactory* ingredientFactory = new ChicagoPizzaIngredientFactory;

        if (type == "cheese")
        {
            pizza = new CheesePizza(ingredientFactory);
            pizza->setName("Chicago Style Cheese Pizza");
        }
        else if (type == "pepperoni")
        {
            pizza = new PepperoniPizza(ingredientFactory);
            pizza->setName("Chicago Style Pepperoni Pizza");
        }
        else if (type == "clam")
        {
            pizza = new ClamPizza(ingredientFactory);
            pizza->setName("Chicago Style Clam Pizza");
        }
        else if (type == "veggie")
        {
            pizza = new VeggiePizza(ingredientFactory);
            pizza->setName("Chicago Style Veggie Pizza");
        }

        return pizza;
    }
};


int main(int argc, char const *argv[])
{
    PizzaStore* nyps = new NYStylePizzaStore;
    PizzaStore* csps = new ChicagoStylePizzaStore;

    Pizza* pizza = nyps->orderPizza("cheese");
    nyps->orderPizza("clam");
    nyps->orderPizza("veggie");
    nyps->orderPizza("pepperoni");

    csps->orderPizza("cheese");
    csps->orderPizza("clam");
    csps->orderPizza("veggie");
    csps->orderPizza("pepperoni");

    return 0;
}
