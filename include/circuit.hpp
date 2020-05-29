#ifndef circuit_hpp
#define circuit_hpp

#include "parser.hpp"
#include "component.hpp"
#include "components_utils.hpp"

using namespace std;

class Circuit
{
private:
    vector<Component *> _components;
    vector<Node *> _nodes;
    vector<double> _instants;
    vector<Component *> _used_voltages;
    double _f = 1000;
    double _t = 1;

public:
    Circuit(vector<Node *> nodes, vector<Component *> components, vector<double> instants)
    {
        _components = components;
        _nodes = nodes;
        _instants = instants;
    }
    friend ostream &operator<<(ostream &os, Circuit &circuit);
};

ostream &operator<<(ostream &os, Circuit &circuit)
{
    os << endl;
    os << endl;
    os << "==============================" << endl;
    os << "✅ " << circuit._instants.size() << " instants in total" << endl;
    os << "==============================" << endl;
    os << "From: " << circuit._instants[0] << " to: " << circuit._instants[circuit._instants.size() - 1] << " with step: " << circuit._instants[1] << endl;

    os << endl;
    os << endl;
    os << "==============================" << endl;
    os << "✅ " << circuit._components.size() << " components in total" << endl;
    os << "==============================" << endl;
    os << setw(12) << "get_type()" << setw(20) << "get_property()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage(t)" << setw(18) << "check_grounded()" << endl;
    for (auto it = circuit._components.begin(); it != circuit._components.end(); it++)
    {
        os << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_property() << setw(20) << (*it)->get_conductance(1000) << setw(16) << (*it)->get_node("p")->get_name() << setw(18) << (*it)->get_node("n")->get_name() << setw(18) << (*it)->get_current(circuit._t, (*it)->get_node("p")) << setw(18) << (*it)->get_voltage(circuit._t, (*it)->get_node("p")) << setw(18) << (*it)->check_grounded() << endl;
    }

    os << endl;
    os << endl;
    os << "==============================" << endl;
    os << "✅ " << circuit._nodes.size() << " nodes in total execpt for ground" << endl;
    os << "==============================" << endl;
    os << setw(5);
    for (auto it = circuit._nodes.begin(); it != circuit._nodes.end(); it++)
    {
        if ((*it)->get_name() != "0")
        {
            os << setw(22) << (*it)->get_name();
        }
    }
    os << setw(20) << "voltage_state" << setw(10) << "b" << endl;
    for (auto it = circuit._nodes.begin(); it != circuit._nodes.end(); it++)
    {
        if ((*it)->get_name() != "0")
        {
            os << setw(5) << (*it)->get_name();
            for (auto jt = circuit._nodes.begin(); jt != circuit._nodes.end(); jt++)
            {
                if ((*jt)->get_name() != "0")
                {
                    os << setw(22) << (*it)->get_conductance(circuit._f, circuit._used_voltages, (*jt));
                }
            }
            os << setw(10) << (*it)->get_voltage_state() << setw(20) << (*it)->get_value(circuit._t) << endl;
        }
    }
    return os;
}

#endif
