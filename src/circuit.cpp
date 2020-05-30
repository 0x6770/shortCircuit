#include "circuit.hpp"

Circuit::Circuit(vector<Node *> nodes, vector<Component *> components, vector<double> instants)
{
    _components = components;
    _nodes = nodes;
    _instants = instants;

    // find out all the voltage sources in the components
    for (auto component = _components.begin(); component != _components.end(); component++)
    {
        // treat Capacitors as Voltage sources
        if (((*component)->get_type() == "V") or ((*component)->get_type() == "C"))
        {
            _voltages.push_back(*component);
        }
    }

    // initialise _A and _b to correct dimension with zeros
    int dimension = _nodes.size() + _voltages.size() - 1;
    _A = Eigen::MatrixXd::Zero(dimension, dimension);
    _b = Eigen::MatrixXd::Zero(dimension, 1);

    // calculate and fill in elements in _b and _A
    // _A = | G B | where G is conductance matrix, B describes potential differences across voltage sources
    //      | C 0 | C = B^T
    // fill in the Conductance matrix G for _A
    if (_nodes[0]->get_name() != "0")
    {
        cerr << endl;
        cerr << "🚧  ERROR: missing GND" << endl;
        cerr << endl;
        exit(1);
    }
    for (auto it = _nodes.begin() + 1; it != _nodes.end(); it++)
    {
        int row = it - _nodes.begin() - 1;
        // cout << *(*it) << " row: " << row << endl;
        for (auto jt = _nodes.begin() + 1; jt != _nodes.end(); jt++)
        {
            int col = jt - _nodes.begin() - 1;
            // cout << *(*jt) << " row: " << row << " col: " << col << endl;
            _A(row, col) = (*it)->get_conductance(_f, (*jt));
        }
        double current = (*it)->get_current(_t);
        _b(row, 0) = current;
    }

    for (auto voltage = _voltages.begin(); voltage != _voltages.end(); voltage++)
    {
        int row = _nodes.size() + voltage - _voltages.begin() - 1;
        // cout << "row: " << row << endl;
        for (auto node = _nodes.begin() + 1; node != _nodes.end(); node++)
        {
            int col = node - _nodes.begin() - 1;
            // cout << "row: " << row << "col: " << col << endl;
            if ((*voltage)->get_node("p") == *node)
            {
                _A(row, col) = 1.0;
                _A(col, row) = 1.0;
            }
            else if ((*voltage)->get_node("n") == *node)
            {
                _A(row, col) = -1.0;
                _A(col, row) = -1.0;
            }
            _b(row, 0) = (*voltage)->get_voltage(_t, (*voltage)->get_node("p"));
        }
    }
}

void Circuit::update_b(double t)
{
    for (auto it = _nodes.begin() + 1; it != _nodes.end(); it++)
    {
        int row = it - _nodes.begin() - 1;
        double current = (*it)->get_current(_t);
        _b(row, 0) = current;
    }
    for (auto voltage = _voltages.begin(); voltage != _voltages.end(); voltage++)
    {
        int row = _nodes.size() + voltage - _voltages.begin() - 1;
        // cout << "row: " << row << endl;
        for (auto node = _nodes.begin() + 1; node != _nodes.end(); node++)
        {
            int col = node - _nodes.begin() - 1;
            // cout << "row: " << row << "col: " << col << endl;
            _b(row, 0) = (*voltage)->get_voltage(_t, (*voltage)->get_node("p"));
        }
    }
}

ostream &operator<<(ostream &os, Circuit &circuit)
{
    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ " << circuit._instants.size() << " instants in total" << endl;
    os << "==================================================" << endl;
    os << "From " << circuit._instants[0] << " to " << circuit._instants[circuit._instants.size() - 1] << ", with step: " << circuit._instants[1] << endl;

    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ " << circuit._components.size() << " components in total" << endl;
    os << "==================================================" << endl;
    os << setw(12) << "get_type()" << setw(20) << "get_property()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage(t)" << setw(18) << "check_grounded()" << endl;
    for (auto it = circuit._components.begin(); it != circuit._components.end(); it++)
    {
        os << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_property() << setw(20) << (*it)->get_conductance(1000) << setw(16) << (*it)->get_node("p")->get_name() << setw(18) << (*it)->get_node("n")->get_name() << setw(18) << (*it)->get_current(circuit._t, (*it)->get_node("p")) << setw(18) << (*it)->get_voltage(circuit._t, (*it)->get_node("p")) << setw(18) << (*it)->check_grounded() << endl;
    }

    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ " << circuit._nodes.size() - 1 << " nodes in total except ground" << endl;
    os << "==================================================" << endl;
    os << setw(20) << "Node Names:" << setw(20) << "get_current:" << endl;
    for (auto it = circuit._nodes.begin(); it != circuit._nodes.end(); it++)
    {
        if ((*it)->get_name() != "0")
        {
            os << setw(20) << (*it)->get_name() << setw(20) << (*it)->get_current(circuit._t) << endl;
        }
    }

    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ matrix A, with dimension " << circuit._A.rows() << " x " << circuit._A.cols() << endl;
    os << "==================================================" << endl;
    os << circuit._A << endl;

    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ vector b, with dimension " << circuit._b.rows() << " x " << circuit._b.cols() << endl;
    os << "==================================================" << endl;
    os << circuit._b << endl;

    return os;
}