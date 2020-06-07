#include "component.hpp"

Node *Component::get_node(string x)
{
    Node *node = (x == "p") ? _node_p : _node_n;
    return node;
}

bool Component::contain_node(string node)
{
    if (node == _node_p->get_name() or node == _node_n->get_name())
    {
        return true;
    }
    return false;
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
        spdlog::error("🚧 ERROR: invalid node, {} not exit in {} and {}.", node->get_name(), _node_p->get_name(), _node_n->get_name());
        exit(1);
    }
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
