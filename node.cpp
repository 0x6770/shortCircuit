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