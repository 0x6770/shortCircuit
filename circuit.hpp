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
    Circuit(){};

    ~Circuit(){};

    Circuit(double f1, double t1, vector<Component*> temp){
        f = f1;
        t = t1;
        comp = temp;
    }

    vector<complex<double>> get_conductance(); //done & checked

    void store_conductance(); //requires work to be done

    double get_freq();
    double get_time();

    vector<Component*> get_comp();

    complex<double> get_node_conductance(Node *a, Node *b);
};

#endif
