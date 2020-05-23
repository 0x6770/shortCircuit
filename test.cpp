#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
#include "circuit.hpp"
using namespace std;

int main(){
    double f = 0;
    Component *R1 = new Resistor("1", "3", 2);
    Component *R2 = new Resistor("2", "3", 2);
    Component *R3 = new Resistor("1", "2", 5);
    Component *R4 = new Resistor("0", "2", 1.25);
    Component *R5 = new Resistor("4", "2", 10);
    Component *R6 = new Resistor("4", "0", 5);
    Component *R7 = new Resistor("4","5",2.5);
    Component *V1 = new DC_voltage("2","4",10);
    Component *I1 = new current_source("1","0",13);
    Component *I2 = new current_source("3","5",8);
    Component *I3 = new current_source("5","0",20);
    vector<Component *> circuit = {R1,R2,R3,R4,R5,R6,R7,V1,I1,I2,I3};
    Circuit * test_circuit = new Circuit(circuit,f);
    double t = 2;
    cout << test_circuit->get_conductance("5","5",t) << endl;

}