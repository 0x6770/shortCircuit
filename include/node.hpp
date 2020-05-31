#ifndef node_hpp
#define node_hpp

#include <vector>
#include <string>
#include <complex>
#include <algorithm>

using namespace std;

class Component;

/**
 * @brief An abstaction of a physical node
 * 
 */
class Node
{
private:
    string _name;
    double _node_voltage;
    vector<Component *> _components;

public:
    /**
     * @brief Construct a new Node object
     * 
     * @param name the name of the current node
     */
    Node(const string name);

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
    double get_conductance(Node *node);

    /**
     * @brief Get the components of the current node
     * 
     * @return const vector<Component *> _components 
     */
    vector<Component *> get_components();

    /**
     * @brief add a component to _components
     * 
     * @param component 
     */
    void add_components(Component *component);

    /**
     * @brief Get the name of the current node
     * 
     * @return string 
     */
    string get_name();

    /**
     * @brief Get the voltage of the current node
     * 
     * @param t the required time instant
     * @return double the nodal voltage value from previous instant
     */
    double get_node_voltage();

    /**
     * @brief Get the currrent of the current node
     * 
     * @param t the required time instant
     * @return double the current value at the required instant
     */
    double get_current();

    /**
     * @brief Get the current flow into the current node of the given component
     * 
     * @param comp 
     * @return double 
     */
    double get_current_through(double t, Component *comp);

    void set_node_voltage(double voltage);

    /**
     * @brief check whether a component is voltage source or current source
     * 
     * @param comp A component
     */
    friend ostream &operator<<(ostream &os, Node &node);
};

ostream &operator<<(ostream &os, Node &node);

bool compare_node(Node *node_a, Node *node_b);

Node *get_or_create_node(vector<Node *> &nodes, const string &node);

#endif