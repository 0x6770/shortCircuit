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
}

vector<Component *> Node::get_components()
{
    return _components;
};

void Node::add_components(Component *component)
{
    _components.push_back(component);
}

double Node::get_conductance(const double f, Node *node)
{
    double result = 0.0;
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
    return result;
};

string Node::get_name()
{
    return _name;
}

double Node::get_voltage(const double t)
{
    return _node_voltage;
}

double Node::get_current(const double t)
{
    double result = 0.0;
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        if ((*it)->get_type() == "I")
        {
            result += (*it)->get_current(t, this);
        }
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