#include <iostream>

class ChocolateBoiler
{
private:
    bool empty;
    bool boiled;

    static ChocolateBoiler* instance;

    ChocolateBoiler()
    {
        empty = true;
        boiled = false;
    }

public:
    static ChocolateBoiler* getInstance()
    {
        if (instance == NULL)
        {
            instance = new ChocolateBoiler();
        }

        return instance;
    }

    void fill()
    {
        if (isEmpty())
        {
            std::cout << "filling" << std::endl;
            empty = false;
            boiled = false;
        }
    }

    void drain()
    {
        if (!isEmpty() && isBoiled())
        {
            std::cout << "draining" << std::endl;
            empty = true;
        }
    }

    void boil()
    {
        if (!isEmpty() && !isBoiled())
        {
            std::cout << "boiling" << std::endl;
            boiled = true;
        }
    }

    bool isEmpty()
    {
        return empty;
    }

    bool isBoiled()
    {
        return boiled;
    }
    
};

ChocolateBoiler* ChocolateBoiler::instance = NULL;

int main(int argc, char const *argv[])
{
    ChocolateBoiler* cb = ChocolateBoiler::getInstance();
    cb->fill();
    cb->boil();

    return 0;
}
