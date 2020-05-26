#ifndef TRANSIENT_SIMULATOR_NODE_HPP
#define TRANSIENT_SIMULATOR_NODE_HPP

#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include "Component.hpp"
using namespace std;

class node {
private:
    int _number;
    //default value for current and voltage are zero
    // if want to use the library for Ax = b, these types must be consistent.
    complex<double> _current = (0.0,0.0) ;
    complex<double> _voltage = (0.0,0.0) ;
    vector<Component*> _branches;
    bool connected_current = false;
    bool connected_voltage = false;
public:
    //empty node constructors
    node(int id){
        _number = id;
    };

    bool is_connect_current();

    bool is_connect_voltage();

    complex<double> get_current();

    complex<double> get_voltage();

    int get_number();

    void add_branches(Component* branch);

    vector<Component*> get_branches();

    bool operator==(node * a);

    bool is_super_node();

    bool is_connected_current();

    bool is_connected_voltage();

    void set_current();
};


#endif //TRANSIENT_SIMULATOR_NODE_HPP
