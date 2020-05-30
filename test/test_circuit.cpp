#include "components.hpp"
#include "node.hpp"
#include "parser.hpp"
// #include "circuit.hpp"

#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    ifstream input_file("./input/test_input.net");

    double f = 1000;
    double t = 0.001;

    vector<Component *> components;
    vector<Node *> nodes;
    vector<double> instants;
    string line;

    while (getline(input_file, line))
    {
        if (is_component(line))
        {
            cerr << "⚙️  Parsing component: " << line << endl;
            components.push_back(parse_component(line));
        }
        else if (is_directive(line))
        {
            if (is_tran(line))
            {
                cerr << "⏱  Parsing directive: " << line << endl;
                instants = generate_instants(line);
            }
            else if (is_end(line))
            {
                cerr << "🎬 Reach END of file: " << line << endl;
                break;
            }
            else
            {
                cerr << "⚠️  Unsupported syntax: " << line << endl;
            }
        }
    }

    cout << components.size() << " components in total" << endl;
    cout << setw(12) << "get_type()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage(t)" << setw(18) << "check_grounded()" << endl;
    for (auto it = components.begin(); it != components.end(); it++)
    {
        // cout << "conductance:\t" << (*it)->getPin(1) << endl;
        cout << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_conductance(1000) << setw(16) << (*it)->get_node("p") << setw(18) << (*it)->get_node("n") << setw(18) << (*it)->get_current(t, (*it)->get_node("p")) << setw(18) << (*it)->get_voltage(t, (*it)->get_node("p")) << setw(18) << (*it)->is_grounded() << endl;
    }
}