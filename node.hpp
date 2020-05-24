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
    bool isGround = false;
    string name;

public:
    Node(){}; //(1)

    Node(double vol, vector<Component*> temp, bool ground); //not frequently used (2)

    Node(double vol, bool ground); //frequently used (3)

    Node(vector<Component*> temp, bool ground); //frequently used (4)

    bool check_equal(Node *a, Node *b);


    ~Node(){};

    void set_node(double vol, vector<Component*> temp,bool ground); //match with (1)

    void set_node(vector<Component*> temp); //match with (3)

    void set_voltage(double vol); //match with (4)

    void set_name(string temp); //node name is set when component is read

    void store_comp(Component* t); //store component in node

    double get_voltage(); //checked
    bool is_ground(); //checked
    int get_num_of_components(); //checked
    string get_name(); //checked
    vector<Component*> get_components();
    void set_is_ground();

    bool operator==(Node *a);

};





#endif
