#include "component.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "components_parser.hpp"
using namespace std;

int main(){

    vector<Component *> compt;
    vector<string>
            component_strings = {"V1 2 4 10",
                                 "R1 1 3 2",
                                 "R2 1 2 5",
                                 "R3 2 3 2",
                                 "R4 2 0 1.25",
                                 "R5 4 0 5",
                                 "R6 4 5 2.5",
                                 "R7 2 4 10",
                                 "I1 1 0 13",
                                 "I2 3 5 8",
                                 "V2 5 0 20"};
    for (auto it = component_strings.begin(); it != component_strings.end(); it++)
    {
        compt.push_back(parse_component(*it));
    }

   // cout << compt.size() << endl;
    double f = 1000, t = 0.001;
    Circuit *total = new Circuit(f,t,compt);
    total->store_conductance();
    total->store_node();
    vector<complex<double>> output = total->get_conductance();
    for(int i = 0; i < output.size(); i++){
       // cout << output[i] << endl;
    }

    total->eliminate_ground_node("0");
    vector<Node*> num = total->get_nod();
    cout << num.size() << endl;
    for(int i = 0; i < num.size(); i++) {
        //cout << num[i]->get_name() <<" " << (bool)num[i]->is_ground()<<  endl;
    }
    for(int i = 0; i < num.size();i++){
        for(int k = 0; k < num.size();k++){
            cout << "the conductance between " << num[i]->get_name() <<" " << num[k]->get_name() <<" : "<<total->get_node_conductance(num[i],num[k]) << endl;
        }
    }

}