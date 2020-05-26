#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>

#include "components.hpp"
#include "components_utils.hpp"
#include "parser.hpp"

using namespace std;

int main()
{
    ifstream input("./test/test_input.net");
    string line;
    vector<Component *> circuit;
    vector<double> instants;

    while (getline(input, line))
    {
        if (is_component(line))
        {
            circuit.push_back(parse_component(line));
        }
        else if (is_directive(line))
        {
            instants = generate_instants(line);
        }
        else if (is_end(line))
        {
            break;
        }
    }
    cout << "instants" << endl;
    cout << "From: " << instants[0] << "\t\tto: " << instants[instants.size() - 1] << "\twith step: " << instants[1] << "\tand size: " << instants.size() << endl;
    cout << "circuits" << endl;
    cout << circuit.size() << " components in total" << endl;
    double f = 1000;
    double t = 0.001;
    cout << setw(12) << "get_type()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage(t)" << setw(18) << "check_grounded()" << endl;
    for (auto it = circuit.begin(); it != circuit.end(); it++)
    {
        // cout << "conductance:\t" << (*it)->getPin(1) << endl;
        cout << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_conductance(1000) << setw(16) << (*it)->get_node("p") << setw(18) << (*it)->get_node("n") << setw(18) << (*it)->get_current(t, (*it)->get_node("p")) << setw(18) << (*it)->get_voltage(t, (*it)->get_node("p")) << setw(18) << (*it)->check_grounded() << endl;
    }
}