#include <iostream>
#include <vector>

class QuackObservable;

class Observer
{
public:
    virtual void update(QuackObservable* duck) = 0;
};


class Quackologist : public Observer
{
public:
    void update(QuackObservable* duck)
    {
        std::cout << "Quackologist: " << duck << " just quacked" << std::endl;
    }
};


class QuackObservable
{
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class Quackable : public QuackObservable
{
public:
    virtual void quack() = 0;
};


class Observable : public QuackObservable
{
    std::vector<Observer*> observers;
    QuackObservable* duck;

public:
    Observable(QuackObservable* duck)
    {
        this->duck = duck;
    }

    void registerObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void notifyObservers()
    {
        for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); it++)
        {
            (*it)->update(duck);
        }
    }
};


class MallardDuck : public Quackable
{
    Observable* observable;
public:
    MallardDuck()
    {
        observable = new Observable(this);
    }

    ~MallardDuck()
    {
        delete observable;
        observable = NULL;
    }

    void quack() 
    {
        std::cout << "Quack" << std::endl;
        notifyObservers();
    }

    void registerObserver(Observer* observer)
    {
        observable->registerObserver(observer);
    }

    void notifyObservers()
    {
        observable->notifyObservers();
    }
};


class ReadheadDuck : public Quackable
{
    Observable* observable;
public:
    ReadheadDuck()
    {
        observable = new Observable(this);
    }

    ~ReadheadDuck()
    {
        delete observable;
        observable = NULL;
    }

    void quack()
    {
        std::cout << "Quack" << std::endl;
        notifyObservers();
    }

    void registerObserver(Observer* observer)
    {
        observable->registerObserver(observer);
    }

    void notifyObservers()
    {
        observable->notifyObservers();
    }
};


class DuckCall : public Quackable
{
    Observable* observable;
public:
    DuckCall()
    {
        observable = new Observable(this);
    }

    ~DuckCall()
    {
        delete observable;
        observable = NULL;
    }

    void quack()
    {
        std::cout << "Kwak" << std::endl;
        notifyObservers();
    }

    void registerObserver(Observer* observer)
    {
        observable->registerObserver(observer);
    }

    void notifyObservers()
    {
        observable->notifyObservers();
    }
};


class RubberDuck : public Quackable
{
    Observable* observable;
public:
    RubberDuck()
    {
        observable = new Observable(this);
    }

    ~RubberDuck()
    {
        delete observable;
        observable = NULL;
    }

    void quack()
    {
        std::cout << "Squeak" << std::endl;
        notifyObservers();
    }

    void registerObserver(Observer* observer)
    {
        observable->registerObserver(observer);
    }

    void notifyObservers()
    {
        observable->notifyObservers();
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
    Observable* observable;
public:
    GooseAdapter(Goose* goose)
    {
        this->goose = goose;
        observable = new Observable(this);
    }

    ~GooseAdapter()
    {
        delete this->goose;
        this->goose = NULL;

        delete observable;
        observable = NULL;
    }

    void quack()
    {
        goose->honk();
        notifyObservers();
    }

    void registerObserver(Observer* observer)
    {
        observable->registerObserver(observer);
    }

    void notifyObservers()
    {
        observable->notifyObservers();
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

    void registerObserver(Observer* observer)
    {
        duck->registerObserver(observer);
    }

    void notifyObservers()
    {
        duck->notifyObservers();
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

    void registerObserver(Observer* observer)
    {
        for (std::vector<Quackable*>::iterator it = quackers.begin(); it != quackers.end(); it++)
        {
            (*it)->registerObserver(observer);
        }
    }

    void notifyObservers()
    {
        for (std::vector<Quackable*>::iterator it = quackers.begin(); it != quackers.end(); it++)
        {
            (*it)->notifyObservers();
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

        Quackologist quackologist;
        flockOfDucks->registerObserver(&quackologist);

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
