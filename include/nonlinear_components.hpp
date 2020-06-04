#ifndef nonlinear_components_hpp
#define nonlinear_components_hpp

#include "component.hpp"

using namespace std;

/**
 * @brief Base class for all Diode models
 * 
 */
class Diode : public Component
{
protected:
    string _model; // model of diode
    double _I_s; // saturation current
    double _V_t; // thermal voltage
};

/**
 * @brief Diode class for model D
 * 
 */
class Diode_D : public Diode
{
public:
    Diode_D(string name, Node *node_p, Node *node_n);

    double get_conductance();

    double get_current_through(Node *node);

    void set_current_through(double current);
};

#endif