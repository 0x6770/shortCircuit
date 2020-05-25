#ifndef TRANSIENT_SIMULATOR_CIRCUIT_HPP
#define TRANSIENT_SIMULATOR_CIRCUIT_HPP

#include <iostream>
#include "Component.hpp"
#include "node.hpp"
#include <vector>
#include <algorithm>
#include <complex>
#include <utility>
#include <map>
#include <cmath>
using namespace std;

class circuit {
private:
    double _frequency;
    double _time;
    vector<Component*> _components; // useful when calculating the conductance due to one single component;
    vector<node*> _node_no_ground; // useful when constructing the vector b in the equation Ax = b;
    node* GND = new node("0");
    map<pair<int,int>,complex<double>> conductance_matrix; // should not vary with time;
public:
    //the constructor for the circuit
    //two functions
    //1. create the new instances fo nodes(without ground node) from strings that has been found from the inputs
    //2. stored these nodes in the circuit
    circuit(double f,vector<Component*> components){
        _frequency = f;
        vector<string> nodes_string;
        string temp;
        for(int i = 0; i < components.size();i++){
            temp = components[i]->get_node(1);
            nodes_string.push_back(temp);
            temp = components[i]->get_node(2);
            nodes_string.push_back(temp);
        }
        //remove duplicates strings in the nodes_string
        sort(nodes_string.begin(),nodes_string.end());
        nodes_string.erase(unique(nodes_string.begin(),nodes_string.end()),nodes_string.end());
        // create instances for node
        for(int i = 0; i< nodes_string.size();i++){
            node* create_node = new node(nodes_string[i]);
            for(int k = 0; k < components.size();k++){
                if(nodes_string[i] != "0"){
                    if (components[k]->get_node(1) == nodes_string[i] or components[k]->get_node(2) == nodes_string[i]) {
                        create_node->add_branches(components[k]);
                    }
                }
            }
            if(nodes_string[i] != "0")
                    _node_no_ground.push_back(create_node);
        }
    }

    //helper function for the build_conductance_matrix, should not used for itself;
    complex<double> single_conductance(Component* a);

    //return the nodes vector without the ground node;
    vector<node*> get_node_no_ground();

    //get the ground node within one circuit;
    node* get_GND();


    // to fill map<pair<node*,node*>,complex<double> conductance_matrix;
    //TODO:: special treatment for the the circuit containing the super node.
    void build_conductance_matrix();

    //helper function for the build_conductance_matrix, should not used for itself;
    complex<double> conductance_between_nodes(node *a,node *b);

    // one of the key advantage of using the int, is that the matrix values will be stored in order
    map<pair<int,int>,complex<double>> get_conductance_matrix();
};


#endif //TRANSIENT_SIMULATOR_CIRCUIT_HPP
