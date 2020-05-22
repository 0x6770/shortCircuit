#ifndef components_hpp
#define components_hpp

#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <limits>

using namespace std;

class Component
{
protected:
    string _pin1;
    string _pin2;

public:
    Component(){};
    string getPin(int n)
    {
        string pin = n == 1 ? _pin1 : _pin2;
        return pin;
    }
    virtual complex<double> getValue(double f, double t){};
    virtual ~Component(){};
};

class Inductor : public Component
{
private:
    double _inductance;

public:
    Inductor(string pin1, string pin2, double inductance)
    {
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _inductance = inductance;
    }

    double getInductance(){
        return _inductance;
    }

    complex<double> getValue(double f, double t)
    {
        return complex<double>(0.0, -1.0 / (2.0 * M_PI * f * _inductance));
    }
};

class Capacitor : public Component
{
private:
    double _capacitance;

public:
    Capacitor(string pin1, string pin2, double capacitance)
    {
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _capacitance = capacitance;
    }

    double getCapacitance(){
        return _capacitance;
    }
    complex<double> getValue(double f, double t)
    {
        return complex<double>(0.0, 2.0 * M_PI * f * _capacitance);
    }
};

class Resistor : public Component
{
private:
    double _resistance;

public:
    Resistor(string pin1, string pin2, double resistance)
    {
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _resistance = resistance;
    }

    complex<double> getValue(double f, double t)
    {
        return complex<double>((1.0 / _resistance), 0.0);
    }
};

class DC_voltage: public Component{
private:
    double _voltage;
    double _frequency = 0;
public:
    DC_voltage(string pin1, string pin2, double voltage)
    {
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _voltage = voltage;
    }
    complex<double> getValue(double f, double t){
        return complex<double> (0.0,0.0);
    }
};

class current_source: public Component{
private:
    double _current;
public:
    current_source(string pin1, string pin2, double current){
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _current = current;
    }
    complex<double> getValue(double f, double t){
        return complex<double> (0.0,0.0);
    }

};



// voltage source
class Voltage : public Component
{
private:
    double _voltage;

public:
    Voltage(string pin1, string pin2, double voltage)
    {
        assert(pin1 != pin2);
        if (pin1 < pin2)
        {
            _pin1 = pin1;
            _pin2 = pin2;
        }
        else
        {
            _pin1 = pin2;
            _pin2 = pin1;
        }
        _voltage = voltage;
        // use "function" to initialise voltage member
    };
    ~Voltage(){};
    complex<double> getValue(double f, double t)
    {
        return complex<double>(_voltage);
    };
};

#endif