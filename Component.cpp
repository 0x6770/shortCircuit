#include "Component.hpp"

int Component::get_node(int n) {
    if(n == 1)
        return _n1;
    if(n == 2)
        return _n2;
}

double Component::get_value() {
    return _value;
}

string Component::get_identifier() {
    return _identifier;
}

bool Component::is_current() {
    if(_identifier[0] == 'I')
        return true;
    return false;
}

bool Component::is_voltage() {
    if (_identifier[0] == 'V')
        return true;
    return false;
}

bool Component::is_passive() {
    if(_identifier[0] == 'L' or _identifier[0] == 'C')
        return true;
    return false;
}

int Component::convert_node_to_int(string a){
    if(a == "0"){
        return stoi(a);
    }
    else{
        string temp;
        temp = a.substr(1,3);
        return stoi(temp);
    }
}

bool Component::is_grounded(){
    if(_n1 == 0 or _n2 == 0){
        return true;
    }
    return false;
}

double SIN::get_real_voltage(double time){
    if(time == 0){
        return dc_offset;
    }
    _value = dc_offset + ac_amplitude * sin(2 * M_PI * frequency * time);
    return _value;
}