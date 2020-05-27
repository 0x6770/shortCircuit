#include <iostream>
#include <string>
#include <vector>
#include "circuit.hpp"
#include "Component.hpp"
#include "node.hpp"
#include "parser.hpp"
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\Core>
#include <C:\Users\44736\Desktop\shortCircuit\Eigen\LU>
using namespace Eigen;
using namespace std;

int main(){
    string input;
    vector<Component*> components_vector;
    vector<double> simulation_parameters;
    // read the circuit with out time step parameters yet
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
    double f = 0.0;
    circuit *total = new circuit(f,components_vector);
    total->build_conductance_matrix();
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> A;
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> b;
    A = total->A;
    b = total->b;
    cout << A ;
    cout << endl;
    cout << b;
    cout << endl;
    Matrix<double,Eigen::Dynamic,Eigen::Dynamic> x = A.lu().solve(b);
    cout << x << endl;


}