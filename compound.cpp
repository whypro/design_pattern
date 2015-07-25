#include <iostream>
#include <vector>


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


class Flock : public Quackable
{
    std::vector<Quackable*> quackers;

public:
    ~Flock()
    {
        for (std::vector<Quackable*>::iterator it = quackers.begin(); it != quackers.end(); it++)
        {
            delete *it;
            *it = NULL;
        }
    }

    void add(Quackable* quacker)
    {
        quackers.push_back(quacker);
    }

    void quack()
    {
        for (std::vector<Quackable*>::iterator it = quackers.begin(); it != quackers.end(); it++)
        {
            (*it)->quack();
        }
    }
};


class DuckSimulator
{
public:
    void simulate(AbstractDuckFactory* duckFactory)
    {
        Quackable* readheadDuck = duckFactory->createRedheadDuck();
        Quackable* duckCall = duckFactory->createDuckCall();
        Quackable* rubberDuck = duckFactory->createRubberDuck();
        Quackable* gooseAdapter = new GooseAdapter(new Goose);

        Flock* flockOfDucks = new Flock;
        flockOfDucks->add(readheadDuck);
        flockOfDucks->add(duckCall);
        flockOfDucks->add(rubberDuck);
        flockOfDucks->add(gooseAdapter);

        Quackable* mallardDuckOne = duckFactory->createMallardDuck();
        Quackable* mallardDuckTwo = duckFactory->createMallardDuck();
        Quackable* mallardDuckThree = duckFactory->createMallardDuck();
        Quackable* mallardDuckFour = duckFactory->createMallardDuck();

        Flock* flockOfMallards = new Flock;
        flockOfMallards->add(mallardDuckOne);
        flockOfMallards->add(mallardDuckTwo);
        flockOfMallards->add(mallardDuckThree);
        flockOfMallards->add(mallardDuckFour);

        flockOfDucks->add(flockOfMallards);

        std::cout << "Duck Simulator: Whole Flock Simulation" << std::endl;
        simulate(flockOfDucks);

        std::cout << "Duck Simulator: Mallard Flock Simulation" << std::endl;
        simulate(flockOfMallards);

        std::cout << QuackCounter::getQuacks() << std::endl;

        delete flockOfDucks;
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
