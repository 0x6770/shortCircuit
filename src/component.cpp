#include "component.hpp"

Node *Component::get_node(string x)
{
    Node *node = (x == "p") ? _node_p : _node_n;
    return node;
}

bool Component::contain_node(string node)
{
    if (node == _node_p->get_name() || node == _node_n->get_name())
    {
        return true;
    }
    return false;
}

bool Component::check_grounded()
{
    return _is_grounded;
}

string Component::get_name()
{
    return _name;
}

double Component::get_voltage_across(double t, Node *node)
{
    double result = 0.0;
    return result;
}

double Component::get_current_through(Node *node)
{
    return _current_through;
}

double Component::get_current(Node *node)
{
    double result = 0.0;
    return result;
}

void Component::set_current_through(double current)
{
    _current_through = current;
}

void Component::set_voltage_across(double voltage)
{
}

double Component::get_property()
{
    return _property;
}

double Component::get_conductance()
{
    double result = 0.0;
    return result;
}

string Component::get_type()
{
    return _type;
}
