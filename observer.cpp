#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


class Observer
{
public:
    virtual void update(float temp, float humidity, float pressure) = 0;
};

class Subject
{
public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
};

class DisplayElement
{
public:
    virtual void display() = 0;
};

class WeatherData : public Subject
{
private:
    std::vector<Observer*> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    void registerObserver(Observer* o)
    {
        observers.push_back(o);
    }

    void removeObserver(Observer* o)
    {
        std::vector<Observer*>::iterator i = std::find(observers.begin(), observers.end(), o);
        if (i == observers.end())
        {
            std::cout << "Error, Not found!" << std::endl;
        }
        else
        {
            observers.erase(i);
        }
    }

    void notifyObservers()
    {
        for (std::vector<Observer*>::iterator i = observers.begin(); i != observers.end(); i++)
        {
            (*i)->update(temperature, humidity, pressure);
        }
    }

    void mesurementsChanged()
    {
        notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure)
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        mesurementsChanged();
    }
};

class CurrentConditionsDisplay : public Observer, DisplayElement
{
private:
    float temperature;
    float humidity;
    Subject* weatherData;

public:
    CurrentConditionsDisplay(Subject* weatherData)
    {
        this->weatherData = weatherData;
        this->weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure)
    {
        this->temperature = temperature;
        this->humidity = humidity;
        display();
    }

    void display()
    {
        std::cout << "Current Conditions: " << temperature << "F degrees and " << humidity << "% humidity" << std::endl;
    }
};


class StaticsticsDisplay : public Observer, DisplayElement
{
private:
    std::vector<float> temperatures;
    float maxTemperature;
    float minTemperature;
    float avgTemperature;

    Subject* weatherData;

public:
    StaticsticsDisplay(Subject* weatherData)
    {
        this->weatherData = weatherData;
        this->weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure)
    {
        temperatures.push_back(temperature);
        maxTemperature = *std::max_element(temperatures.begin(), temperatures.end());
        minTemperature = *std::min_element(temperatures.begin(), temperatures.end());
        avgTemperature = std::accumulate(temperatures.begin(), temperatures.end(), 0) / temperatures.size();
        display();
    }

    void display()
    {
        std::cout << "Avg/Max/Min temperature = " << avgTemperature << "/" << maxTemperature << "/" << minTemperature << std::endl;
    }
};


class HeatIndexDisplay : public Observer, DisplayElement
{
private:
    float heatIndex;
    Subject* weatherData;

public:
    HeatIndexDisplay(Subject* weatherData)
    {
        this->weatherData = weatherData;
        this->weatherData->registerObserver(this);
    }

    void update(float temperature, float humidity, float pressure)
    {
        heatIndex = 0;
        display();
    }

    void display()
    {
        std::cout << "Heat index is: " << heatIndex << std::endl;
    }
};



int main(int argc, char const *argv[])
{
    WeatherData wd;

    CurrentConditionsDisplay ccd(&wd);
    StaticsticsDisplay sd(&wd);
    HeatIndexDisplay hid(&wd);

    wd.setMeasurements(80, 65, 30.4f);
    wd.setMeasurements(82, 70, 29.2f);
    wd.setMeasurements(78, 90, 29.2f);

    return 0;
}
