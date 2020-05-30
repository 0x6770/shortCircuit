#include "components.hpp"

Inductor::Inductor(string name, string node_p, string node_n, double property)
{
    assert(node_p != node_n);
    _type = "L";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

complex<double> Inductor::get_conductance(double f)
{
    return complex<double>(0.0, -1.0 / (2.0 * M_PI * f * _property));
}

Capacitor::Capacitor(string name, string node_p, string node_n, double property)
{
    assert(node_p != node_n);
    _type = "C";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

complex<double> Capacitor::get_conductance(double f)
{
    return complex<double>(0.0, 2.0 * M_PI * f * _property);
}

Resistor::Resistor(string name, string node_p, string node_n, double property)
{
    assert(node_p != node_n);
    _type = "R";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

complex<double> Resistor::get_conductance(double f)
{
    return complex<double>((1.0 / _property), 0.0);
}

Voltage::Voltage(string name, string node_p, string node_n, double amplitude)
{
    assert(node_p != node_n);
    _type = "V";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _amplitude = amplitude;
}

double Voltage::get_voltage(double t, string node)
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

SINE_Voltage::SINE_Voltage(string name, string node_p, string node_n, double bias, double amplitude, double frequency)
{
    assert(node_p != node_n);
    _type = "V";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _bias = bias;
    _amplitude = amplitude;
    _frequency = frequency;
}

double SINE_Voltage::get_voltage(double t, string node)
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

Current::Current(string name, string node_p, string node_n, double amplitude)
{
    assert(node_p != node_n);
    _type = "I";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _amplitude = amplitude;
}

double Current::get_current(double t, string node)
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