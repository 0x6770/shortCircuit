#include "parser.hpp"
#include "components.hpp"
#include "circuit.hpp"

#include <fstream>

using namespace std;

int main()
{
    ifstream input_file("./input/test_input_6.net");
    vector<Component *> components;
    vector<Node *> nodes;
    vector<double> time_params; // [step, end]
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
                time_params = parse_tran(line);
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

    Circuit *circuit = new Circuit(nodes, components, time_params[0], time_params[1]);
    // cout << *circuit << endl;
    circuit->print();
}
