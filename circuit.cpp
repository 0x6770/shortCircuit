#include "circuit.hpp"

vector<node*> circuit::get_node_no_ground(){
    return _node_no_ground;
}

// TODO: might needed to consider more about AC power source
complex<double> circuit::single_conductance(Component* a){
    if(a->get_identifier()[0] == 'R'){
        return complex<double> (1.0/a->get_value(),0.0);
    }
    else if(a->get_identifier()[0] == 'C'){
        return complex<double> (0.0,2*M_PI*_frequency*a->get_value());
    }
    else if(a->get_identifier()[0] == 'L'){
        return complex<double> (0.0,-1.0*(1.0/(a->get_value()*2*M_PI*_frequency)));
    }
    else{
        return complex<double>(0.0,0.0);
    }
}

//without supper node
complex<double> circuit::conductance_between_nodes(node *a,node *b){
    complex<double> output = (0.0,0.0);
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

void circuit::build_conductance_matrix(){
    for(int i = 0 ; i < _node_no_ground.size();i++){
        for(int k = 0; k < _node_no_ground.size();k++){
            pair<int,int> temp = make_pair(_node_no_ground[i]->get_number(),_node_no_ground[k]->get_number());
            conductance_matrix[temp] = conductance_between_nodes(_node_no_ground[i],_node_no_ground[k]);
        }
    }
}

node* circuit::get_GND(){
    return GND;
}

map<pair<int,int>,complex<double>> circuit::get_conductance_matrix(){
    return conductance_matrix;
}