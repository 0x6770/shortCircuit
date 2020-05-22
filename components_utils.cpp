#include "components_utils.hpp"
#include "components.hpp"
#include <map>
#include <utility>

vector<string> remove_duplicates(vector<string> &nums)
{
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] == nums[i + 1])
        {
            nums.erase(nums.begin() + i);
            return remove_duplicates(nums);
        }
    }
    return nums;
}

vector<string> find_nodes(vector<Component *> circuit)
{
    vector<string> nodes;
    for (auto it = circuit.begin(); it != circuit.end(); it++)
    {
        nodes.push_back((*it)->getPin(1));
        nodes.push_back((*it)->getPin(2));
    }
    sort(nodes.begin(), nodes.end());

    return remove_duplicates(nodes);
}

int demension(vector<string> nodes){
    return nodes.size()-1;
}

bool is_powersource(Component* component){
    if(component->get_type() == "power_source"){
        return true;
    }
    return false;
}

bool is_single_component(string node1, string node2,map<Component*,pair<string,string>> component_nodes){
    bool first,second;
    pair<string,string> nodes_forward  = make_pair(node1,node2);
    pair<string,string> nodes_reverse  = make_pair(node2,node1);
    for(auto it = component_nodes.begin(); it != component_nodes.end() ;it++){
        first = (it->second == nodes_forward);
        second = (it->second == nodes_reverse);
        if(first || second){
            return true;
        }
    }
    return false;
}

map<Component*,pair<string,string>> components_nodes(vector<Component *> circuit)
{
    map<Component*,pair<string,string>> result;
    pair<string,string> nodes;
    for(int i = 0; i<circuit.size();i++ )
    {
        nodes.first = circuit[i]->getPin(1);
        nodes.second = circuit[i]->getPin(2);
        result[circuit[i]] = nodes;
    }
    return result;
}

Component* get_component(string node1,string node2,map<Component*,pair<string,string>> component_nodes){
    pair<string,string> nodes_forward  = make_pair(node1,node2);
    pair<string,string> nodes_reverse  = make_pair(node2,node1);
    for(auto it = component_nodes.begin(); it != component_nodes.end() ;it++){
        if(it->second == nodes_forward || it->second == nodes_reverse){
            return it->first;
        }
    }
    return nullptr;
}

complex<double> find_conductance(string node1, string node2, vector<Component *> circuit,double f, double t,map<Component*,pair<string,string>> component_nodes){
    vector<Component*> temp;
    if(node1 == node2){
        //cout << "enter here1" << endl;
        for(int i = 0;i < circuit.size();i++){
            //cout << is_powersource(circuit[i]) << endl;
            if(!is_powersource(circuit[i])){
                if(circuit[i]->getPin(1) == node1 or circuit[i]->getPin(2) == node2 ){
                  temp.push_back(circuit[i]);
                }
            }
        }
        complex<double> result = complex<double>(0.0,0.0);
        for(int i = 0;i<temp.size();i++){
            //cout << "enter here2" << endl;
            result = result + temp[i]->getValue(f,t);
        }
        return result;
    }
    if(is_single_component(node1,node2,component_nodes)){
        return complex<double> (-1.0 * get_component(node1,node2,component_nodes)->getValue(f,t));
    }
    else{
        return complex<double> (0.0,0.0);
    }
}

int main(){
    Component *R1 = new Resistor("1", "3", 2);
    Component *R2 = new Resistor("2", "3", 2);
    Component *R3 = new Resistor("1", "2", 5);
    Component *R4 = new Resistor("2", "0", 1.25);
    Component *R5 = new Resistor("2", "4", 10);
    Component *R6 = new Resistor("4", "0", 5);
    Component *R7 = new Resistor("4","5",2.5);
    Component *V1 = new DC_voltage("1","0",13);
    Component *V2 = new DC_voltage("3","5",8);
    Component *V3 = new DC_voltage("5","0",20);
    Component *V4 = new DC_voltage("2","4",10);
    vector<Component *> circuit = {V1,R1,R2,R3,V2};
    map<Component*,pair<string,string>> test = components_nodes(circuit);
    //cout << test.size() << endl;
    double time = 2.0;
    double f = V1->getFrequency();
    //for(auto v:test) cout << v.first->getPin(1) << " " << v.first->getPin(2) << " " << endl;
    cout << find_conductance("1","1",circuit,f,time,test) << endl;
}