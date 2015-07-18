#include <iostream>
#include <vector>

class MenuItem
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

};


class PancakeHouseMenu
{
    std::vector<MenuItem*> menuItems;

public:
    PancakeHouseMenu()
    {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
    }

    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
        menuItems.push_back(menuItem);
    }

    std::vector<MenuItem*> getMenuItems()
    {
        return menuItems;
    }

    ~PancakeHouseMenu()
    {
        for (std::vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
        {
            // std::cout << "~PancakeHouseMenu" << std::endl;
            delete *it;
        }
    }

};

class DinerMenu
{
    static const int MAX_ITEMS = 6;
    int numberOfItems;
    MenuItem* menuItems[MAX_ITEMS];

public:
    DinerMenu()
    {
        numberOfItems = 0;

        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
    }

    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
    {
        MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
        if (numberOfItems >= MAX_ITEMS)
        {
            std::cout << "Sorry, menu is full! Can't add item to menu" << std::endl;
        }
        else
        {
            menuItems[numberOfItems] = menuItem;
            numberOfItems++;
        }
    }

    MenuItem** getMenuItems()
    {
        return menuItems;
    }

    ~DinerMenu()
    {
        for (int i = 0; i < numberOfItems; i++)
        {
            // std::cout << "~DinerMenu" << std::endl;
            delete menuItems[i];
        }
    }
};


int main(int argc, char const *argv[])
{
    // MenuItem* item = new MenuItem("name", "description", true, 0.2);

    PancakeHouseMenu phm;
    std::cout << phm.getMenuItems()[0]->getName() << std::endl;

    DinerMenu dm;
    std::cout << dm.getMenuItems()[0]->getName() << std::endl;

    return 0;
}
