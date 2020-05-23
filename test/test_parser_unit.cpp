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

    cout << "==============================" << endl;
    cout << "test for boolean detectors" << endl;
    cout << "==============================" << endl;

    while (getline(input, line))
    {
        string comment = is_comment(line) ? "  comment" : "";
        string directive = is_directive(line) ? "directive" : "";
        string end = is_end(line) ? "      end" : "";
        string component = is_component(line) ? "component" : "";
        cout << comment << directive << end << component << "\t" << line << endl;
    }

    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "test for number parser" << endl;
    cout << "==============================" << endl;

    // 1p, 1n, 1μ, 1m, 1, 1k, 1Meg
    vector<string> numbers = {
        "1.1p",
        "1.1n",
        "1.1μ",
        "1.1m",
        "1.1",
        "1.1k",
        "1.1Meg",
        "0",
        "010",
        "000",
        "0k",
        "01k",

        // // error cases
        // "",
        // "k",
        // "1a1",
    };
    for (auto it = numbers.begin(); it != numbers.end(); it++)
    {
        cout << *it << "\t" << parse_number(*it) << endl;
    }

    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "test for instants generator" << endl;
    cout << "==============================" << endl;

    vector<double> instants = generate_instants(".tran 0 10ms 0 1us ");
    cout << "From: " << instants[0] << "\t\tto: " << instants[instants.size() - 1] << "\twith step: " << instants[1] << "\tand size: " << instants.size() << endl;
    // for (auto it = instant.begin(); it != instant.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    cout << endl;
    cout << endl;
    cout << "==============================" << endl;
    cout << "test for component parser" << endl;
    cout << "==============================" << endl;

    vector<Component *> components;
    vector<string>
        component_strings = {"R1 N001 N003 1k",
                             "C1 N001 0 1μ ",
                             "L1 N002 N001 1m",
                             "R2 N002 N001 1Meg "};
    for (auto it = component_strings.begin(); it != component_strings.end(); it++)
    {
        components.push_back(parse_component(*it));
    }
    cout << components.size() << " components in total" << endl;
    double f = 1000;
    double t = 0.001;
    for (auto it = components.begin(); it != components.end(); it++)
    {
        // cout << "conductance:\t" << (*it)->getPin(1) << endl;
        cout << "conductance:\t" << (*it)->getValue(f, t) << endl;
    }
};