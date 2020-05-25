#include "node.hpp"

Node::Node(vector<Component *> components, string name)
{
    _name = name;
    _components = components;
    contain_voltage_or_current();
}

void Node::contain_voltage_or_current()
{
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        if ((*it)->get_type() == "V") // check if there is voltage source
        {
            _contain_voltage = true;
            _voltages.push_back(*it);
            if (!(*it)->check_grounded()) // check if the voltage source is grounded
            {
                if ((*it)->get_node("p") == _name) // check if the current node is the positive node of the floating voltage source
                {
                    _super_node = "p";
                }
                else
                {
                    _super_node = "n";
                }
            }
        }
        else if ((*it)->get_type() == "I") //check if therer is current source
        {
            _contain_current = true;
            _voltages.push_back(*it);
        }
    }
}

complex<double> Node::get_conductance(double f, string node)
{
    complex<double> result = {0.0, 0.0};
    if (node == _name)
    {
        for (auto it = _components.begin(); it != _components.end(); it++) // sum up the conductance of all components
        {
            result += (*it)->get_conductance(f);
        }
    }
    else
    {
        for (auto it = _components.begin(); it != _components.end(); it++) // sum up the conductance of all components that contains "node"
        {
            if ((*it)->contain_node(node))
            {
                result -= (*it)->get_conductance(f);
            }
        }
    }
    return result;
};

// complex<double> Node::get_node_conductance(double f)
// {
//     complex<double> result = {0.0, 0.0};
//     for (auto it = _components.begin(); it != _components.end(); it++)
//     {
//         result += (*it)->get_conductance(f);
//     }
//     return result;
// };

double Node::get_value(double t)
{
    double result = 0.0;
    if (_contain_voltage && (_super_node == "p"))
    {
        get_voltage(t);
    }
    else
    {
        get_current(t);
    }
}

double Node::get_voltage(double t)
{
    assert(!_contain_voltage);
    double result = 0.0;
    for (auto it = _voltages.begin(); it != _voltages.end(); it++)
    {
        result += (*it)->get_voltage(t);
    }
    return result;
}

double Node::get_current(double t)
{
    assert(!_contain_current);
    double result = 0.0;
    for (auto it = _currents.begin(); it != _currents.end(); it++)
    {
        result += (*it)->get_current(t);
    }
    return result;
}