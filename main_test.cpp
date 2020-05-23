#include "component.hpp"
#include "node.hpp"
#include "circuit.hpp"
using namespace std;

int main(){
    //Node *t0, *t1, *t2;
    Node *t0 = new Node();
    Node *t1 = new Node();
    Node *t2 = new Node();

    Component *a = new Component("voltage_source",5.00,t0,t1);
    Component *b = new Component("resistor",100.00,t1,t2);
    Component *c = new Component("resistor",50.00,t2,t0);
    vector<Component*> temp{a,b,c};
    vector<Component*> temp1{a,c};
    vector<Component*> temp2{a,b};
    vector<Component*> temp3{b,c};
    t0->set_node(0,temp1,true);
    t1->set_node(5,temp2,false);
    t2->set_node(1.666667,temp3,false);

    Circuit *total = new Circuit(5.00,5.00,temp);
    total->store_conductance();

    cout << b->get_type() << endl;
    cout << b->get_conductance() << endl;
    cout << t1->is_ground() << endl;
    cout << total->get_node_conductance(t2,t0) << endl;

}