#include "parser.hpp"
#include "linear_components.hpp"
#include "nonlinear_components.hpp"
#include "circuit.hpp"

#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    spdlog::set_level(spdlog::level::warn);
    if (argc < 2)
    {
        spdlog::error("🚧  ERROR: no input file provided as command line argument");
        exit(1);
    }
    ifstream input_file(argv[1]);

    // Set global log level, available: debug, info, warn, error, critical

    vector<Component *> components;
    vector<Node *> nodes;
    vector<double> time_params;
    string line;

    while (getline(input_file, line))
    {
        if (is_component(line))
        {
            spdlog::debug("⚙️  Parsing component: {}", line);
            components.push_back(parse_component(line, nodes));
        }
        else if (is_directive(line))
        {
            if (is_tran(line))
            {
                spdlog::debug("⏱  Parsing directive: {}", line);
                time_params = parse_tran(line);
            }
            else if (is_end(line))
            {
                spdlog::debug("🎬 Reach END of file: {}", line);
                break;
            }
            else
            {
                // spdlog::warn("⚠️  Unsupported syntax: {}", line);
                cerr << "⚠️  Unsupported syntax: " << line << endl;
            }
        }
    }

    Circuit *circuit = new Circuit(nodes, components, time_params[0], time_params[1]);
    // cerr << *circuit << endl;
    circuit->loop();
}