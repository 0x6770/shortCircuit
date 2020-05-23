#ifndef SHORTCIRCUIT_CIRCUIT_HPP
#define SHORTCIRCUIT_CIRCUIT_HPP

#include <iostream>
#include <string>
#include <map>
#include <complex>
#include "components.hpp"
#include "components_utils.hpp"
class Circuit{
private:
    vector<Component*> _circuit;
    map<pair<string,string>,Component*> forward_nodes_component;
    map<pair<string,string>,Component*> reverse_nodes_component;
    vector<string> nodes;
    int _dimension;
    double _frequency;
public:
    Circuit(const vector<Component*> & components,const double &frequency){
        _circuit = components;
        nodes = find_nodes(components);
        pair<string,string> temp_forward,temp_reverse;
        for(int i = 0; i < components.size();i++){
            temp_forward = make_pair(components[i]->getPin(1),components[i]->getPin(2));
            temp_reverse = make_pair(components[i]->getPin(2),components[i]->getPin(1));
            forward_nodes_component[temp_forward] = components[i];
            reverse_nodes_component[temp_reverse] = components[i];
        }
        _frequency = frequency;
    }
    bool is_single_component(string node1, string node2){
        pair<string,string> nodes  = make_pair(node1,node2);
        auto it1 = forward_nodes_component.find(nodes);
        auto it2 = reverse_nodes_component.find(nodes);
        if(it1 != forward_nodes_component.end() or it2 != reverse_nodes_component.end()){
            return true;
        }
        return false;
    }
    int get_dimension(){
        return nodes.size()-1;
    }

    Component* get_component(string node1,string node2){
        pair<string,string> nodes  = make_pair(node1,node2);
        auto it1 = forward_nodes_component.find(nodes);
        auto it2 = reverse_nodes_component.find(nodes);
        if(it1 != forward_nodes_component.end()){
            return it1->second;
        }
        if(it2 != reverse_nodes_component.end()){
            return it2->second;

        }
        return nullptr;
    }

    complex<double> get_conductance(string node1,string node2,double t){
        vector<Component*> temp;
        if(node1 == node2){
            for(int i = 0;i < _circuit.size();i++){
                if(!is_powersource(_circuit[i])){
                    if(_circuit[i]->getPin(1) == node1 or _circuit[i]->getPin(2) == node2 ){
                        temp.push_back(_circuit[i]);
                    }
                }
            }
            complex<double> result = complex<double>(0.0,0.0);
            for(int i = 0;i<temp.size();i++){
                result = result + temp[i]->getValue(_frequency,t);
            }
            return result;
        }

        if(is_single_component(node1,node2)){
            return complex<double> (-1.0 * get_component(node1,node2)->getValue(_frequency,t));
        }
        else{
            return complex<double> (0.0,0.0);
        }

    }

    vector<Component*> get_components(){
        return _circuit;
    }
    map<pair<string,string>,Component*> get_forward_nodes_component(){
        return forward_nodes_component;
    }
    map<pair<string,string>,Component*> get_reverse_nodes_component(){
        return reverse_nodes_component;
    }
    vector<string> get_nodes(){
        return nodes;
    }

};


#endif //SHORTCIRCUIT_CIRCUIT_HPP