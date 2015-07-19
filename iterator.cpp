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


class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual MenuItem* next() = 0;
};

class DinerMenuIterator : public Iterator
{
    MenuItem** items;
    int numberOfItems;
    int position;
public:
    DinerMenuIterator(MenuItem** items, int numberOfItems)
    {
        this->numberOfItems = numberOfItems;
        position = 0;
        this->items = items;
    }

    MenuItem* next()
    {
        MenuItem* menuItem = items[position];
        position++;
        return menuItem;
    }

    bool hasNext()
    {
        if (position >= numberOfItems || items[position] == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};


class PancakeHouseMenuIterator : public Iterator
{
    std::vector<MenuItem*> items;
    int position;
public:
    PancakeHouseMenuIterator(std::vector<MenuItem*>& items)
    {
        this->items = items;
        position = 0;
    }

    MenuItem* next()
    {
        MenuItem* menuItem = items[position];
        position++;
        return menuItem;
    }

    bool hasNext()
    {
        if (position >= items.size() || items[position] == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
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

    ~PancakeHouseMenu()
    {
        for (std::vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
        {
            // std::cout << "~PancakeHouseMenu" << std::endl;
            delete *it;
        }
    }

    Iterator* createIterator()
    {
        return new PancakeHouseMenuIterator(menuItems);
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

    ~DinerMenu()
    {
        for (int i = 0; i < numberOfItems; i++)
        {
            // std::cout << "~DinerMenu" << std::endl;
            delete menuItems[i];
        }
    }

    Iterator* createIterator()
    {
        return new DinerMenuIterator(menuItems, numberOfItems);
    }
};


class Waitress
{
    PancakeHouseMenu* pancakeHouseMenu;
    DinerMenu* dinerMenu;

    void printMenu(Iterator* it)
    {
        while (it->hasNext())
        {
            MenuItem* menuItem = it->next();

            std::cout << menuItem->getName() << ", ";
            std::cout << menuItem->getPrice() << " -- ";
            std::cout << menuItem->getDescription() << std::endl;
        }
    }
public:
    Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu)
    {
        this->pancakeHouseMenu = pancakeHouseMenu;
        this->dinerMenu = dinerMenu;
    }

    void printMenu()
    {
        Iterator* pancakeIterator = pancakeHouseMenu->createIterator();
        Iterator* dinerIterator = dinerMenu->createIterator();

        std::cout << "MENU" << std::endl;
        std::cout << "----" << std::endl;
        std::cout << "BREAKFAST" << std::endl;
        printMenu(pancakeIterator);
        std::cout << "LANCH" << std::endl;
        printMenu(dinerIterator);

    }
};








int main(int argc, char const *argv[])
{
    PancakeHouseMenu pancakeHouseMenu;
    DinerMenu dinerMenu;

    Waitress alice(&pancakeHouseMenu, &dinerMenu);
    alice.printMenu();

    return 0;
}
