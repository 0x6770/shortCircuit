#include "component.hpp"
#include "node.hpp"
#include "circuit.hpp"

double Circuit::get_freq(){
    return f;
}

double Circuit::get_time(){
    return t;
}

vector<Component*> Circuit::get_comp(){
    return comp;
}

vector<complex<double>> Circuit::get_conductance(){
    vector<Component*> temp = get_comp();
    vector<complex<double>> output;
    for(int i = 0; i < temp.size(); i++){
        if(temp[i]->get_type() == "resistor"){
            output.push_back(complex<double>(1.0/temp[i]->get_value(),0.0));
        }else if(temp[i]->get_type() == "capacitor"){
            output.push_back(complex<double>(0.0,2*M_PI*get_freq()*temp[i]->get_value()));
        }else if(temp[i]->get_type() == "inductor"){
            output.push_back(complex<double>(0.0,1.0/(2*M_PI*get_freq()*temp[i]->get_value())));
        }else if(temp[i]->is_power_source()){
            output.push_back(complex<double>(0.0,0.0));
        }
    }
    return output;
}

void Circuit::store_conductance(){
    vector<complex<double>> temp = get_conductance();
    for(int i = 0; i < temp.size(); i++){
        comp[i]->conductance = temp[i];
    }
}

complex<double> Circuit::get_node_conductance(Node *a, Node *b){
    complex<double> output = complex<double>(0.0,0.0);
    vector<Component*> x = a->get_components();
    vector<Component*> y = b->get_components();
    for (std::vector<Component*>::iterator i = x.begin(); i != x.end(); ++i)
    { if (std::find(y.begin(), y.end(), *i) != y.end()){
        output += (*i)->get_conductance();
    }}
    return output;
}

bool equal_node(Node *a, Node *b){
    if(a->get_name() == b->get_name()){
        return true;
    }
    return false;
}

vector<Node*> Circuit::get_nod(){
    return nod;
}

bool Circuit::check_node_inside_nod(Node *temp){
    bool output = false;
    for(int i = 0; i < nod.size(); i++){
        if(equal_node(temp,nod[i])){
            output = true;
            break;
        }
    }
    return output;
}


void Circuit::store_node(){
    nod.push_back(comp[0]->n1);
    nod.push_back(comp[0]->n2);
    for(int i = 1; i < comp.size(); i++){
        if(!check_node_inside_nod(comp[i]->n1)){
            nod.push_back(comp[i]->n1);
        }
        if(!check_node_inside_nod(comp[i]->n2)){
            nod.push_back(comp[i]->n2);
        }
    }

    for(int i = 0; i < comp.size(); i++){
        for(int j = 0; j < nod.size(); j++){
            if(equal_node(comp[i]->n1,nod[j]) or equal_node(comp[i]->n2,nod[j])) {
                nod[j]->store_comp(comp[i]);
            }

        }
    }
}

Node* Circuit::get_ground(){
    for(int i = 0;i<nod.size();i++){
        if(nod[i]->is_ground == true)
            return nod[i];
    }
    return nullptr;
}

void Circuit::set_ground(string ground){
    for(int i = 0;i < nod.size();i++){
        if(nod[i]->get_name() == ground){
            nod[i].set_is_ground = true;
        }
    }
}