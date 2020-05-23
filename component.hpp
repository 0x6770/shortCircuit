#ifndef component_hpp
#define component_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include <complex>

using namespace std;

class Node;

class Circuit;

class Component{
public:
    Component(string temp_type, double val, Node* m1, Node* m2);

    Component(){};

    ~Component(){};

    double get_voltage(); //done
    double get_current(); //TODO: missing capacitor and inductor
    double get_value(); //done
    complex<double> get_conductance();
    Node* get_node1(); //done
    Node* get_node2(); //done
    string get_type(); //return type
    bool is_power_source(); //return true if type == voltage_source or current_source
    void store_conductance(complex<double> temp);

private:
    Node* n1;
    Node* n2;
    double voltage;
    double current;
    double value;
    complex<double> conductance;
    string type; //type == "current_source" or "voltage_source" or "resistor" or "inductor" or "capacitor"

};


#endif
