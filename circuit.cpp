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
       // pair<int,int> temp = make_pair(row,col);
        //conductance_matrix[temp] = conductance_between_nodes(a,_node_no_ground[k]);
    }
    b(row-1,0) = a->get_current();
    //column_matrix[row] = a->get_current();
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
            //pair<int,int> temp = make_pair(row,col);
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
            //pair<int,int> temp = make_pair(row,col);
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
        //pair<int,int> temp = make_pair(row,col);
        if(row == col){
            A(row-1,col-1) = 1.0;
        }
        else{
            A(row-1,col-1) = 0.0;
        }
    }
    auto it_positive = forward_nodes.find(row);
    if(it_positive != forward_nodes.end()){
        pair<int,int> value = make_pair(row,0);
        b(row-1,0) = super_node_equation[value];
    }
    else{
        pair<int,int> value = make_pair(0,row);
        b(row-1,0) = -1.0 * super_node_equation[value];
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


node* circuit::get_node_from_int(int a){
    for(int i = 0; i < _node_no_ground.size(); i++){
        if(_node_no_ground[i]->get_number() == a)
            return _node_no_ground[i];
    }
}
