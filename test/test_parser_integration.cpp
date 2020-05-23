#include <iostream>
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
    ifstream input("test_input.net");
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
    for (auto it = circuit.begin(); it != circuit.end(); it++)
    {
        // cout << "conductance:\t" << (*it)->getPin(1) << endl;
        cout << "conductance:\t" << (*it)->getValue(f, t) << endl;
    }
}