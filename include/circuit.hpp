#ifndef circuit_hpp
#define circuit_hpp

#include "parser.hpp"
#include "component.hpp"
#include "eigen/Core"
#include "eigen/Dense"

using namespace std;

class Circuit
{
private:
    vector<Component *> _components; // all the components in the circuit including voltage sources
    vector<Component *> _voltages;   // voltage sources forms a seperated vector since MNA required special treat to voltage sources
    vector<Node *> _nodes;           // all the nodes in the circuit
    Eigen::MatrixXd _A;              // only change if nonlinear components present
    Eigen::VectorXd _b;              // b in A·x = b; should be empty initially;
    Eigen::VectorXd _x;              // x in A·x = b; should be empty initially;
    double _step = 0.0;              // length of each instance
    double _end = 0.0;               // end time of simulation
    double _time = 0.0;              // current time

public:
    /**
     * @brief Construct a new Circuit object
     * 
     * @param nodes all the nodes in a circuit 
     * @param components  all the components in a circuit
     * @param step length of each instance
     * @param end end time of simulation 
     */
    Circuit(vector<Node *> nodes, vector<Component *> components, double step, double end);

    /**
     * @brief check whether paralleled voltages exist in the circuit, exit(1) if there are
     * 
     * @param components components needed to check
     */
    void check_parallel_voltages(vector<Component *> components);

    /**
     * @brief update the b matrix in A·x = b
     * 
     */
    void update_b();

    /**
     * @brief update the A matrix in A·x = b
     * 
     */
    void update_A();

    /**
     * @brief solve the equation A·x = b
     * 
     */
    void solve_matrix();

    /**
     * @brief solve the states of nonlinear components 
     * 
     */
    void process_nonlinear_components();

    /**
     * @brief print the title of the tsv format output 
     * 
     */
    void print_table_title();

    /**
     * @brief print voltage_across and current_through of every component in one line in the order of the title
     * 
     */
    void print();

    /**
     * @brief loop through instants, solve and output voltages and current
     * 
     */
    void loop();

    /**
     * @brief print the basic infomation of a circuit
     * 
     * @param os 
     * @param circuit 
     * @return ostream& 
     */
    friend ostream &operator<<(ostream &os, Circuit &circuit);
};

ostream &operator<<(ostream &os, Circuit &circuit);

#endif
