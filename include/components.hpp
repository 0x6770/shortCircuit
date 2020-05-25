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
    string _type;
    string _node_p;
    string _node_n;
    double _property = 0;
    double _bias = 0.0;
    double _amplitude = 0.0;
    double _frequency = 0.0;
    bool _is_grounded = false;

public:
    Component() {}
    string get_node(string x)
    {
        string node = x == "p" ? _node_p : _node_n;
        return node;
    }
    bool contain_node(string node)
    {
        if (node == _node_p || node == _node_n)
        {
            return true;
        }
        return false;
    }
    bool check_grounded()
    {
        return _is_grounded;
    }
    virtual double get_voltage(double t)
    {
        double result = 0.0;
        return result;
    }
    virtual double get_current(double t)
    {
        double result = 0.0;
        return result;
    }
    virtual complex<double> get_conductance(double f)
    {
        complex<double> result = {0.0, 0.0};
        return result;
    }
    string get_type()
    {
        return _type;
    }
    virtual ~Component() {}
};

class Inductor : public Component
{
public:
    Inductor(string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "L";
        _node_p = node_p;
        _node_n = node_n;
        _property = property;
    }

    complex<double> get_conductance(double f)
    {
        return complex<double>(0.0, -1.0 / (2.0 * M_PI * f * _property));
    }
};

class Capacitor : public Component
{
public:
    Capacitor(string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "C";
        _node_p = node_p;
        _node_n = node_n;
        _property = property;
    }

    complex<double> get_conductance(double f)
    {
        return complex<double>(0.0, 2.0 * M_PI * f * _property);
    }
};

class Resistor : public Component
{
public:
    Resistor(string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "R";
        _node_p = node_p;
        _node_n = node_n;
        _property = property;
    }

    complex<double> get_conductance(double f)
    {
        return complex<double>((1.0 / _property), 0.0);
    }
};

class Voltage : public Component
{
public:
    Voltage(string node_p, string node_n, double amplitude)
    {
        assert(node_p != node_n);
        _type = "V";
        _node_p = node_p;
        _node_n = node_n;
        _amplitude = amplitude;
        if (contain_node("0"))
        {
            _is_grounded = true;
        }
    }

    double get_voltage(double t)
    {
        return _amplitude;
    }
};

class SINE_Voltage : public Component
{
public:
    SINE_Voltage(string node_p, string node_n, double bias, double amplitude, double frequency)
    {
        assert(node_p != node_n);
        _type = "V";
        _node_p = node_p;
        _node_n = node_n;
        _bias = bias;
        _amplitude = amplitude;
        _frequency = frequency;
        if (contain_node("0"))
        {
            _is_grounded = true;
        }
    }

    double get_voltage(double t)
    {
        double result = _bias + _amplitude * sin(_frequency * t);
        return result;
    }
};

class Current : public Component
{
protected:
public:
    Current(string node_p, string node_n, double amplitude)
    {
        assert(node_p != node_n);
        _type = "I";
        _node_p = node_p;
        _node_n = node_n;
        _amplitude = amplitude;
    }

    double get_current(double t)
    {
        return _amplitude;
    }
};

#endif