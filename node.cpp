#include "node.hpp"

void node::get_voltage() {

}

void node::get_current() {

}

void node::add_branches(Component *branch) {
    _branches.push_back(branch);
}

vector<Component*> node::get_branches() {
    return _branches;
}

int node::get_number() {
    return _number;
}

bool node::operator==(node * a){
    if(_number = a->get_number())
        return true;
    return false;
}