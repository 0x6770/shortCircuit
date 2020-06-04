#include "./include/parser.hpp"
#include "./include/linear_components.hpp"
#include "./include/nonlinear_components.hpp"
#include "./include/circuit.hpp"

#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << endl;
        cerr << "🚧  ERROR: no input file provided as command line argument" << endl;
        cerr << endl;
        exit(1);
    }
    ifstream input_file(argv[1]);
    vector<Component *> components;
    vector<Node *> nodes;
    vector<double> time_params;
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
    // cerr << *circuit << endl;
    circuit->loop();
}