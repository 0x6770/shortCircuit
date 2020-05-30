#ifndef component_hpp
#define component_hpp

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
    string _node_p;
    string _node_n;
    double _property = 0.0;
    double _bias = 0.0;
    double _amplitude = 0.0;
    double _frequency = 0.0;

public:
    Component() {}
    string get_node(string x);

    string get_name();

    string get_type();

    virtual double get_property();

    virtual double get_voltage(double t, string node);

    virtual double get_current(double t, string node);

    virtual complex<double> get_conductance(double f);

    bool is_grounded();

    virtual ~Component() {}
};

#endif