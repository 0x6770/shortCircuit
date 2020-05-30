#include "components.hpp"

Inductor::Inductor(string name, Node *node_p, Node *node_n, double property)
{
    assert(node_p != node_n);
    _type = "L";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

Capacitor::Capacitor(string name, Node *node_p, Node *node_n, double property)
{
    assert(node_p != node_n);
    _type = "C";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

Resistor::Resistor(string name, Node *node_p, Node *node_n, double property)
{
    assert(node_p != node_n);
    _type = "R";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

double Resistor::get_conductance(double f)
{
    return double(1.0 / _property);
}

Voltage::Voltage(string name, Node *node_p, Node *node_n, double amplitude)
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

double Voltage::get_voltage(double t, Node *node)
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

SINE_Voltage::SINE_Voltage(string name, Node *node_p, Node *node_n, double bias, double amplitude, double frequency)
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

double SINE_Voltage::get_voltage(double t, string node)
{

    double result = _bias + _amplitude * sin(_frequency * t);
    if (node == _node_p->get_name())
    {
        return result;
    }
    else if (node == _node_n->get_name())
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

Current::Current(string name, Node *node_p, Node *node_n, double amplitude)
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
    if (node == _node_p->get_name())
    {
        return _amplitude;
    }
    else if (node == _node_n->get_name())
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
