#include "component.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "components_parser.hpp"
using namespace std;

int main(){
    //Node *t0, *t1, *t2;
    //Node *t0 = new Node();
    //Node *t1 = new Node();
    //Node *t2 = new Node();
    //Component *a = new Component("voltage_source",5.00);
    //Component *b = new Component("resistor",100.00);
    //Component *c = new Component("resistor",50.00);
    //vector<Component*> temp{a,b,c};
    /*vector<Component*> temp1{a,c};
    vector<Component*> temp2{a,b};
    vector<Component*> temp3{b,c};
    t0->set_node(temp1,true);
    t1->set_node(temp2,false);
    t2->set_node(temp3,false);*/

    string component_1 = "R1 N001 N002 100";
    string component_2 = "R2 N001 N002 300";
    vector<Component *> compt;
    vector<string>
            component_strings = {"R1 N001 N003 1k",
                                 "C1 N001 0 1μ ",
                                 "L1 N002 N001 1m",
                                 "R2 N002 N001 1Meg "};
    for (auto it = component_strings.begin(); it != component_strings.end(); it++)
    {
        compt.push_back(parse_component(*it));
    }

    cout << compt.size() << endl;

    double f = 1000, t = 0.001;
    Circuit *total = new Circuit(f,t,compt);
    total->store_conductance();
    total->store_node();
    vector<complex<double>> output = total->get_conductance();
    for(int i = 0; i < output.size(); i++){
        cout << output[i] << endl;
    }

    vector<Node*> num = total->get_nod();
    cout << num.size() << endl;
    for(int i = 0; i < num.size(); i++) {
        cout << num[i]->get_name() << endl;
    }
    //cout << num[1]->get_num_of_components() << endl;


    cout << total->get_node_conductance(num[0],num[1]);
    //cout << get_node_conductance();

    //Circuit *total = new Circuit(5.00,5.00,temp);
    //total->store_conductance();

    //cout << b->get_type() << endl;
    //cout << b->get_conductance() << endl;
    //cout << t1->is_ground() << endl;
    //cout << total->get_node_conductance(t2,t0) << endl;
}