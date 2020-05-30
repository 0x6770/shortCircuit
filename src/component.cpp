#include "component.hpp"

string Component::get_node(string x)
{
    string node = (x == "p") ? _node_p : _node_n;
    return node;
}

string Component::get_name()
{
    return _name;
}

string Component::get_type()
{
    return _type;
}

double Component::get_property()
{
    return _property;
}

double get_voltage(double t, string node)
{
    double result = 0.0;
    return result;
}
double get_current(double t, string node)
{
    double result = 0.0;
    return result;
}

bool Component::is_grounded()
{
    if (_node_p == "0" or _node_n == "0")
    {
        return true;
    }
    return false;
}

complex<double> Component::get_conductance(double f)
{
    complex<double> result = {0.0, 0.0};
    return result;
}
