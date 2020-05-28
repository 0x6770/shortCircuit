#include "Component.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "parser.hpp"
#include "transient.hpp"
using namespace std;

int main(){

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
                                 "V2 N005 0 20",
                                 ".tran 0 10ms 0 100us"};
    vector<double> instants;
    for (auto it = component_strings.begin(); it != component_strings.end(); ++it) {
        if(is_directive(*it)){
            instants = generate_instants(*it);
        }
        compt.push_back(parse_component(*it));
    }
    double f = 0.0;
    circuit *total = new circuit(f,compt);

    transient *simul = new transient();
    simul->set_instant(instants);
    simul->set_simulation(total);
    vector<double> result = simul->get_instant();
    cout << " <<< Checking instants stored in circuit <<<" << endl;
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << endl;
    }

    cout << simul->get_simulation_size() << endl;

    total->build_conductance_matrix();
    map<pair<int,int>,complex<double>> conductance = total->get_conductance_matrix();
    cout << "<<< Constructing conductance matrix <<<" << endl;
    for(auto it = conductance.begin(); it!= conductance.end();it++){
        pair<int,int> temp = it->first;
        cout << temp.first << " " << temp.second << " ";
        cout << it->second << endl;
    }

    cout << "<<< Constructing column matrix <<<" << endl;
    map<int,complex<double>> current = total->get_column_matrix();
    for(auto it = current.begin(); it != current.end(); ++it){
        cout << "node" << it->first << ":" << it->second << endl;
    }
}