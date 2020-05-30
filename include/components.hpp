#ifndef components_hpp
#define components_hpp

#include "component.hpp"

using namespace std;

/** 
 * @brief Inductor Class
 * 
 */
class Inductor : public Component
{
public:
    Inductor(string name, Node *node_p, Node *node_n, double property);
};

/** 
 * @brief Capacitor Class 
 * 
 */
class Capacitor : public Component
{
public:
    Capacitor(string name, Node *node_p, Node *node_n, double property);

    double update_voltage(double t, double current, Node *node);

    double get_voltage(double t, Node *node);
};

/** 
 * @brief Resistor Class 
 * 
 */
class Resistor : public Component
{
public:
    Resistor(string name, Node *node_p, Node *node_n, double property);

    double get_conductance(double f);
};

/** 
 * @brief Voltage Class 
 * 
 */
class Voltage : public Component
{
public:
    Voltage(string name, Node *node_p, Node *node_n, double amplitude);

    double get_voltage(double t, Node *node);
};

/** 
 * @brief SINE Voltage Class 
 * 
 */
class SINE_Voltage : public Component
{
public:
    SINE_Voltage(string name, Node *node_p, Node *node_n, double bias, double amplitude, double frequency);

    double get_voltage(double t, Node *node);
};

/** 
 * @brief Current Class 
 * 
 */
class Current : public Component
{
public:
    Current(string name, Node *node_p, Node *node_n, double amplitude);

    double get_current(double t, Node *node);
};

#endif
