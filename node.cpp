#include "node.hpp"
#include "Component.hpp"

complex<double> node::get_voltage() {
    return _voltage;
}

complex<double> node::get_current() {
    return _current;
}

void node::add_branches(Component *branch) {
    _branches.push_back(branch);
    if(branch->is_current()){
        connected_current = true;
    }
    if(branch->is_voltage()){
        connected_voltage = true;
    }
}

vector<Component*> node::get_branches() {
    return _branches;
}

int node::get_number() {
    return _number;
}

bool node::operator==(node * a){
    if(_number == a->get_number())
        return true;
    return false;
}

bool node::is_super_node(){
    if(connected_voltage){
        for(int i = 0; i<_branches.size(); i++){
            if(_branches[i]->is_grounded() && _branches[i]->is_voltage()) {
                return false;
            }
            }
        return true;
    }
    return false;
}

bool node::is_connected_current(){
    for(int i = 0; i < _branches.size();i++){
        if(_branches[i]->is_current())
            return true;
    }
    return false;
}

bool node::is_connected_voltage(){
    for(int i = 0; i < _branches.size();i++){
        if(_branches[i]->is_voltage())
            return true;
    }
    return false;
}

//useful when setting the Ax = b, b_column matrix
void node::set_current(){
    if(connected_current && !(connected_voltage)){
        for(int i = 0; i<_branches.size();i++){
            if(_branches[i]->is_current()){
                if(_branches[i]->get_node(1) == _number){
                    _current = _current + (complex<double>)_branches[i]->get_value();
                }
                else if(_branches[i]->get_node(2) == _number){
                    _current = _current - (complex<double>)_branches[i]->get_value();
                }
            }
        }
    }
}



bool node::is_connect_current(){
    return false;
}

bool node::is_connect_voltage(){
    return false;
}