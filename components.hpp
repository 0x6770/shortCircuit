#ifndef components_hpp
#define components_hpp

#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>

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
    virtual string get_type(){};
    virtual double getFrequency(){};
    virtual ~Component(){};
    
};

class Inductor : public Component
{
private:
    double _inductance;
    string _type = "inductor";

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
    string get_type(){
        return _type;
    }

    double cache_current(double t){
        //return the current at time t
    }

    double get_voltage(double t){
        //require an extra parameter: timestep
        //require a library for numerical differentiation
        //return differentiate(cache_current(t - timestep))*L with respect to t
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
    string _type = "capacitor";

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

    string get_type(){
        return _type;
    }
    double cache_current(double t){
        //to store the current at time t
    }

    double get_voltage(double t){
        //require an extra parameter: timestep
        //require a library for numerical integration
        //return integrate(cache_current(t - timestep)/C) with respect to t
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
    string _type = "resistor";
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
    string get_type(){
        return _type;
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
    string _type = "power_source";
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
    double getFrequency(){
        return _frequency;
    }
    double getVoltage(double t){
        return _voltage;
    }
    complex<double> getValue(double f, double t){
        return complex<double> (0.0,0.0);
    }

    string get_type(){
        return _type;
    }
};

class SIN_voltage: public Component{
private:
    double _amplitude;
    double _frequency;
    string _type = "power_source";
public:
    SIN_voltage(string pin1, string pin2, double amplitude, double frequency)
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
        _amplitude = amplitude;
        _frequency = frequency;
    }
    double getFrequency(){
        return _frequency;
    }
    double getVoltage(double t){
        double result;
        result = _amplitude * sin(2.0 * M_PI * _frequency * t);
        return result;
    }
    complex<double> getValue(double f, double t){
        return complex<double> (0.0,0.0);
    }

    string get_type(){
        return _type;
    }
};


class current_source: public Component{
private:
    double _current;
    string _type = "power_source";
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
    double getCurrent(double t){
        return _current;
    }
    string get_type(){
        return _type;
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
    string _type = "power_source";

public:
    string get_type(){
        return _type;
    }

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