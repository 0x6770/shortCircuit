#ifndef node_hpp
#define node_hpp

#include "components.hpp"

/**
 * @brief An abstaction of a physical node
 * 
 */
class Node
{
private:
    string _name;
    vector<Component *> _components;
    vector<Component *> _voltages;
    vector<Component *> _currents;
    bool _contain_voltage = false;
    bool _contain_current = false;
    Node *_super_node_positive;
    /**
     * @brief describe how the current node is connected with voltage source
     *        ""    if no voltage source
     *        "g"   if there is grounded source
     *        "p"   if there is no grounded source but a floating voltage source, and the current node is the Positive terminal
     *        "n"   if there is no grounded source but a floating voltage source, and the current node is the Negative terminal
     */
    string _voltage_state = "";

public:
    /**
     * @brief Construct a new Node object
     * 
     * @param components a vector of components that contains the current node
     * @param name the name of the current node
     */
    Node(const vector<Component *> components, const string name);

    /**
     * @brief Destroy the Node object
     * 
     */
    ~Node();

    /**
     * @brief Get the conductance between current node and another node or total conductance related to the current node
     * 
     * @param node name of a node
     * @return complex<double> conductance between current node and another node if another node is provided
     *                         total conductance related to the current node     if the current node is provided
     */
    const complex<double> get_conductance(const double f, const string node);

    /**
     * @brief Get the components of the current node
     * 
     * @return const vector<Component *> _components 
     */
    const vector<Component *> get_components();

    /**
     * @brief Get the name of the current node
     * 
     * @return string 
     */
    string get_name();

    /**
     * @brief Get the state of how the current node is connected with voltage source
     * 
     * @return string ""    if no voltage source
     *                "g"   if there is grounded source
     *                "p"   if there is no grounded source but a floating voltage source, and the current node is the Positive terminal
     *                "n"   if there is no grounded source but a floating voltage source, and the current node is the Negative terminal
     */
    string get_voltage_state();

    /**
     * @brief Get the "value" of the current node for "b" in A·x=b
     * 
     * @param t the required time instant
     * @return double get_current()      if   the current node does not contain voltage source OR is the negative node of a floating node
     *                                   else get_voltage()
     */
    double get_value(const double t);

    /**
     * @brief Get the voltage of the current node
     * 
     * @param t the required time instant
     * @return double the voltage value at the required instant     if      the current node contains a grounded voltage source OR the positive node of a floating node
     *                                                              else    0
     */
    double get_voltage(const double t);

    /**
     * @brief Get the currrent of the current node
     * 
     * @param t the required time instant
     * @return double the current value at the required instant
     */
    double get_current(const double t);

    /**
     * @brief check whether a component is voltage source or current source
     * 
     * @param comp A component
     */
    void is_voltage_or_current(Component *comp);
};

#endif