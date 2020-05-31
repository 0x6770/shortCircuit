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
    double _frequency = 0.0;
    bool _is_grounded = false;
    double _current_through = 0.0;
    double _voltage_across = 0.0;

public:
    Component() {}

    string get_type();

    string get_name();

    Node *get_node(string x);

    virtual double get_voltage_across(double t, Node *node);

    virtual double get_current(Node *node);

    virtual double get_current_through(Node *node);

    virtual double get_property();

    virtual double get_conductance();

    virtual void set_current_through(double current);

    virtual void set_voltage_across(double voltage);

    bool contain_node(string node);

    bool check_grounded();

    virtual ~Component() {}
};

#endif