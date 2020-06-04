#include "../include/nonlinear_components.hpp"

Diode_D::Diode_D(string name, Node *node_p, Node *node_n)
{
    _name = name;
    _type = "D";
    _model = "D";
    _node_p = node_p;
    _node_n = node_n;
    _I_s = 1.0e-12;            // saturation current
    _V_t = 0.02585;            // thermal curent
    _current_through = 1.0e-3; // initial guess of current through the diode
};

double Diode_D::get_conductance()
{
    double result = _V_t * log(abs(_current_through) / _I_s + 1.0);
    return result;
}

double Diode_D::get_current_through(Node *node)
{
    if (node == _node_p)
    {
        return _current_through;
    }
    else if (node == _node_n)
    {
        return -1.0 * _current_through;
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid node, " << node << " not exit in " << _node_p << " and " << _node_n << endl;
        cerr << endl;
        exit(1);
    }
};

void Diode_D::set_current_through(double current)
{
    _current_through = current;
};
