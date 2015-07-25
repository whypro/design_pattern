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

    ~GooseAdapter()
    {
        delete this->goose;
        this->goose = NULL;
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

    ~QuackCounter()
    {
        delete this->duck;
        this->duck = NULL;
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


class AbstractDuckFactory 
{
public:
    virtual Quackable* createMallardDuck() = 0;
    virtual Quackable* createRedheadDuck() = 0;
    virtual Quackable* createDuckCall() = 0;
    virtual Quackable* createRubberDuck() = 0;
};


class DuckFactory : public AbstractDuckFactory
{
public:
    Quackable* createMallardDuck()
    {
        return new MallardDuck;
    }

    Quackable* createRedheadDuck()
    {
        return new ReadheadDuck;
    }

    Quackable* createDuckCall()
    {
        return new DuckCall;
    }

    Quackable* createRubberDuck()
    {
        return new RubberDuck;
    }
};


class CountingDuckFactory : public AbstractDuckFactory
{
public:
    Quackable* createMallardDuck()
    {
        return new QuackCounter(new MallardDuck);
    }

    Quackable* createRedheadDuck()
    {
        return new QuackCounter(new ReadheadDuck);
    }

    Quackable* createDuckCall()
    {
        return new QuackCounter(new DuckCall);
    }

    Quackable* createRubberDuck()
    {
        return new QuackCounter(new RubberDuck);
    }
};


class DuckSimulator
{
public:
    void simulate(AbstractDuckFactory* duckFactory)
    {
        Quackable* mallardDuckCounter = duckFactory->createMallardDuck();
        Quackable* readheadDuckCounter = duckFactory->createRedheadDuck();
        Quackable* duckCallCounter = duckFactory->createDuckCall();
        Quackable* rubberDuckCounter = duckFactory->createRubberDuck();
        Quackable* gooseAdapterCounter = new QuackCounter(new GooseAdapter(new Goose));

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
    AbstractDuckFactory* adf = new CountingDuckFactory;
    DuckSimulator ds;
    ds.simulate(adf);

    delete adf;
    adf = NULL;

    return 0;
}
