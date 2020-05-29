#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>

#include "components_utils.hpp"
#include "parser.hpp"
#include "components.hpp"
#include "circuit.hpp"

using namespace std;

int main()
{
    ifstream input_file("./input/test_input_4.net");
    vector<Component *> components;
    vector<Node *> nodes;
    vector<double> instants;
    string line;

    while (getline(input_file, line))
    {
        if (is_component(line))
        {
            cerr << "⚙️  Parsing component: " << line << endl;
            components.push_back(parse_component(line, nodes));
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

    Circuit *circuit = new Circuit(nodes, components, instants);
    cout << *circuit << endl;
}