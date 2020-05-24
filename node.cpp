#include "node.hpp"
#include "component.hpp"
#include "circuit.hpp"
using namespace std;
#include <cassert>

Node::Node(double vol, vector<Component*> temp, bool ground){
    voltage = vol;
    components = temp;
    isGround = ground;
    assert(isGround and vol == 0);
    if(is_ground()){ voltage = 0; }
}

Node::Node(vector<Component*> temp, bool ground){
    components = temp;
    isGround = ground;
    if(is_ground()){ voltage = 0; }
}



double Node::get_voltage(){
    return voltage;
}

int Node::get_num_of_components(){
    return components.size();
}

bool Node::is_ground(){
    return isGround;
}

vector<Component*> Node::get_components(){
    return components;
}

void Node::set_node(double vol, vector<Component*> temp,bool ground){
    voltage = vol;
    components = temp;
    isGround = ground;
    if(is_ground()){ voltage = 0;}
}

void Node::set_node(vector<Component*> temp){
    components = temp;
}

void Node::set_voltage(double vol){
    voltage = vol;
}

void Node::set_name(string temp){
    name = temp;
}