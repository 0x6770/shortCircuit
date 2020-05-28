#include <iostream>
#include <string>
#include <vector>
#include "circuit.hpp"
#include "Component.hpp"
#include "node.hpp"
#include "parser.hpp"
using namespace std;

int main(){
    string input;
    vector<Component*> components_vector;
    vector<double> simulation_parameters;

    while(getline(cin,input)){
        if(is_component(input)){
            components_vector.push_back(parse_component(input));
        }
        else if(is_directive(input)){
            simulation_parameters = generate_instants(input);
        }
        else if(is_end(input)){
            break;
        }
    }
    double f = 0.0; // just assume a value, this should be get from the simulation command.
    //cout << "entered here 1" << endl;
    circuit *total = new circuit(f,components_vector);
    //cout << "entered here 2" << endl;
    total->build_conductance_matrix();
    map<pair<int,int>,complex<double>> conductance = total->get_conductance_matrix();
    cout << "conductance_matrix_with_super_node" << endl;
    for(auto it = conductance.begin(); it!= conductance.end();it++){
        pair<int,int> temp = it->first;
        cout <<"(" <<temp.first << " " << temp.second << ")"<< " ";
        cout << it->second << endl;
    }
    map<int,complex<double>> column = total->get_column_matrix();
    cout << "column matrix for b" << endl;
    for(auto v: column){
        cout << v.first << " " << v.second << endl;
    }
}