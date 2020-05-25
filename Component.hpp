#ifndef TRANSIENT_SIMULATOR_COMPONENT_HPP
#define TRANSIENT_SIMULATOR_COMPONENT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <complex>
using namespace std;
class Component {
private:
    string _identifier;
    string _n1;
    string _n2;
    double _value;
    // for the convention in LTspice
    // the node with positive polarity always appear first, so the first pin of any power_source should be positive
public:
    Component(const string &name,const string &n1,const string &n2,const double &value ){
        _identifier = name;
        _n1 = n1;
        _n2 = n2;
        _value = value;
    }
    ~Component(){};

    // order matters for the power source
    // for the consideration of super node
    // for judging the direction of current source
    string get_node(int n);

    //return the value of this component;
    double get_value();

    //return the identifier of this component;
    string get_identifier();

    //tell whether the component is voltage_source;
    //TODO: not considered ac yet
    bool is_voltage();

    //tell whether the component is current_source;
    bool is_current();

    //check capacitors and inductors;
    bool is_passive();

};



#endif //TRANSIENT_SIMULATOR_COMPONENT_HPP
