#ifndef SHORTCIRCUIT_NODES_HPP
#define SHORTCIRCUIT_NODES_HPP

#include "components.hpp"
#include "circuit.hpp"
#include <iostream>
#include <string>

class Node{
private:
    string _name;
    double _voltage;
    vector<Component*> branches;
    bool is_ground;
public:
    Node(string name,){

    }
    vector<Node*> set_nodes(Circuit circuit) {
        vector<Node*> result;
        Node* temp = nullptr;
        for(int i = 0; i < circuit.get_nodes().size();i++){
            temp = new
        }
        return result;
    }

};

#endif //SHORTCIRCUIT_NODES_HPP
