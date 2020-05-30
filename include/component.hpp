#ifndef component_hpp
#define component_hpp

#include "node.hpp"

#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cassert>
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

    string get_type();

    string get_name();

    Node *get_node(string x);

    virtual double get_voltage(double t, Node *node);

    virtual double get_current(double t, Node *node);

    virtual double get_property();

    virtual double get_conductance(double f);

    bool contain_node(string node);

    bool check_grounded();

    virtual ~Component() {}
};

#endif