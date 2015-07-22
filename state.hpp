#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <iostream>


class GumballMachine;


class State
{
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
};

class NoQuarterState : public State
{
    GumballMachine* gumballMachine;
public:
    NoQuarterState(GumballMachine* gumballMachine);

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();
};

class HasQuarterState : public State
{
    GumballMachine* gumballMachine;
public:
    HasQuarterState(GumballMachine* gumballMachine);

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();
};

class SoldState : public State
{
    GumballMachine* gumballMachine;
public:
    SoldState(GumballMachine* gumballMachine);

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();
};

class SoldOutState : public State
{
    GumballMachine* gumballMachine;
public:
    SoldOutState(GumballMachine* gumballMachine);

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();
};

class WinnerState : public State
{
    GumballMachine* gumballMachine;
public:
    WinnerState(GumballMachine* gumballMachine);

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();
};


class GumballMachine
{
    State* soldOutState;
    State* noQuarterState;
    State* hasQuarterState;
    State* soldState;
    State* winnerState;

    State* state;
    int count;

public:
    GumballMachine(int numberGumballs);

    ~GumballMachine();

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();

    void releaseBall();

    void refill(int count);

    void setState(State* state);

    State* getState();

    State* getNoQuarterState();

    State* getHasQuarterState();

    State* getSoldState();

    State* getSoldOutState();

    State* getWinnerState();

    int getCount();

    friend std::ostream& operator<<(std::ostream& os, GumballMachine& gm);
};

#endif
