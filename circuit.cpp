#include "circuit.hpp"

vector<node*> circuit::get_node_no_ground(){
    return _node_no_ground;
}

// TODO: might needed to consider more about AC power source
complex<double> circuit::single_conductance(Component* a){
    if(a->get_identifier()[0] == 'R'){
        a->_conductance = complex<double> (1.0/a->get_value(),0.0);
        return a->_conductance;
    }
    else if(a->get_identifier()[0] == 'C'){
        if(_time == 0){ a->_voltage = 0; a->_current = 0;}

        a->_conductance = complex<double> (0.0,2.0*M_PI*_frequency*a->get_value());
        return a->_conductance;
    }
    else if(a->get_identifier()[0] == 'L'){
        a->_conductance = complex<double> (0.0,-1.0*(1.0/(a->get_value()*2*M_PI*_frequency)));
        return a->_conductance;
    }
        a->_conductance = complex<double>(0.0,0.0);
        return a->_conductance; //added complex<double>
}

//without supper node
complex<double> circuit::conductance_between_nodes(node *a,node *b){
    complex<double> output = complex<double>(0.0,0.0);
    vector<Component*> x  = a->get_branches();
    vector<Component*> y  = b->get_branches();
    for(auto it = x.begin(); it != x.end(); ++it){
        if(find(y.begin(),y.end(),*it) != y.end()){
            output += single_conductance(*it);
        }
    }
    if(!(a == b)){
        output = (complex<double>) -1.0 * output;
    }
    return output;
}

void circuit::pure_node_matrix_row(node* a) {
    int row =  a->get_number();
    for(int k = 0; k < _node_no_ground.size();k++){
        int col =  _node_no_ground[k]->get_number();
        pair<int,int> temp = make_pair(row,col);
        conductance_matrix[temp] = conductance_between_nodes(a,_node_no_ground[k]);
    }
    column_matrix[row] = (complex<double>)a->get_current();
}

void circuit::equation_matrix(node* a){
    int row = a->get_number();
    auto it1 = forward_nodes.find(row);
    auto it2 = backward_nodes.find(row);
    // difficult one
    if(it1 != forward_nodes.end()){
        int id = forward_nodes[row];
        node * other = get_node_from_int(id);
        for(int i = 0; i < _node_no_ground.size();i++){
            int col = _node_no_ground[i]->get_number();
            pair<int,int> temp = make_pair(row,col);
            if(col == id ){
                conductance_matrix[temp] = complex<double> (0.0,0.0);
            }
            else if(col == row){
                conductance_matrix[temp] = conductance_between_nodes(a,a) + conductance_between_nodes(other,other) + (complex<double>) 2.0 * conductance_between_nodes(a,other);
            }
            else{
                conductance_matrix[temp] = conductance_between_nodes(a,_node_no_ground[i]) + conductance_between_nodes(other,_node_no_ground[i]); //for supernode
            }
        }
        pair<int,int> value = make_pair(row,id);
        column_matrix[row] = (complex<double>) super_node_equation[value] * (conductance_between_nodes(other,other) + conductance_between_nodes(other,a));
    }
        // easy one
    else if(it2 != backward_nodes.end()){
        int id = backward_nodes[row];
        for(int i = 0; i <_node_no_ground.size(); i++){
            int col = _node_no_ground[i]->get_number();
            pair<int,int> temp = make_pair(row,col);
            if(col == row){
                conductance_matrix[temp] = complex<double> (-1.0,0.0);
            }
            else if(col == id){
                conductance_matrix[temp] = complex<double> (1.0,0.0);
            }
            else{
                conductance_matrix[temp] = complex<double> (0.0,0.0);
            }
        }
        pair<int,int> value = make_pair(id,row);
        column_matrix[row] = (complex<double>) super_node_equation[value];
    }
}

void circuit::direct_source_matrix(node* a){
    int row  = a->get_number();
    int col;
    for(int i = 0; i < _node_no_ground.size();i++){
        col = _node_no_ground[i]->get_number();
        pair<int,int> temp = make_pair(row,col);
        if(row == col){
            conductance_matrix[temp] = complex<double> (1.0,0.0);
        }
        else{
            conductance_matrix[temp] = complex<double> (0.0,0.0);
        }
    }
    auto it_positive = forward_nodes.find(row);
    if(it_positive != forward_nodes.end()){
        pair<int,int> value = make_pair(row,0);
        column_matrix[row] = (complex<double>) super_node_equation[value];
    }
    else{
        pair<int,int> value = make_pair(0,row);
        column_matrix[row] = (complex<double>) -1.0 * super_node_equation[value];
    }
}


void circuit::build_conductance_matrix(){
    for(int i =0; i < _node_no_ground.size();i++){
        if(!(_node_no_ground[i]->is_connected_voltage())) {
            pure_node_matrix_row(_node_no_ground[i]);
        }
        else if(_node_no_ground[i]->is_super_node()){
            equation_matrix(_node_no_ground[i]);
        }
        else{
            direct_source_matrix(_node_no_ground[i]);
        }
    }
}

node* circuit::get_GND(){
    return GND;
}

map<pair<int,int>,complex<double>> circuit::get_conductance_matrix(){
    return conductance_matrix;
}

node* circuit::get_node_from_int(int a){
    for(int i = 0; i < _node_no_ground.size(); i++){
        if(_node_no_ground[i]->get_number() == a)
            return _node_no_ground[i];
    }
    return new node();
}

map<int,complex<double>> circuit::get_column_matrix(){
    return column_matrix;
}

void circuit::set_time(double t){
    _time = t;
}

double circuit::get_freq(){
    return _frequency;
}

vector<Component*> circuit::get_comp(){
    return _components;
}