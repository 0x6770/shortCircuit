#ifndef circuit_hpp
#define circuit_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>

class Component;

class Node;

class Circuit{
private:
    double f;
    double t;
    vector<Component*> comp;
    vector<complex<double>> conductance;

public:
    vector<complex<double>> get_conductance();

    void store_conductance();

    double get_freq();
    double get_time();

    vector<Component*> get_comp();

    complex<double> get_node_conductance(Node *a, Node *b); //TODO
};

#endif
