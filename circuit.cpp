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