#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <string>

#include "components.hpp"
#include "components_utils.hpp"

using namespace std;

int main()
{
    Component *V = new Voltage("9", "2", 100);
    Component *R = new Resistor("1", "2", 100);
    Component *C = new Capacitor("23", "2", 100);
    Component *I = new Inductor("3", "100", 100);
    vector<Component *> circuit = {V, R, C, I};
    vector<string> nodes = find_nodes(circuit);
    cout << V->getValue(1000, 1) << endl;
    cout << R->getValue(1000, 1) << endl;
    cout << C->getValue(1000, 1) << endl;
    cout << I->getValue(1000, 1) << endl;
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        cout << *it << endl;
    }
};