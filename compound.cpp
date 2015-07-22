#include <iostream>

class Quackable
{
public:
    virtual void quack() = 0;
};


class MallardDuck : public Quackable
{
public:
    void quack() 
    {
        std::cout << "Quack" << std::endl;
    }
};


class ReadheadDuck : public Quackable
{
public:
    void quack()
    {
        std::cout << "Quack" << std::endl;
    }
};


class DuckCall : public Quackable
{
public:
    void quack()
    {
        std::cout << "Kwak" << std::endl;
    }
};


class RubberDuck : public Quackable
{
public:
    void quack()
    {
        std::cout << "Squeak" << std::endl;
    }
};


class Goose
{
public:
    void honk()
    {
        std::cout << "Honk" << std::endl;
    }
};


class GooseAdapter : public Quackable
{
    Goose* goose;
public:
    GooseAdapter(Goose* goose)
    {
        this->goose = goose;
    }

    void quack()
    {
        goose->honk();
    }
};


class QuackCounter : public Quackable
{
    Quackable* duck;
    static int numberOfQuacks;
public:
    QuackCounter(Quackable* duck)
    {
        this->duck = duck;
    }

    void quack()
    {
        duck->quack();
        numberOfQuacks++;
    }

    static int getQuacks()
    {
        return numberOfQuacks;
    }
};


class DuckSimulator
{
public:
    void simulate()
    {

        MallardDuck mallardDuck;
        Quackable* mallardDuckCounter = new QuackCounter(&mallardDuck);
        ReadheadDuck readheadDuck;
        Quackable* readheadDuckCounter = new QuackCounter(&readheadDuck);
        DuckCall duckCall;
        Quackable* duckCallCounter = new QuackCounter(&duckCall);
        RubberDuck rubberDuck;
        Quackable* rubberDuckCounter = new QuackCounter(&rubberDuck);

        Goose goose;
        GooseAdapter gooseAdapter(&goose);
        Quackable* gooseAdapterCounter = new QuackCounter(&gooseAdapter);

        std::cout << "Duck Simulator" << std::endl;

        simulate(mallardDuckCounter);
        simulate(readheadDuckCounter);
        simulate(duckCallCounter);
        simulate(rubberDuckCounter);
        simulate(gooseAdapterCounter);

        std::cout << QuackCounter::getQuacks() << std::endl;

        delete mallardDuckCounter;
        mallardDuckCounter = NULL;
        delete readheadDuckCounter;
        readheadDuckCounter = NULL;
        delete duckCallCounter;
        duckCallCounter = NULL;
        delete rubberDuckCounter;
        rubberDuckCounter = NULL;
        delete gooseAdapterCounter;
        gooseAdapterCounter = NULL;
    }

    void simulate(Quackable* duck)
    {
        duck->quack();
    }
};

int QuackCounter::numberOfQuacks = 0;

int main(int argc, char const *argv[])
{
    DuckSimulator ds;
    ds.simulate();


    return 0;
}
