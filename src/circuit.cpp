#include "circuit.hpp"

Circuit::Circuit(vector<Node *> nodes, vector<Component *> components, double step, double end)
{
    _components = components;
    _nodes = nodes;
    _step = step;
    _end = end;
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
    _b = Eigen::VectorXd::Zero(dimension, 1);

    // determine whether the current circuit has a ground
    if (_nodes[0]->get_name() != "0")
    {
        cerr << endl;
        cerr << "🚧  ERROR: missing GND" << endl;
        cerr << endl;
        exit(1);
    }

    // calculate and fill in elements in _b and _A
    // _A = | G B | where G is conductance matrix, B describes potential differences across voltage sources
    //      | C 0 | C = B^T
    // fill in the Conductance matrix G for _A
    for (auto it = _nodes.begin() + 1; it != _nodes.end(); it++)
    {
        int row = it - _nodes.begin() - 1;
        // cout << *(*it) << " row: " << row << endl;
        for (auto jt = _nodes.begin() + 1; jt != _nodes.end(); jt++)
        {
            int col = jt - _nodes.begin() - 1;
            // cout << *(*jt) << " row: " << row << " col: " << col << endl;
            _A(row, col) = (*it)->get_conductance(*jt);
        }
        double current = (*it)->get_current();
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
            _b(row, 0) = (*voltage)->get_voltage_across(_time, (*voltage)->get_node("p"));
        }
    }
}

void Circuit::solve()
{
    // solve x from x = A^{-1}·b
    _x = _A.inverse() * _b;

    // update nodal voltages
    for (auto node = _nodes.begin() + 1; node != _nodes.end(); node++)
    {
        int row = node - _nodes.begin() - 1;
        (*node)->set_node_voltage(_x[row]);
    }

    // update current flow through voltage sources
    for (auto voltage = _voltages.begin(); voltage != _voltages.end(); voltage++)
    {
        int row = _nodes.size() + voltage - _voltages.begin() - 1;
        (*voltage)->set_current_through(_x[row]);
    }

    for (auto comp = _components.begin(); comp != _components.end(); comp++)
    {
        // update current flow through Inductors
        if ((*comp)->get_type() == "L")
        {
            double pre_voltage = -(*comp)->get_node("p")->get_node_voltage() + (*comp)->get_node("n")->get_node_voltage();
            double pre_current = (*comp)->get_current_through((*comp)->get_node("p"));
            double result = pre_current + (_step * pre_voltage) / (*comp)->get_property(); // Forward Euler v(t+Δt)≈v(t)+(Δt·i(t))/C
            // double result = pre_current + (_step * pre_voltage) / (2.0 * (*comp)->get_property()); // Trapezoid v(t+Δt)≈v(t)+(Δt·i(t))/(2C)
            // cout << "result: " << result << " pre_voltage: " << pre_voltage << " _step: " << _step << " pre_current: " << pre_current << " (*comp)->get_property(): " << (*comp)->get_property() << endl;
            (*comp)->set_current_through(result);
        }
        // update voltage across Capacitor
        else if ((*comp)->get_type() == "C")
        {
            // cerr << "here is a capacitor " << endl;
            double pre_voltage = (*comp)->get_voltage_across(_step, (*comp)->get_node("p"));
            double pre_current = (*comp)->get_current_through((*comp)->get_node("p"));
            double result = pre_voltage + (_step * pre_current / (*comp)->get_property()); // Forawrd Euler i(t+Δt)≈i(t)+(Δt·v(t))/L
            // double result = pre_voltage + (_step * pre_current / (2.0 * (*comp)->get_property()));  // Trapezoid i(t+Δt)≈i(t)+(Δt·v(t))/(2L)
            // cout << "pre_voltage: " << pre_voltage << "_step: " << _step << "pre_current: " << pre_current << "(*comp)->get_property()" << (*comp)->get_property() << endl;
            (*comp)->set_voltage_across(result);
        }
    }
};

void Circuit::update_b()
{
    for (auto it = _nodes.begin() + 1; it != _nodes.end(); it++)
    {
        int row = it - _nodes.begin() - 1;
        double current = (*it)->get_current();
        _b(row, 0) = current;
    }
    for (auto voltage = _voltages.begin(); voltage != _voltages.end(); voltage++)
    {
        int row = _nodes.size() + voltage - _voltages.begin() - 1;
        // cout << "row: " << row << endl;
        _b(row, 0) = (*voltage)->get_voltage_across(_time, (*voltage)->get_node("p"));
    }
}

void Circuit::print_table_title()
{
    cout << "time"
         << "\t";
    for (auto node = _nodes.begin() + 1; node != _nodes.end(); node++)
    {
        cout << "V(" << (*node)->get_name() << ")\t";
    }
    for (auto voltage = _voltages.begin(); voltage != _voltages.end(); voltage++)
    {
        cout << "I(" << (*voltage)->get_name() << ")\t";
    }
    for (auto component = _components.begin(); component != _components.end(); component++)
    {
        if ((*component)->get_type() != "C" or (*component)->get_type() != "V")
        {
            cout << "I(" << (*component)->get_name() << ")\t";
        }
    }
    cout << endl;
}

void Circuit::print()
{
    cout << _time << "\t";
    for (int i = 0; i < _x.rows(); i++)
    {
        cout << _x[i] << "\t";
    }
    for (auto component = _components.begin(); component != _components.end(); component++)
    {
        if ((*component)->get_type() != "C" or (*component)->get_type() != "V")
        {
            cout << (*component)->get_current_through((*component)->get_node("p")) << "\t";
        }
    }
    cout << endl;
}

ostream &operator<<(ostream &os, Circuit &circuit)
{
    // os << endl;
    // os << endl;
    // os << "==================================================" << endl;
    // os << "✅ " << circuit._end / circuit._step << " instants in total" << endl;
    // os << "==================================================" << endl;
    // os << "From " << 0 << " to " << circuit._end << ", with step: " << circuit._step << endl;

    // os << endl;
    // os << endl;
    // os << "==================================================" << endl;
    // os << "✅ " << circuit._components.size() << " components in total" << endl;
    // os << "==================================================" << endl;
    // os << setw(12) << "get_type()" << setw(20) << "get_property()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage_across(t)" << setw(18) << "check_grounded()" << endl;
    // for (auto it = circuit._components.begin(); it != circuit._components.end(); it++)
    // {
    //     os << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_property() << setw(20) << (*it)->get_conductance() << setw(16) << (*it)->get_node("p")->get_name() << setw(18) << (*it)->get_node("n")->get_name() << setw(18) << (*it)->get_current(circuit._step, (*it)->get_node("p")) << setw(18) << (*it)->get_voltage_across(circuit._step, (*it)->get_node("p")) << setw(18) << (*it)->check_grounded() << endl;
    // }

    // os << endl;
    // os << endl;
    // os << "==================================================" << endl;
    // os << "✅ " << circuit._nodes.size() - 1 << " nodes in total except ground" << endl;
    // os << "==================================================" << endl;
    // os << setw(20) << "Node Names:" << setw(20) << "get_current:" << endl;
    // for (auto it = circuit._nodes.begin(); it != circuit._nodes.end(); it++)
    // {
    //     if ((*it)->get_name() != "0")
    //     {
    //         os << setw(20) << (*it)->get_name() << setw(20) << (*it)->get_current(circuit._step) << endl;
    //     }
    // }

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

void Circuit::loop()
{
    print_table_title();
    while (_time <= _end)
    {
        // cerr << *this << endl;
        solve();
        print();
        _time += _step;
        update_b();
    }
}