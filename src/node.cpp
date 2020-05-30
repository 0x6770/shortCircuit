#include "components.hpp"

void check_parallel_voltages(Node *node, Component *voltage, const vector<Component *> &voltages)
{
    Node *the_other_node = voltage->get_node("p") == node ? voltage->get_node("n") : voltage->get_node("p");
    for (auto it = voltages.begin(); it != voltages.end(); it++) // check parallel votage sources
    {
        if ((*it)->contain_node(the_other_node->get_name()))
        {
            cerr << endl;
            cerr << "🚧 ERROR: paralleled voltage sources present"
                 << "\t" << (*it)->get_name() << " and " << voltage->get_name() << endl;
            cerr << endl;
            exit(1);
        }
    }
}

Node::Node(const string name)
{
    _name = name;
    // _components = components;
    // for (auto it = components.begin(); it != components.end(); it++)
    // {
    //     Component *this_comp = (*it);
    //     assert(this_comp->contain_node(_name));
    //     is_voltage_or_current(*it);
    // }
}

void Node::is_voltage_or_current(Component *comp)
{
    if (comp->get_type() == "V") // check if there is voltage source
    {
        check_parallel_voltages(this, comp, _voltages);
        _contain_voltage = true;
        _voltages.push_back(comp);
        if (comp->check_grounded()) // check if the voltage source is grounded
        {
            _voltage_state = "g";
        }
        else if (!comp->check_grounded() && _voltage_state != "g") // current voltage source is not grounded and not grounded voltage source presents
        {
            _voltage_state = "f";
            // if (comp->get_node("p") == this) // check if the current node is the positive node of the floating voltage source
            // {
            //     _voltage_state = "p";
            // }
            // else
            // {
            //     _voltage_state = "n";
            // }
        }
    }
    else if (comp->get_type() == "I") //check if therer is current source
    {
        _contain_current = true;
        _voltages.push_back(comp);
    }
}

vector<Component *> Node::get_components()
{
    return _components;
};

void Node::add_components(Component *component)
{
    _components.push_back(component);
    is_voltage_or_current(component);
}

bool used_super_node_voltage(vector<Component *> used_voltages, Component *voltage)
{
    int occurance = 0;
    for (auto it = used_voltages.begin(); it != used_voltages.end(); it++)
    {
        if ((*it) == voltage)
        {
            occurance++;
        }
    }
    if (occurance < 2)
    {
        return false;
    }
    return true;
}

double Node::get_conductance(const double f, Node *node)
{
    double result = 0.0;
    // if (_voltage_state == "")
    // {
    if (node->get_name() == _name)
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
            if ((*it)->contain_node(node->get_name()))
            {
                result -= (*it)->get_conductance(f);
            }
        }
    }
    // }
    // else if (_voltage_state == "g")
    // {
    //     if (node->get_name() == _name)
    //     {
    //         result = {1.0, 0.0};
    //     }
    // }
    // else if (_voltage_state == "f")
    // {
    //     // if (node->get_name() == _name)
    //     // {
    //     for (auto it = _voltages.begin(); it != _voltages.end(); it++)
    //     {
    //         if (((*it)->get_node("p") == node))
    //         {
    //             result = {1.0, 0.0};
    //         }
    //         else if (((*it)->get_node("n") == node))
    //         {
    //             result = {-1.0, 0.0};
    //         }
    //     }
    // }
    // else if (node == _voltages[0]->get_node("n"))
    // {
    //     result = {-1.0, 0.0};
    // }
    // }
    // else if (_voltage_state == "n")
    // {
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
    // }

    return result;
};

// double Node::get_value(const double t)
// {
//     double result = 0.0;
//     if (_contain_voltage)
//     {
//         return get_voltage(t);
//     }
//     else
//     {
//         return get_current(t);
//     }
// }

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
        result += (*it)->get_voltage(t, this);
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
        result += (*it)->get_current(t, this);
    }
    return result;
}

ostream &operator<<(ostream &os, Node &node)
{
    os << node.get_name();
    return os;
};

bool compare_node(Node *node_a, Node *node_b)
{
    return node_a->get_name() < node_b->get_name();
}

Node *get_or_create_node(vector<Node *> &nodes, const string &node)
{
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if ((*it)->get_name() == node)
        {
            // cerr << "💡 found node " << node << endl;
            return (*it);
        }
    }
    Node *new_node = new Node(node);
    // cerr << "new node created " << *new_node << endl;
    nodes.push_back(new_node);
    sort(nodes.begin(), nodes.end(), compare_node);
    return new_node;
}