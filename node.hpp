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
    // if want to use the library for Ax = b, assuming these types must be consistent.
    complex<double> _current = (0.0,0.0) ;
    complex<double> _voltage = (0.0,0.0) ;
    vector<Component*> _branches;
public:
    //empty node constructors
    node(string name){
        if(name == "0"){
            _number = stoi(name);
        }
        else {
            string temp;
            for(int i = 1; i < name.size();i++){
                temp.push_back(name[i]);
            }
            _number = stoi(temp);
        }
    };

    void get_current();

    void get_voltage();

    int get_number();

    void add_branches(Component* branch);

    vector<Component*> get_branches();

    bool operator==(node * a);
};


#endif //TRANSIENT_SIMULATOR_NODE_HPP
