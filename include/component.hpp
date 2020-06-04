#ifndef component_hpp
#define component_hpp

#include "node.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

class Component
{
protected:
    string _type;
    string _name;
    Node *_node_p; // positive node/terminal
    Node *_node_n; // negative node/terminal
    double _property = 0.0;
    double _current_through = 0.0;
    double _voltage_across = 0.0;

public:
    Component() {}

    /**
     * @brief Get the type of a component
     * 
     * @return string the _type of the component
     */
    string get_type();

    /**
     * @brief Get the name of a component
     * 
     * @return string the _name of the component
     */
    string get_name();

    /**
     * @brief Get a specific node of a component
     * 
     * @param x the name of the node within the component, e.g. "p", "n"
     * @return Node* the node object required
     */
    Node *get_node(string x);

    /**
     * @brief Get the voltage across a component
     * 
     * @param t required if voltage is time related
     * @param node used to determine the orientation of the component
     * @return double value of voltage across the component
     */
    virtual double get_voltage_across(double t, Node *node);

    /**
     * @brief Get the current source value of a component
     * 
     * @param node used to determine the orientation of the component
     * @return double return current value if the component is a current source, return 0 otherwise
     */
    virtual double get_current(Node *node);

    /**
     * @brief Get the current flow through a component
     * 
     * @param node used to determine the orientation of the component
     * @return double value of current through a component
     *                current is positive if flow into the positive terminal of a component
     */
    virtual double get_current_through(Node *node);

    /**
     * @brief Get the property of a component
     *        property: resistance, capacitance, etc
     * @return double value of property
     */
    virtual double get_property();

    /**
     * @brief Get the conductance of a component
     * 
     * @return double value of conductance
     */
    virtual double get_conductance();

    /**
     * @brief Set the current_through property of a component
     * 
     * @param current new current_through value
     */
    virtual void set_current_through(double current);

    /**
     * @brief Set the voltage_across property of a component
     * 
     * @param voltage new voltage_across value
     */
    virtual void set_voltage_across(double voltage);

    /**
     * @brief check whether a component contains a specific node
     * 
     * @param node the name of a specific node, use name so "0" can be checked more conveniently
     * @return true if the component does contain the given node
     * @return false if the component does not contain the given node
     */
    bool contain_node(string node);

    virtual ~Component() {}
};

#endif