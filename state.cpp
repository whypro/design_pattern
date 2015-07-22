#include "state.hpp"


NoQuarterState::NoQuarterState(GumballMachine* gumballMachine)
{
    this->gumballMachine = gumballMachine;
}

void NoQuarterState::insertQuarter()
{
    std::cout << "You inserted a quarter" << std::endl;
    gumballMachine->setState(gumballMachine->getHasQuarterState());
}
void NoQuarterState::ejectQuarter()
{
    std::cout << "You haven't inserted a quarter" << std::endl;
}

void NoQuarterState::turnCrank()
{
    std::cout << "You haven't inserted a quarter" << std::endl;
}

void NoQuarterState::dispense()
{
    std::cout << "You need to pay first" << std::endl;
}


HasQuarterState::HasQuarterState(GumballMachine* gumballMachine)
{
    this->gumballMachine = gumballMachine;
}

void HasQuarterState::insertQuarter()
{
    std::cout << "You can't insert another quarter" << std::endl;
}

void HasQuarterState::ejectQuarter()
{
    std::cout << "Qurater returned" << std::endl;
    gumballMachine->setState(gumballMachine->getNoQuarterState());
}

void HasQuarterState::turnCrank()
{

    std::cout << "You turned..." << std::endl;
    gumballMachine->setState(gumballMachine->getSoldState());
    gumballMachine->dispense();
}

void HasQuarterState::dispense()
{
    std::cout << "No gumballs dispensed" << std::endl;
}


SoldState::SoldState(GumballMachine* gumballMachine)
{
    this->gumballMachine = gumballMachine;
}

void SoldState::insertQuarter()
{
    std::cout << "Please wait, we're already giving you a gumball" << std::endl;
}

void SoldState::ejectQuarter()
{
    std::cout << "Sorry, you already turned the crank" << std::endl;
}

void SoldState::turnCrank()
{
    std::cout << "Turning twice doesn't get you another gumball!" << std::endl;
}

void SoldState::dispense()
{
    gumballMachine->releaseBall();
    if (gumballMachine->getCount() > 0)
    {
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    }
    else
    {
        std::cout << "Oops, out of gumballs!" << std::endl;
        gumballMachine->setState(gumballMachine->getSoldOutState());
    }
}


SoldOutState::SoldOutState(GumballMachine* gumballMachine)
{
    this->gumballMachine = gumballMachine;
}

void SoldOutState::insertQuarter()
{
    std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
}

void SoldOutState::ejectQuarter()
{
    std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
}

void SoldOutState::turnCrank()
{
    std::cout << "You turned, but there are no gumballs" << std::endl;
}

void SoldOutState::dispense()
{
    std::cout << "No gumballs dispensed" << std::endl;
}


GumballMachine::GumballMachine(int numberGumballs)
{
    soldOutState = new SoldOutState(this);
    noQuarterState = new NoQuarterState(this);
    hasQuarterState = new HasQuarterState(this);
    soldState = new SoldState(this);

    count = numberGumballs;

    if (numberGumballs > 0)
    {
        state = noQuarterState;
    }
    else
    {
        state = soldOutState;
    }
}

GumballMachine::~GumballMachine()
{
    delete soldOutState;
    soldOutState = NULL;
    delete noQuarterState;
    noQuarterState = NULL;
    delete hasQuarterState;
    hasQuarterState = NULL;
    delete soldState;
    soldState = NULL;
}

void GumballMachine::insertQuarter()
{
    state->insertQuarter();
}

void GumballMachine::ejectQuarter()
{
    state->ejectQuarter();
}

void GumballMachine::turnCrank()
{
    state->turnCrank();
}

void GumballMachine::dispense()
{
    state->dispense();
}

void GumballMachine::releaseBall()
{
    if (count != 0)
    {
        std::cout << "A gumball comes rolling out the slot" << std::endl;
        count -= 1;
    }
}

void GumballMachine::setState(State* state)
{
    this->state = state;
}

State* GumballMachine::getState()
{
    return state;
}

State* GumballMachine::getNoQuarterState()
{
    return noQuarterState;
}

State* GumballMachine::getHasQuarterState()
{
    return hasQuarterState;
}

State* GumballMachine::getSoldState()
{
    return soldState;
}

State* GumballMachine::getSoldOutState()
{
    return soldOutState;
}

int GumballMachine::getCount()
{
    return count;
}


std::ostream& operator<<(std::ostream& os, GumballMachine& gm)
{
    std::cout << "Mighty Gumball, Inc." << std::endl;
    std::cout << "Inventory: " << gm.count << " gumballs" << std::endl;

    State* state = gm.getState();

    if (state == gm.getHasQuarterState())
    {
        std::cout << "Machine is waiting for cranking";
    }
    else if (state == gm.getSoldOutState())
    {
        std::cout << "Machine is sold out";
    }
    else if (state == gm.getSoldState())
    {
        std::cout << "Machine is dispensing";
    }
    else if (state == gm.getNoQuarterState())
    {
        std::cout << "Machine is waiting for quarter";
    }

    return os;
}


int main(int argc, char const *argv[])
{
    GumballMachine gumballMachine(5);

    std::cout << gumballMachine << std::endl;
    std::cout << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine << std::endl;
    std::cout << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.ejectQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine << std::endl;
    std::cout << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.ejectQuarter();

    std::cout << gumballMachine << std::endl;
    std::cout << std::endl;

    gumballMachine.insertQuarter();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();

    std::cout << gumballMachine << std::endl;
    std::cout << std::endl;

    return 0;
}
