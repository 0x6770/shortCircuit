#ifndef TRANSIENT_SIMULATOR_CIRCUIT_HPP
#define TRANSIENT_SIMULATOR_CIRCUIT_HPP

#include "component.hpp"
#include "node.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <utility>
#include <map>
#include <cmath>
#include "../lib/Eigen/Core"
#include "../lib/Eigen/LU"

using namespace Eigen;
using namespace std;

class circuit
{
private:
    // the properties inside the one circuit;
    vector<Component *> _components; // useful when calculating the conductance due to one single component;
    vector<Node *> _node_no_ground;  // useful when constructing the vector b in the equation Ax = b;
    vector<string> _node_names;

    // used to build the super-node equation and give nodes values when we already know the value;
    map<pair<int, int>, double> _super_node_equation; // to store super node equations and the node with know value;
    map<int, int> _forward_nodes;
    map<int, int> _backward_nodes; // only matters for super node
    map<int, double> _known_voltage;

    // used to initialise the matrix A and  b in Ax = b;
    int _dimension;

public:
    // the reason for making this as public is that when writing return functions, it is not convenient to give
    // the return type as dynamically-allocated size;
    Matrix<double, Eigen::Dynamic, Eigen::Dynamic> A; // should not vary with time;
    Matrix<double, Eigen::Dynamic, Eigen::Dynamic> b; // b in Ax = b; should be empty initially;

public:
    //the constructor for the circuit
    //two functions
    //1. create the new instances fo nodes(without ground node) from strings that has been found from the inputs
    //2. stored these nodes in the circuit
    circuit(double f, vector<Component *> components)
    {
        vector<string> node_names;
        string node_p, node_n;
        for (auto component = components.begin(); component != components.end(); component++)
        {
            node_p = (*component)->get_node("p");
            node_names.push_back(node_p);
            node_n = (*component)->get_node("n");
            node_names.push_back(node_n);
            if ((*component)->get_type() == "V")
            {
                if (!((*component)->is_grounded()))
                {
                    pair<string, string> coffe = make_pair(node_p, node_n);
                    _super_node_equation[coffe] = (*component)->get_property();
                }
                else
                {
                    if (node_p == "0")
                    {
                        _known_voltage[node_n] = -1.0 * (*component)->get_property();
                    }
                    else if (node_n == "0")
                    {
                        _known_voltage[node_p] = (*component)->get_property();
                    }
                }
            }
        }
        //remove duplicates strings in the nodes_string
        sort(node_names.begin(), node_names.end());
        node_names.erase(unique(node_names.begin(), node_names.end()), node_names.end());
        node_names.erase(remove(node_names.begin(), node_names.end(), 0), node_names.end()); // remove ground node
        _node_names = node_names;
        // create instances for node
        for (int i = 0; i < node_names.size(); i++)
        {
            Node *create_node = new Node(node_names[i]);
            for (auto component = components.begin(); component != components.size(); component++)
            {
                if ((*component)->get_node("p") == node_names[i] or
                    (*component)->get_node("n") == node_names[i])
                {
                    create_node->add_branches(*component);
                }
            }
            create_node->set_current();
            _node_no_ground.push_back(create_node);
        }
        _dimension = _node_no_ground.size();
        A.resize(_dimension, _dimension);
        b.resize(_dimension, 1);
        simplify();
    }

    //helper function for the build_conductance_matrix, should not used for itself;
    //used to find the conductance due to resistor;
    double single_conductance(Component *a);

    //return the nodes vector without the ground node;
    vector<Node *> get_node_no_ground();

    //get the ground node within one circuit;
    // TODO: to see whether later it would be useful to return the ground node of the circuit;

    // to fill map<pair<node*,node*>,double conductance_matrix;
    // three different methods are applied for different node row
    // 1. pure_node calculation means the node is not connected any voltage node, and may have the current as zero or non-zeor
    // this one we could apply the simple rule as we test before
    // 2. node with known value, this is one is done by using the helper function direct_source node row calculation.
    // 3. equation, the one involved super node, and we have to ensure none of node in this equation is known value
    // so there are two rules for this, depending on the position of that particular node;
    void build_conductance_matrix();

    //helper function for the build_conductance_matrix, should not used for itself;
    double conductance_between_nodes(Node *a, Node *b);

    // this one will give the original conductance matrix row with the row number a->get_number();
    // this is calculated exactly the same as before;
    // required no other containers;
    void pure_node_matrix_row(Node *a);

    // this one is most difficult one;
    // after the simplification process, the super_node_euqation pair map with only involve super node that cannot
    // be derived from the known_voltages;
    // eg V2 - V1 = V;
    // when it is first one V1, we will find it on backward map, means V1 is the second one.
    // the matrix row would be G12 = 1; G11 = -1;
    // the complex situation comes for V2, we will find on the forward map
    // G21 = 0; G22 = G11 + G21(G12); G23 = G23 + G13; G24 = G14 + G24; G25 = G25 + G25;
    void equation_matrix(Node *a);

    // the nodal equation with known source, except that node, all values are zero, in this case;
    // we will use the known_values map to find this;
    void direct_source_matrix(Node *a);

    // only is the helper function for equation case;
    Node *get_node_from_int(int a);

    // the reason put this here, is we have to get all the equations we have to derive the node that may already has the defined value;
    void simplify();

    // since the conductance_matrix won't change, we have to build the b_matrix seperately from conductance_matrix
    void build_current_matrix(double time);
};

#endif //TRANSIENT_SIMULATOR_CIRCUIT_HPP
