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
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\Core>
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\LU>
using namespace Eigen;
using namespace std;

class circuit {
private:
    double _frequency;
    double _time;
    vector<Component*> _components; // useful when calculating the conductance due to one single component;
    vector<node*> _node_no_ground; // useful when constructing the vector b in the equation Ax = b;
    node* GND = new node(0);

    map<pair<int,int>,double> super_node_equation; // to store super node equations and the node with know value;
    map<int,int> forward_nodes;
    map<int,int> backward_nodes; // only matters for super node

    int dimension;

public:
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic>  A;// should not vary with time;
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic>  b;  // b in Ax = b; should be empty initially;
public:
    //the constructor for the circuit
    //two functions
    //1. create the new instances fo nodes(without ground node) from strings that has been found from the inputs
    //2. stored these nodes in the circuit
    circuit(double f,vector<Component*> components){
        _frequency = f;
        vector<int> nodes_int;
        int temp1,temp2;
        for(int i = 0; i < components.size();i++){
            temp1 = components[i]->get_node(1);
            nodes_int.push_back(temp1);
            temp2 = components[i]->get_node(2);
            nodes_int.push_back(temp2);
            if(components[i]->is_voltage()){
                pair<int,int> coffe = make_pair(temp1,temp2);
                super_node_equation[coffe] = components[i]->get_value();
                forward_nodes[temp1] = temp2;
                backward_nodes[temp2] = temp1;
            }
        }
        //remove duplicates strings in the nodes_string
        sort(nodes_int.begin(),nodes_int.end());
        nodes_int.erase(unique(nodes_int.begin(),nodes_int.end()),nodes_int.end());
        nodes_int.erase(remove(nodes_int.begin(),nodes_int.end(),0),nodes_int.end()); // remove ground node
        // create instances for node
        // cout << nodes_string.size() << endl;
        for(int i = 0; i< nodes_int.size();i++){
                node *create_node = new node(nodes_int[i]);
                for (int k = 0; k < components.size(); k++) {
                    if (components[k]->get_node(1) == nodes_int[i] or
                        components[k]->get_node(2) == nodes_int[i]) {
                        create_node->add_branches(components[k]);
                    }
                }
                create_node->set_current();
                _node_no_ground.push_back(create_node);
        }
        dimension = _node_no_ground.size();
        A.resize(dimension,dimension);
        b.resize(dimension,1);
    }

    //helper function for the build_conductance_matrix, should not used for itself;
    double single_conductance(Component* a);

    //return the nodes vector without the ground node;
    vector<node*> get_node_no_ground();

    //get the ground node within one circuit;
    node* get_GND();


    // to fill map<pair<node*,node*>,double conductance_matrix;
    //TODO:: special treatment for the the circuit containing the super node.
    void build_conductance_matrix();

    //helper function for the build_conductance_matrix, should not used for itself;
    double conductance_between_nodes(node *a,node *b);

    // one of the key advantage of using the int, is that the matrix values will be stored in order
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> get_A_matrix();

    void pure_node_matrix_row(node* a);

    void equation_matrix(node* a);

    void direct_source_matrix(node* a);

    node* get_node_from_int(int a);

    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> get_b_matrix();


};


#endif //TRANSIENT_SIMULATOR_CIRCUIT_HPP
