#ifndef circuit_hpp
#define circuit_hpp

#include "parser.hpp"
#include "component.hpp"
#include "../Eigen/Core"
#include "../Eigen/Dense"

using namespace std;

class Circuit
{
private:
    vector<Component *> _components;
    vector<Component *> _voltages;
    vector<Node *> _nodes;
    vector<Component *> _used_voltages;
    Eigen::MatrixXd _A; // should not vary with time;
    Eigen::VectorXd _b; // b in Ax = b; should be empty initially;
    Eigen::VectorXd _x; // x in Ax = b; should be empty initially;
    double _step = 0.0; // step of time
    double _end = 0.0;
    double _time = 0.0; // current time

public:
    Circuit(vector<Node *> nodes, vector<Component *> components, double step, double end);

    void update_b();

    void solve();

    void print_table_title();

    void print();

    void loop();

    friend ostream &operator<<(ostream &os, Circuit &circuit);
};

ostream &operator<<(ostream &os, Circuit &circuit);

#endif
