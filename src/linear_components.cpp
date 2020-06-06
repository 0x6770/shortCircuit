#include "linear_components.hpp"

Inductor::Inductor(string name, Node *node_p, Node *node_n, double property)
{
    assert(node_p != node_n);
    _type = "L";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _property = property;
}

double Inductor::get_current(Node *node)
{
    if (node == _node_p)
    {
        return _current_through;
    }
    else if (node == _node_n)
    {
        return -1.0 * _current_through;
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
        cerr << endl;
        exit(1);
    }
};

double Inductor::get_current_through(Node *node)
{
    return get_current(node);
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

double Capacitor::get_voltage_across(double t, Node *node)
{
    if (node == _node_p)
    {
        return _voltage_across;
    }
    else if (node == _node_n)
    {
        return -1.0 * _voltage_across;
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
        cerr << endl;
        exit(1);
    }
}

void Capacitor::set_voltage_across(double voltage)
{
    _voltage_across = voltage;
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

double Resistor::get_conductance()
{
    return double(1.0 / _property);
}

double Resistor::get_current_through(Node *node)
{
    double direction = (node == _node_p) ? 1.0 : -1.0;
    double magnitude = (_node_p->get_node_voltage() - _node_n->get_node_voltage()) / _property;
    return direction * magnitude;
}

Voltage::Voltage(string name, Node *node_p, Node *node_n, double amplitude)
{
    assert(node_p != node_n);
    _type = "V";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _voltage_across = amplitude;
}

double Voltage::get_voltage_across(double t, Node *node)
{
    if (node == _node_p)
    {
        return _voltage_across;
    }
    else if (node == _node_n)
    {
        return -1.0 * _voltage_across;
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
        cerr << endl;
        exit(1);
    }
}

double Voltage::get_current_through(Node *node)
{
    return _current_through;
}

void Voltage::set_current_through(double current)
{
    _current_through = current;
}

SINE_Voltage::SINE_Voltage(string name, Node *node_p, Node *node_n, double bias, double amplitude, double frequency)
{
    assert(node_p != node_n);
    _type = "V";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _bias = bias;
    _voltage_across = amplitude;
    _frequency = frequency;
}

double SINE_Voltage::get_voltage_across(double t, Node *node)
{
    double result = _bias + _voltage_across * sin(2 * M_PI * _frequency * t);
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

double SINE_Voltage::get_current_through(Node *node)
{
    return _current_through;
}

void SINE_Voltage::set_current_through(double current)
{
    _current_through = current;
}

Current::Current(string name, Node *node_p, Node *node_n, double amplitude)
{
    assert(node_p != node_n);
    _type = "I";
    _name = name;
    _node_p = node_p;
    _node_n = node_n;
    _current_through = amplitude;
}

double Current::get_current(Node *node)
{
    if (node == _node_p)
    {
        return _current_through;
    }
    else if (node == _node_n)
    {
        return -1.0 * _current_through;
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid node, " << node << " for " << _name << " not exit in " << _node_p << " and " << _node_n << endl;
        cerr << endl;
        exit(1);
    }
}

double Current::get_current_through(Node *node)
{
    return get_current(node);
}