#include <iostream>
#include <string>
#include <vector>
#include "circuit.hpp"
#include "Component.hpp"
#include "node.hpp"
#include "parser.hpp"
#include "transient.hpp"
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\Core>
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\LU>
using namespace Eigen;
using namespace std;

string print_node_name(int a){
    string result;
    if(a <= 9){
        result = "V(n00" + to_string(a) + ")";
    }
    else if(a >= 10 && a <= 99){
        result = "V(N0" + to_string(a) + ")";
    }
    else{
        result = "V(N" + to_string(a) + ")";
    }
    return result;
}

int main(){
    string input;
    vector<Component*> components_vector;
    transient* simulation_setting = nullptr;
    double time  = 0.0; // starting time is always zero;
    // read the circuit with out time step parameters yet
    while(getline(cin,input)){
        if(is_component(input)){
            components_vector.push_back(parse_component(input));
        }
        else if(is_simulation(input)){
            simulation_setting = generate_simulation(input);
        }
        else if(is_end(input)){
            break;
        }
    }
    double f = 0.0;
    circuit *total = new circuit(f,components_vector);
    total->build_conductance_matrix();
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A;
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> b;
    A = total->A;
    b = total->b;
    //cout << A ;
   // cout << endl;
    //cout << b;
    //cout << endl;
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> x = A.lu().solve(b);
    //cout << x << endl;


    int total_nodes = x.rows();
    //cout << "time" << '\t';
    for(int i = 1; i <= total_nodes; i++){
        //cout << print_node_name(i) << '\t';
    }

}