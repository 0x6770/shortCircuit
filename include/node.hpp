#ifndef node_hpp
#define node_hpp

#include "component.hpp"

#include <iostream>
#include <vector>
#include <complex>
#include <string>

using namespace std;

class Node
{
private:
    string _name;
    int _index;
    // default value for current and voltage are zero
    double _current = 0.0;
    double _voltage = 0.0;
    vector<Component *> _branches;
    bool _is_connected_current = false;
    bool _is_connected_voltage = false;

public:
    //empty node constructors
    Node(string name)
    {
        _name = name;
    };

    string get_name();

    int get_index();

    double get_current();

    double get_voltage();

    vector<Component *> get_branches();

    /**
     * @brief add branches to the current node
     * 
     * @param branch a Component
     */
    void add_branches(Component *branch);

    /**
     * @brief check whether a given node is equal to the current node
     * 
     * @param a a Node
     * @return true     if the given node is equal to the current node
     * @return false    if the given node is not equal to the current node 
     */
    bool operator==(Node *a);

    bool get_is_connected_voltage();

    void set_current();
};

#endif // node_hpp
