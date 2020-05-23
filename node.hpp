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

    Node(double vol, vector<Component*> temp, bool ground){
        voltage = vol;
        components = temp;
        isGround = ground;
    }

    ~Node(){};

    void set_node(double vol, vector<Component*> temp,bool ground);

    double get_voltage(); //checked
    bool is_ground(); //checked
    int get_num_of_components(); //checked
    vector<Component*> get_components();

};





#endif
