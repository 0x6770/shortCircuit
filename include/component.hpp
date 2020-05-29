#ifndef component_hpp
#define component_hpp

#include "node.hpp"

#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>

using namespace std;

class Component
{
protected:
    string _type;
    string _name;
    Node *_node_p;
    Node *_node_n;
    double _property = 0;
    double _bias = 0.0;
    double _amplitude = 0.0;
    double _frequency = 0.0;
    bool _is_grounded = false;

public:
    Component() {}
    Node *get_node(string x)
    {
        Node *node = (x == "p") ? _node_p : _node_n;
        return node;
    }
    const bool contain_node(string node)
    {
        if (node == _node_p->get_name() || node == _node_n->get_name())
        {
            return true;
        }
        return false;
    }
    const bool check_grounded()
    {
        return _is_grounded;
    }
    const string get_name()
    {
        return _name;
    }
    virtual double get_voltage(double t, Node *node)
    {
        double result = 0.0;
        return result;
    }
    virtual double get_current(double t, Node *node)
    {
        double result = 0.0;
        return result;
    }
    virtual double get_property()
    {
        return _property;
    }
    virtual complex<double> get_conductance(double f)
    {
        complex<double> result = {0.0, 0.0};
        return result;
    }
    string get_type()
    {
        return _type;
    }
    virtual ~Component() {}
};

#endif