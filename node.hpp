#ifndef node_hpp
#define node_hpp

#include <iostream>
#include <vector>
#include <string>
#include <complex>

using namespace std;

class Component;

class Circuit;

class Node{
private:
    double voltage;
    vector<Component*> components;
    bool isGround;
    string name; //optional: better to add a name to each node

public:
    Node(){};

    ~Node(){};

    double get_voltage();
    bool is_ground();
    int get_num_of_components();
    vector<Component*> get_components();

};





#endif
