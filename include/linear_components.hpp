#ifndef linear_components_hpp
#define linear_components_hpp

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

    double get_current_through(Node *node);

    double get_current(Node *node);
};

/** 
 * @brief Capacitor Class 
 * 
 */
class Capacitor : public Component
{
public:
    Capacitor(string name, Node *node_p, Node *node_n, double property);

    double get_voltage_across(double t, Node *node);

    void set_voltage_across(double voltage);
};

/** 
 * @brief Resistor Class 
 * 
 */
class Resistor : public Component
{
public:
    Resistor(string name, Node *node_p, Node *node_n, double property);

    double get_conductance();

    double get_current_through(Node *node);
};

/** 
 * @brief Voltage Class 
 * 
 */
class Voltage : public Component
{
public:
    Voltage(string name, Node *node_p, Node *node_n, double amplitude);

    double get_voltage_across(double t, Node *node);

    void set_current_through(double current);
};

/** 
 * @brief SINE Voltage Class 
 * 
 */
class SINE_Voltage : public Component
{
private:
    double _bias = 0.0;
    double _frequency = 0.0;
    double _time;

public:
    SINE_Voltage(string name, Node *node_p, Node *node_n, double bias, double amplitude, double frequency);

    double get_voltage_across(double t, Node *node);

    void set_current_through(double current);
};

/** 
 * @brief Current Class 
 * 
 */
class Current : public Component
{
public:
    Current(string name, Node *node_p, Node *node_n, double amplitude);

    double get_current(Node *node);
};

#endif
