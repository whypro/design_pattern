#include <iostream>


enum SLOT_DEF
{
    SLOT_INVALID = 0,
    SLOT_LIVING_ROOM_LIGHT,
    SLOT_KITCHEN_LIGHT,
    SLOT_CEILING_FAN,
    SLOT_GARAGE_DOOR,
    SLOT_STEREO,
    SLOT_ALL_LIGHT,
    SLOT_MACRO,
    SLOT_MAX,
};

#define REMOTE_CONTROL

// Receiver
class Light
{
public:
    void on()
    {
        std::cout << "Light on" << std::endl;
    }
    void off()
    {
        std::cout << "Light off" << std::endl;
    }
};

class GarageDoor
{
public:
    void up()
    {
        std::cout << "Garage door up" << std::endl;
    }

    void down()
    {
        std::cout << "Garage door down" << std::endl;
    }

    void stop()
    {
        std::cout << "Garage door stop" << std::endl;
    }

    void lightOn()
    {
        std::cout << "Garage door light on" << std::endl;
    }

    void lightOff()
    {
        std::cout << "Garage door light off" << std::endl;
    }
};

class CeilingFan
{
    int speed;
public:
    static const int OFF = 0;
    static const int LOW = 1;
    static const int MEDIUM = 2;
    static const int HIGH = 3;

    void high()
    {
        std::cout << "Ceiling Fan high" << std::endl;
        speed = HIGH;
    }

    void medium()
    {
        std::cout << "Ceiling Fan medium" << std::endl;
        speed = MEDIUM;
    }

    void low()
    {
        std::cout << "Ceiling Fan low" << std::endl;
        speed = LOW;
    }

    void off()
    {
        std::cout << "Ceiling Fan off" << std::endl;
        speed = OFF;
    }

    int getSpeed()
    {
        return speed;
    }
};

class Stereo
{
    int volumn;
    int mode;
public:
    static const int CD = 1;

    void on()
    {
        std::cout << "Stereo on" << std::endl;
    }
    void off()
    {
        std::cout << "Stereo off" << std::endl;
    }
    void setCd()
    {
        mode = CD;
        std::cout << "Stereo set CD" << std::endl;
    }
    void setDvd()
    {
        std::cout << "Stereo set DVD" << std::endl;
    }
    void setRadio()
    {
        std::cout << "Stereo set Radio" << std::endl;
    }
    void setVolumn(int volumn)
    {
        std::cout << "Stereo set volume to " << volumn << std::endl;
        this->volumn = volumn;
    }

    int getVolumn()
    {
        return volumn;
    }

    int getMode()
    {
        return mode;
    }
};


// Command
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class NoCommand : public Command
{
public:
    void execute()
    {
        std::cout << "No Command" << std::endl;
    }
    void undo()
    {
        std::cout << "No Command" << std::endl;
    }
};

class LightOnCommand : public Command
{
    Light* light;

public:
    LightOnCommand(Light* light)
    {
        this->light = light;
    }

    void execute()
    {
        light->on();
    }

    void undo()
    {
        light->off();
    }
};

class LightOffCommand : public Command
{
    Light* light;

public:
    LightOffCommand(Light* light)
    {
        this->light = light;
    }

    void execute()
    {
        light->off();
    }

    void undo()
    {
        light->on();
    }
};

class CeilingFanHighCommand : public Command
{
    CeilingFan* ceilingFan;
    int prevSpeed;
public:
    CeilingFanHighCommand(CeilingFan* ceilingFan)
    {
        this->ceilingFan = ceilingFan;
    }

    void execute()
    {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->high();
    }

    void undo()
    {
        switch (prevSpeed) 
        {
        case CeilingFan::OFF:
            ceilingFan->off();
            break;
        case CeilingFan::LOW:
            ceilingFan->low();
            break;
        case CeilingFan::MEDIUM:
            ceilingFan->medium();
            break;
        case CeilingFan::HIGH:
            ceilingFan->high();
            break;
        default:
            break;
        }
    }
};

class CeilingFanOffCommand : public Command
{
    CeilingFan* ceilingFan;
public:
    CeilingFanOffCommand(CeilingFan* ceilingFan)
    {
        this->ceilingFan = ceilingFan;
    }

    void execute()
    {
        ceilingFan->off();
    }

    void undo()
    {
        ceilingFan->high();
    }
};

class GarageDoorOpenCommand : public Command
{
    GarageDoor* garageDoor;
public:
    GarageDoorOpenCommand(GarageDoor* garageDoor)
    {
        this->garageDoor = garageDoor;
    }

    void execute()
    {
        garageDoor->up();
    }

    void undo()
    {
        garageDoor->down();
    }
};

class GarageDoorCloseCommand : public Command
{
    GarageDoor* garageDoor;
public:
    GarageDoorCloseCommand(GarageDoor* garageDoor)
    {
        this->garageDoor = garageDoor;
    }

    void execute()
    {
        garageDoor->down();
    }

    void undo()
    {
        garageDoor->up();
    }
};

class StereoOnForCDCommand : public Command
{
    Stereo* stereo;
public:
    StereoOnForCDCommand(Stereo* stereo)
    {
        this->stereo = stereo;
    }

    void execute()
    {
        stereo->on();
        stereo->setCd();
        stereo->setVolumn(12);
    }

    void undo()
    {
        stereo->off();
    }
};

class StereoOffCommand : public Command
{
    Stereo* stereo;

    int prevVolumn;
    int prevMode;
public:
    StereoOffCommand(Stereo* stereo)
    {
        this->stereo = stereo;
    }

    void execute()
    {
        prevVolumn = stereo->getVolumn();
        prevMode = stereo->getMode();
        stereo->off();
    }

    void undo()
    {
        stereo->on();
        switch (prevMode)
        {
        case Stereo::CD:
            stereo->setCd();
            break;
        default:
            break;
        }
        stereo->setVolumn(prevVolumn);
    }
};

class MacroCommand : public Command
{
    Command** commands;
    int command_num ;
public:
    MacroCommand(Command** commands, int n)
    {
        this->commands = commands;
        command_num = n;
    }

    void execute()
    {
        for (int i = 0; i < command_num; i++)
        {
            commands[i]->execute();
        }
    }

    void undo()
    {
        for (int i = 0; i < command_num; i++)
        {
            commands[i]->undo();
        }
    }
};


// Invoker
class SimpleRemoteControl
{
    Command* slot;
public:
    void setCommand(Command* command)
    {
        slot = command;
    }
    void buttonWasPressed()
    {
        slot->execute();
    }
};

class RemoteControl
{
    Command** onCommands;
    Command** offCommands;

    // 可用堆栈实现连续撤销
    Command* undoCommand;
    Command* noCommand;

public:
    RemoteControl()
    {
        onCommands = new Command*[SLOT_MAX];
        offCommands = new Command*[SLOT_MAX];

        noCommand = new NoCommand();

        for (int i = 0; i < SLOT_MAX; i++)
        {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
        undoCommand = noCommand;
    }

    ~RemoteControl()
    {
        delete onCommands;
        delete offCommands;
        delete noCommand;
    }

    void setCommand(int slot, Command* onCommand, Command* offCommand)
    {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }

    void onButtonWasPushed(int slot)
    {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }

    void offButtonWasPushed(int slot)
    {
        offCommands[slot]->execute();
        undoCommand = offCommands[slot];
    }

    void undoButtonWasPushed()
    {
        undoCommand->undo();
    }

};


// Client
int main(int argc, char const *argv[])
{
    Light* light = new Light();
    LightOnCommand* lightOn = new LightOnCommand(light);
    LightOffCommand* lightOff = new LightOffCommand(light);

    GarageDoor* garageDoor = new GarageDoor();
    GarageDoorOpenCommand* doorOpen = new GarageDoorOpenCommand(garageDoor);
    GarageDoorCloseCommand* doorClose = new GarageDoorCloseCommand(garageDoor);

    CeilingFan* ceilingFan = new CeilingFan();
    CeilingFanHighCommand* fanHigh = new CeilingFanHighCommand(ceilingFan);
    CeilingFanOffCommand* fanOff = new CeilingFanOffCommand(ceilingFan);

    Stereo* stereo = new Stereo();
    StereoOnForCDCommand* stereoOnForCD = new StereoOnForCDCommand(stereo);
    StereoOffCommand* stereoOff = new StereoOffCommand(stereo);

    Command* partyOn[] = { lightOn, stereoOnForCD };
    Command* partyOff[] = { lightOff, stereoOff };
    MacroCommand* partyOnMacro = new MacroCommand(partyOn, sizeof(partyOn)/sizeof(partyOn[0]));
    MacroCommand* partyOffMacro = new MacroCommand(partyOff, sizeof(partyOff)/sizeof(partyOff[0]));

#ifndef REMOTE_CONTROL
    SimpleRemoteControl* remote = new SimpleRemoteControl();
    remote->setCommand(lightOn);
    remote->buttonWasPressed();
    remote->setCommand(lightOff);
    remote->buttonWasPressed();

    remote->setCommand(doorOpen);
    remote->buttonWasPressed();
    remote->setCommand(doorClose);
    remote->buttonWasPressed();

    remote->setCommand(fanHigh);
    remote->buttonWasPressed();
    remote->setCommand(fanOff);
    remote->buttonWasPressed();

    remote->setCommand(stereoOnForCD);
    remote->buttonWasPressed();
    remote->setCommand(stereoOff);
    remote->buttonWasPressed();
#else
    RemoteControl* remote = new RemoteControl();
    remote->setCommand(SLOT_LIVING_ROOM_LIGHT, lightOn, lightOff);
    // remote->setCommand(SLOT_KITCHEN_ROOM_LIGHT, lightOn, lightOff);
    remote->setCommand(SLOT_CEILING_FAN, fanHigh, fanOff);
    remote->setCommand(SLOT_GARAGE_DOOR, doorOpen, doorClose);
    remote->setCommand(SLOT_STEREO, stereoOnForCD, stereoOff);


    remote->onButtonWasPushed(SLOT_LIVING_ROOM_LIGHT);
    remote->offButtonWasPushed(SLOT_LIVING_ROOM_LIGHT);
    remote->onButtonWasPushed(SLOT_CEILING_FAN);
    remote->offButtonWasPushed(SLOT_CEILING_FAN);
    remote->undoButtonWasPushed();
    remote->onButtonWasPushed(SLOT_GARAGE_DOOR);
    remote->offButtonWasPushed(SLOT_GARAGE_DOOR);
    remote->onButtonWasPushed(SLOT_STEREO);
    remote->offButtonWasPushed(SLOT_STEREO);

    remote->undoButtonWasPushed();

    remote->setCommand(SLOT_MACRO, partyOnMacro, partyOffMacro);
    remote->onButtonWasPushed(SLOT_MACRO);
    remote->offButtonWasPushed(SLOT_MACRO);

    // remote->onButtonWasPushed(6);
    // remote->offButtonWasPushed(6);
#endif

    return 0;
}
