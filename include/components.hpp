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
    string _name;
    string _node_p;
    string _node_n;
    double _property = 0;
    double _bias = 0.0;
    double _amplitude = 0.0;
    double _frequency = 0.0;
    bool _is_grounded = false;

public:
    Component() {}
    const string get_node(string x)
    {
        string node = x == "p" ? _node_p : _node_n;
        return node;
    }
    const bool contain_node(string node)
    {
        if (node == _node_p || node == _node_n)
        {
            return true;
        }
        return false;
    }
    const bool check_grounded()
    {
        return _is_grounded;
    }
    const string get_name()
    {
        return _name;
    }
    virtual double get_voltage(double t, string node)
    {
        double result = 0.0;
        return result;
    }
    virtual double get_current(double t, string node)
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
    Inductor(string name, string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "L";
        _name = name;
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
    Capacitor(string name, string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "C";
        _name = name;
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
    Resistor(string name, string node_p, string node_n, double property)
    {
        assert(node_p != node_n);
        _type = "R";
        _name = name;
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
    Voltage(string name, string node_p, string node_n, double amplitude)
    {
        assert(node_p != node_n);
        _type = "V";
        _name = name;
        _node_p = node_p;
        _node_n = node_n;
        _amplitude = amplitude;
        if (contain_node("0"))
        {
            _is_grounded = true;
        }
    }

    double get_voltage(double t, string node)
    {
        if (node == _node_p)
        {
            return _amplitude;
        }
        else if (node == _node_n)
        {
            return -1.0 * _amplitude;
        }
        else
        {
            cerr << endl;
            cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
            cerr << endl;
            exit(1);
        }
    }
};

class SINE_Voltage : public Component
{
public:
    SINE_Voltage(string name, string node_p, string node_n, double bias, double amplitude, double frequency)
    {
        assert(node_p != node_n);
        _type = "V";
        _name = name;
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

    double get_voltage(double t, string node)
    {

        double result = _bias + _amplitude * sin(_frequency * t);
        if (node == _node_p)
        {
            return result;
        }
        else if (node == _node_n)
        {
            return -1.0 * result;
        }
        else
        {
            cerr << endl;
            cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
            cerr << endl;
            exit(1);
        }
        return result;
    }
};

class Current : public Component
{
protected:
public:
    Current(string name, string node_p, string node_n, double amplitude)
    {
        assert(node_p != node_n);
        _type = "I";
        _name = name;
        _node_p = node_p;
        _node_n = node_n;
        _amplitude = amplitude;
    }

    double get_current(double t, string node)
    {
        if (node == _node_p)
        {
            return _amplitude;
        }
        else if (node == _node_n)
        {
            return -1.0 * _amplitude;
        }
        else
        {
            cerr << endl;
            cerr << "🚧 ERROR: invalid node, " << node << " for " << _name << " not exit in " << _node_p << " and " << _node_n << endl;
            cerr << endl;
            exit(1);
        }
    }
};

#endif