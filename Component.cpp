//
// Created by 44736 on 25/05/2020.
//

#include "Component.hpp"

string Component::get_node(int n) {
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
    if(_identifier[0] = 'I')
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

