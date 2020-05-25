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
    string _super_node = "";

public:
    /**
     * @brief Construct a new Node object
     * 
     * @param components a vector of components that contains the current node
     * @param name the name of the current node
     */
    Node(vector<Component *> components, string name);

    /**
     * @brief Destroy the Node object
     * 
     */
    ~Node();

    /**
     * @brief Get the conductance between current node and another node
     * 
     * @param node name of the other node
     * @return complex<double> conductance
     */
    complex<double> get_conductance(double f, string node);

    // /**
    //  * @brief Get the total conductance linked to the current node
    //  *
    //  * @param f frequency of which the circuit is working on
    //  * @return complex<double> conductance
    //  */
    // complex<double> get_node_conductance(double f);

    /**
     * @brief Get the "value" of the current node for "b" in A·x=b
     * 
     * @param t the required time instant
     * @return double return get_current()
     *         if the current node 
     *          does not contain voltage source
     *          OR
     *          is the negative node of a floating node
     *         else return get_voltage()
     */
    double get_value(double t);

    /**
     * @brief Get the voltage of the current node
     *        if the current node:
     *          contains a grounded voltage source 
     *          OR
     *          the positive node of a floating node
     * 
     * @param t the required time instant
     * @return double the voltage value at the required instant
     */
    double get_voltage(double t);

    /**
     * @brief Get the currrent of the current node
     * 
     * @param t the required time instant
     * @return double the current value at the required instant
     */
    double get_current(double t);

    /**
     * @brief check whether the current node contains voltage source or current source
     * 
     */
    void contain_voltage_or_current();
};

#endif