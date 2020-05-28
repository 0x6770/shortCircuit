#include "circuit.hpp"
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\Core>
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\LU>


vector<node*> circuit::get_node_no_ground(){
    return _node_no_ground;
}

// TODO: might needed to consider more about AC power source
double circuit::single_conductance(Component* a){
    if(a->get_identifier()[0] == 'R'){
        return (double)1.0/a->get_value();
    }
    else if(a->get_identifier()[0] == 'C'){
        return (double) 0.0;
    }
    else if(a->get_identifier()[0] == 'L'){
        return (double) 0.0;
    }
    else{
        return (double) 0.0;
    }
}

//without supper node
double circuit::conductance_between_nodes(node *a,node *b){
    double output = 0.0;
    vector<Component*> x  = a->get_branches();
    vector<Component*> y  = b->get_branches();
    for(auto it = x.begin(); it != x.end(); ++it){
        if(find(y.begin(),y.end(),*it) != y.end()){
            output += single_conductance(*it);
        }
    }
    if(!(a == b)){
        output = -1.0 * output;
    }
    return output;
}

void circuit::pure_node_matrix_row(node* a) {
    int row =  a->get_number();
    for(int k = 0; k < _node_no_ground.size();k++){
        int col =  _node_no_ground[k]->get_number();
        A(row-1,col-1) = conductance_between_nodes(a,_node_no_ground[k]);
    }
    b(row-1,0) = a->get_current();
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
            if(col == id ){
                A(row-1,col-1) = 0.0;
            }
            else if(col == row){
                A(row-1,col-1) = conductance_between_nodes(a,a) + conductance_between_nodes(other,other) + (double) 2.0 * conductance_between_nodes(a,other);
            }
            else{
                A(row-1,col-1) = conductance_between_nodes(a,_node_no_ground[i]) + conductance_between_nodes(other,_node_no_ground[i]);
            }
        }
        pair<int,int> value = make_pair(row,id);
        b(row-1,0) = (double) super_node_equation[value] * (conductance_between_nodes(other,other) + conductance_between_nodes(other,a));
    }
    // easy one
    else if(it2 != backward_nodes.end()){
        int id = backward_nodes[row];
        for(int i = 0; i <_node_no_ground.size(); i++){
            int col = _node_no_ground[i]->get_number();
            if(col == row){
                A(row-1,col-1) = -1.0;
            }
            else if(col == id){
                A(row-1,col-1) = 1.0;
            }
            else{
                A(row-1,col-1) = 0.0;
            }
        }
        pair<int,int> value = make_pair(id,row);
        b(row-1,0) = super_node_equation[value];
    }
}

void circuit::direct_source_matrix(node* a){
    int row  = a->get_number();
    int col;
    for(int i = 0; i < _node_no_ground.size();i++){
        col = _node_no_ground[i]->get_number();
        if(row == col){
            A(row-1,col-1) = 1.0;
        }
        else{
            A(row-1,col-1) = 0.0;
        }
    }
    auto it_positive = known_voltage.find(row);
    if(it_positive != known_voltage.end()){
        double id_know = known_voltage[row];
        b(row-1,0) = id_know;
    }
}


void circuit::build_conductance_matrix(){
    for(int i =0; i < _node_no_ground.size();i++){
        // the simplest one
        if(!(_node_no_ground[i]->is_connected_voltage())) {
            pure_node_matrix_row(_node_no_ground[i]);
        }
        // nodes involving supernodes and know value
        else{
            int id = _node_no_ground[i]->get_number();
            auto it = known_voltage.find(id);
            if(it != known_voltage.end()){
                direct_source_matrix(_node_no_ground[i]);
            }
            else{
                equation_matrix(_node_no_ground[i]);
            }
        }
    }
}


void build_current_matrix();


node* circuit::get_node_from_int(int a){
    for(int i = 0; i < _node_no_ground.size(); i++){
        if(_node_no_ground[i]->get_number() == a)
            return _node_no_ground[i];
    }
}


void circuit::simplify(){
    map<pair<int,int>,double> temp_super = super_node_equation;
    for(auto it = temp_super.begin(); it != temp_super.end();it++){
        pair<int,int> temp  = it->first;
        auto find_1 = known_voltage.find(temp.first);
        auto find_2 = known_voltage.find(temp.second);
        if(find_1 != known_voltage.end()){
            int known = temp.second;
            known_voltage[known] = known_voltage[temp.first] - it->second;
            super_node_equation.erase(temp);
        }
        if(find_2 != known_voltage.end()){
            int known = temp.first;
            known_voltage[known] = known_voltage[temp.second] + it->second;
            super_node_equation.erase(temp);
        }
    }
    // set out the forward and backward euqation;
    if(super_node_equation.size() != 0){
        for(auto v: super_node_equation){
            pair<int,int> set_map = v.first;
            forward_nodes[set_map.first] = set_map.second;
            backward_nodes[set_map.second] = set_map.first;
        }
    }
}