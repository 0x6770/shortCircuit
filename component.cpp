#include "component.hpp"
#include "node.hpp"
#include "circuit.hpp"

Component::Component(string temp_type, double val, Node* m1, Node* m2){
    type = temp_type;
    value = val;
    n1 = m1;
    n2 = m2;
    voltage = m1->get_voltage() - m2->get_voltage();
    if(type == "resistor"){
        current = -1 * get_voltage()/value;
    }else if(type == "current_source"){
        current = value;
    }else{
        current = 0;
    }
}


string Component::get_type(){
    return type;
}

bool Component::is_power_source(){
    if(type == "voltage_source" or type == "current_source"){
        return true;
    }
    return false;
}

Node* Component::get_node1(){
    return n1;
}

Node* Component::get_node2(){
    return n2;
}

double Component::get_voltage(){
    if(type == "voltage_source"){ return voltage; }
    return n1->get_voltage() - n2->get_voltage();
}

double Component::get_current(){
    if(type == "resistor"){
        return -1.00 * (get_voltage())/value;
    }else if(type == "current_source"){
        return value;
    }else{
        return 0;
    }
}

double Component::get_value(){
    return value;
}

complex<double> Component::get_conductance(){
    return conductance;
}