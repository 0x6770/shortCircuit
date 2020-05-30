#ifndef circuit_hpp
#define circuit_hpp

#include "parser.hpp"
#include "component.hpp"
#include "../Eigen/Core"

using namespace std;

class Circuit
{
private:
    vector<Component *> _components;
    vector<Component *> _voltages;
    vector<Node *> _nodes;
    vector<double> _instants;
    vector<Component *> _used_voltages;
    Eigen::MatrixXd _A; // should not vary with time;
    Eigen::MatrixXd _b; // b in Ax = b; should be empty initially;
    double _f = 1000;
    double _t = 1;

public:
    Circuit(vector<Node *> nodes, vector<Component *> components, vector<double> instants);

    friend ostream &operator<<(ostream &os, Circuit &circuit);
};

ostream &operator<<(ostream &os, Circuit &circuit);

#endif
