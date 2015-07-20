#include <iostream>
#include <vector>
#include <list>


class MenuComponent
{
public:
    virtual std::string& getName() = 0;

    virtual std::string& getDescription() = 0;

    virtual void print() = 0;
};


class MenuItem : public MenuComponent
{
    std::string name;
    std::string description;
    bool vegetarian;
    double price;

public:
    MenuItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        this->name = name;
        this->description = description;
        this->vegetarian = vegetarian;
        this->price = price;
    }

    std::string& getName()
    {
        return name;
    }

    std::string& getDescription()
    {
        return description;
    }

    double getPrice()
    {
        return price;
    }

    bool isVegetarian()
    {
        return vegetarian;
    }

    void print()
    {
        std::cout << "  " << getName();
        if (isVegetarian())
        {
            std::cout << "(v)";
        }
        std::cout << ", " << getPrice() << std::endl;
        std::cout << "    -- " << getDescription() << std::endl;
    }

};



class Menu : public MenuComponent
{
    std::vector<MenuComponent*> menuComponents;
    std::string name;
    std::string description;

public:
    Menu(const std::string& name, const std::string& description)
    {
        this->name = name;
        this->description = description;
    }

    void add(MenuComponent* menuComponent)
    {
        menuComponents.push_back(menuComponent);
    }

    MenuComponent* getChild(int i)
    {
        return menuComponents[i];
    }

    std::string& getName()
    {
        return name;
    }

    std::string& getDescription()
    {
        return description;
    }

    void print()
    {
        std::cout << "\n" << getName();
        std::cout << ", " << getDescription() << std::endl;
        std::cout << "------------------------" << std::endl;

        for (std::vector<MenuComponent*>::iterator it = menuComponents.begin(); it != menuComponents.end(); it++)
        {
            (*it)->print();
        }
    }
};


class Waitress
{
    MenuComponent* allMenus;

public:
    Waitress(MenuComponent* allMenus)
    {
        this->allMenus = allMenus;
    }

    void printMenu()
    {
        allMenus->print();
    }
};


int main(int argc, char const *argv[])
{
    Menu pancakeHouseMenu("PANCAKE HOUSE MENU", "Breakfast");
    Menu dinerMenu("DINER MENU", "Lunch");
    Menu cafeMenu("CAFE MENU", "Dinner");
    Menu dessertMenu("DESSERT MENU", "Dessert of course");

    Menu allMenus("ALL MENUS", "All menus combined");

    allMenus.add(&pancakeHouseMenu);
    allMenus.add(&dinerMenu);
    allMenus.add(&cafeMenu);

    MenuItem item1_1("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
    MenuItem item1_2("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
    MenuItem item1_3("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
    MenuItem item1_4("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
    dinerMenu.add(&item1_1);
    dinerMenu.add(&item1_2);
    dinerMenu.add(&item1_3);
    dinerMenu.add(&item1_4);

    MenuItem item1_5("Apple Pie", "Apple pie with a flakey crust, topped with vanilla ice cream", true, 1.59);
    dessertMenu.add(&item1_5);

    dinerMenu.add(&dessertMenu);

    Waitress alice(&allMenus);
    alice.printMenu();

    return 0;
}
