#include "node.hpp"
#include "component.hpp"
#include "circuit.hpp"
using namespace std;


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
