#include "circuit.hpp"

void Circuit::check_parallel_voltages(vector<Component *> components)
{
    for (auto component = components.begin(); component != components.end(); component++)
    {
        if ((*component)->get_type() == "V")
        {
            Component *voltage = (*component);
            Node *positive = voltage->get_node("p");
            Node *negative = voltage->get_node("n");
            vector<Component *> p_components = positive->get_components();
            for (auto p_component = p_components.begin(); p_component != p_components.end(); p_component++)
            {
                Component *another_voltage = (*p_component);
                if ((another_voltage != voltage) and another_voltage->contain_node(negative->get_name()))
                {
                    spdlog::error("🚧 ERROR: {} and {} are paralleled voltage sources", voltage->get_name(), another_voltage->get_name());
                    exit(1);
                }
            }
        }
    }
}

void Circuit::update_A()
{
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
    }
}

Circuit::Circuit(vector<Node *> nodes, vector<Component *> components, double step, double end)
{
    _components = components;
    _nodes = nodes;
    _step = step;
    _end = end;

    // Check whether paralleled voltage sources exist
    check_parallel_voltages(_components);

    // find out all the voltage sources (Voltage sources, Capacitors, Diodes) in the components
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
        spdlog::error("🚧  ERROR: missing GND");
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

void Circuit::solve_matrix()
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
            double pre_voltage = (*comp)->get_node("p")->get_node_voltage() - (*comp)->get_node("n")->get_node_voltage();
            double pre_current = (*comp)->get_current_through((*comp)->get_node("p"));
            double result = pre_current - (_step * pre_voltage) / (*comp)->get_property(); // Forward Euler v(t+Δt)≈v(t)+(Δt·i(t))/C
            // double result = pre_current + (_step * pre_voltage) / (2.0 * (*comp)->get_property()); // Trapezoid v(t+Δt)≈v(t)+(Δt·i(t))/(2C)
            (*comp)->set_current_through(result);
        }
        // update voltage across Capacitor
        else if ((*comp)->get_type() == "C")
        {
            double pre_voltage = (*comp)->get_voltage_across(_step, (*comp)->get_node("p"));
            double pre_current = (*comp)->get_current_through((*comp)->get_node("p"));
            double result = pre_voltage + (_step * pre_current / (*comp)->get_property()); // Forawrd Euler i(t+Δt)≈i(t)+(Δt·v(t))/L
            // double result = pre_voltage + (_step * pre_current / (2.0 * (*comp)->get_property()));  // Trapezoid i(t+Δt)≈i(t)+(Δt·v(t))/(2L)
            (*comp)->set_voltage_across(result);
        }
    }
};

void Circuit::process_nonlinear_components()
{
    double theshold = 1.0e-2;
    double I_s = 1.0e-12;
    double V_t = 0.02585;
    int num_nonlinear = 0;
    vector<Component *> diodes;
    for (auto component = _components.begin(); component != _components.end(); component++)
    {
        if ((*component)->get_type() == "D")
        {
            diodes.push_back(*component);
        }
    }
    // cerr << "Found " << num_nonlinear << " nonlinear components in total" << endl;
    while (diodes.size() > 0)
    // for (int i = 0; i < 5; i++)
    {
        _x = _A.inverse() * _b;
        // spdlog::debug("_A \n {} \n _b \n {} \n _x \n {}", _A, _b, _x);
        for (auto component = _components.begin() + 1; component != _components.end(); component++)
        {
            if ((*component)->get_type() == "D")
            {
                // cerr << "Found Diode: " << (*component)->get_name() << endl;
                spdlog::debug("Found Diode: {}", (*component)->get_name());
                int row = component - _components.begin() + 1;
                double positive = 0.0;
                if ((*component)->get_node("p")->get_name() != "0")
                {
                    positive = _x(find(_nodes.begin(), _nodes.end(), (*component)->get_node("p")) - _nodes.begin() - 1);
                }
                double negative = 0.0;
                if ((*component)->get_node("n")->get_name() != "0")
                {
                    negative = _x(find(_nodes.begin(), _nodes.end(), (*component)->get_node("n")) - _nodes.begin() - 1);
                }
                double pd = positive - negative;
                double old_current = (*component)->get_current_through((*component)->get_node("p"));
                // double new_current = (*component)->get_conductance() * pd;
                double new_current = I_s * (exp(pd / V_t) - 1);
                // cerr << "positive: " << positive << endl;
                // cout << "negative: " << negative << endl;
                // cout << "Voltage across Diode is " << pd << endl;
                // cout << "R_d: " << (*component)->get_conductance() << endl;
                spdlog::debug("PD: {}\told_current: {}\tnew_current: {}", pd, old_current, new_current);
                (*component)->set_current_through(new_current);
                if (abs(new_current - old_current) < abs(new_current) * theshold or abs(new_current - old_current) < abs(old_current) * theshold or new_current == 0.0)
                {
                    // cout << "REACH theshold" << endl;
                    for (auto diode = diodes.begin(); diode != diodes.end(); diode++)
                    {
                        int index = diode - diodes.begin();
                        if (*diode == *component)
                        {
                            diodes.erase(diode);
                            break; // avoid segmentation fault, only one diode is removed every time
                        }
                    };
                }
            }
        }
        update_A();
        update_b();
    }
}

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
        if ((*component)->get_type() != "C" and (*component)->get_type() != "V")
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
        if ((*component)->get_type() != "C" and (*component)->get_type() != "V")
        {
            cout << (*component)->get_current_through((*component)->get_node("p")) << "\t";
        }
    }
    cout << endl;
}

ostream &operator<<(ostream &os, Circuit &circuit)
{
    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ " << circuit._end / circuit._step << " instants in total" << endl;
    os << "==================================================" << endl;
    os << "From " << 0 << " to " << circuit._end << ", with step: " << circuit._step << endl;

    os << endl;
    os << endl;
    os << "==================================================" << endl;
    os << "✅ " << circuit._components.size() << " components in total" << endl;
    os << "==================================================" << endl;
    os << setw(12) << "get_type()" << setw(20) << "get_property()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage_across(t)" << endl;
    for (auto it = circuit._components.begin(); it != circuit._components.end(); it++)
    {
        os << setw(12) << (*it)->get_type() << setw(20) << (*it)->get_property() << setw(20) << (*it)->get_conductance() << setw(16) << (*it)->get_node("p")->get_name() << setw(18) << (*it)->get_node("n")->get_name() << setw(18) << (*it)->get_current((*it)->get_node("p")) << setw(18) << (*it)->get_voltage_across(circuit._step, (*it)->get_node("p")) << setw(18) << endl;
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

void Circuit::loop()
{
    print_table_title();
    while (_time <= _end)
    {
        spdlog::info("{}", _time);
        process_nonlinear_components(); // using Newton Raphson method to find states of nonlinear component
        solve_matrix();
        print();
        _time += _step;
        update_b();
    }
}