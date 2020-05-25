#include "Component.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "parser.hpp"
using namespace std;

int main() {

    vector < Component * > compt;
    vector <string>
            component_strings = {"V1 N002 N004 10",
                                 "R1 N001 N003 2",
                                 "R2 N001 N002 5",
                                 "R3 N002 N003 2",
                                 "R4 N002 0 1.25",
                                 "R5 N004 0 5",
                                 "R6 N004 N005 2.5",
                                 "R7 N002 N004 10",
                                 "I1 N001 0 13",
                                 "I2 N003 N005 8",
                                 "V2 N005 0 20"};
    for (auto it = component_strings.begin(); it != component_strings.end(); it++) {
        compt.push_back(parse_component(*it));
    }
    double f = 0.0;
    circuit *total = new circuit(f,compt);
    total->build_conductance_matrix();
    map<pair<int,int>,complex<double>> conductance = total->get_conductance_matrix();
    for(auto it = conductance.begin(); it!= conductance.end();it++){
        pair<int,int> temp = it->first;
        cout << temp.first << " " << temp.second << " ";
        cout << it->second << endl;
    }
}