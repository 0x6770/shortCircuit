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

    Component(string temp_type, double val); //default input

    void set_node(Node *m1, Node *m2); //function to set node

    Component(){};

    ~Component(){};

    double get_voltage(); //done & checked
    double get_current(); //TODO: missing capacitor and inductor //checked for resistor
    double get_value(); //done &  checked
    complex<double> get_conductance(); //done & checked
    Node* get_node1(); //done
    Node* get_node2(); //done
    string get_type(); //done & checked
    bool is_power_source(); //return true if type == voltage_source or current_source
    friend class Circuit; //can access any member in this class

    void set_comp(string type1, double value1, Node* m1, Node* m2);

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
