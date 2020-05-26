#include "node.hpp"

void check_parallel_voltages(const string &node, Component *voltage, const vector<Component *> &voltages)
{
    string the_other_node = voltage->get_node("p") == node ? voltage->get_node("n") : voltage->get_node("p");
    for (auto it = voltages.begin(); it != voltages.end(); it++) // check parallel votage sources
    {
        if ((*it)->contain_node(the_other_node))
        {
            cerr << endl;
            cerr << "🚧 ERROR: paralleled voltage sources present"
                 << "\t" << (*it)->get_name() << " and " << voltage->get_name() << endl;
            cerr << endl;
            exit(1);
        }
    }
}

Node::Node(const vector<Component *> components, const string name)
{
    _name = name;
    _components = components;
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component *this_comp = (*it);
        assert(this_comp->contain_node(_name));
        is_voltage_or_current(*it);
    }
}

void Node::is_voltage_or_current(Component *comp)
{
    if (comp->get_type() == "V") // check if there is voltage source
    {
        check_parallel_voltages(_name, comp, _voltages);
        _contain_voltage = true;
        _voltages.push_back(comp);
        if (comp->check_grounded()) // check if the voltage source is grounded
        {
            _voltage_state = "g";
        }
        else if (!comp->check_grounded() && _voltage_state != "g") // current voltage source is not grounded and not grounded voltage source presents
        {
            if (comp->get_node("p") == _name) // check if the current node is the positive node of the floating voltage source
            {
                _voltage_state = "p";
            }
            else
            {
                _voltage_state = "n";
            }
        }
    }
    else if (comp->get_type() == "I") //check if therer is current source
    {
        _contain_current = true;
        _voltages.push_back(comp);
    }
}

const vector<Component *> Node::get_components()
{
    return _components;
};

const complex<double> Node::get_conductance(const double f, const string node)
{
    complex<double> result = {0.0, 0.0};
    if (_voltage_state == "")
    {
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
    }
    else if (_voltage_state == "g")
    {
        if (node == _name)
        {
            result = {1.0, 0.0};
        }
    }
    else if (_voltage_state == "p")
    {
        if (node == _name)
        {
            result = {1.0, 0.0};
        }
        else if (node == _voltages[0]->get_node("n"))
        {
            result = {-1.0, 0.0};
        }
    }
    else if (_voltage_state == "n")
    {
        // assert(_super_node_positive);
        // if (node == _name)
        // {
        //     for (auto it = _components.begin(); it != _components.end(); it++) // sum up the conductance of all components connected to the Negative terminal of the current super node
        //     {
        //         result += (*it)->get_conductance(f);
        //     }
        //     for (auto it = _super_node_positive->_components.begin(); it != _super_node_positive->_components.end(); it++) // sum up the conductance of all components connected to the Positive terminal of the current super node
        //     {
        //         result += (*it)->get_conductance(f);
        //     }
        // }
        // else
        // {
        //     for (auto it = _components.begin(); it != _components.end(); it++) // sum up the conductance of all components of between the Negative terminal of the current super node and a specific node
        //     {
        //         if ((*it)->contain_node(node))
        //         {
        //             result -= (*it)->get_conductance(f);
        //         }
        //     }
        //     for (auto it = _super_node_positive->_components.begin(); it != _super_node_positive->_components.end(); it++) // sum up the conductance of all components of between the Positive terminal of the current super node and a specific node
        //     {
        //         if ((*it)->contain_node(node))
        //         {
        //             result -= (*it)->get_conductance(f);
        //         }
        //     }
        // }
    }

    return result;
};

double Node::get_value(const double t)
{
    double result = 0.0;
    if (_contain_voltage && !(_voltage_state == "n"))
    {
        return get_voltage(t);
    }
    else
    {
        return get_current(t);
    }
}

string Node::get_voltage_state()
{
    return _voltage_state;
}

string Node::get_name()
{
    return _name;
}

double Node::get_voltage(const double t)
{
    // assert(_contain_voltage);
    // cout << _voltages.size() << " _voltages in total\t";
    double result = 0.0;
    for (auto it = _voltages.begin(); it != _voltages.end(); it++)
    {
        result += (*it)->get_voltage(t, _name);
    }
    return result;
}

double Node::get_current(const double t)
{
    // assert(_contain_current);
    // cout << _currents.size() << " _currents in total\t";
    double result = 0.0;
    for (auto it = _currents.begin(); it != _currents.end(); it++)
    {
        result += (*it)->get_current(t, _name);
    }
    return result;
}

void link_super_node(const vector<Node *> &nodes)
{
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if ((*it)->get_voltage_state() == "n")
        {
            // string node = (*it)->get
            for (auto jt = nodes.begin(); jt != nodes.end(); jt++)
            {
            }
        }
    }
}