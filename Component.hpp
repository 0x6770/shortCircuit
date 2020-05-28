#ifndef TRANSIENT_SIMULATOR_COMPONENT_HPP
#define TRANSIENT_SIMULATOR_COMPONENT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <complex>
#include <cmath>
using namespace std;


class Component{
protected:
    string _identifier;
    int _n1; // first node identifier
    int _n2; // second node identifier
    double _value;
    // for the convention in LTspice
    // the node with positive polarity always appear first, so the first pin of any power_source should be positive

public:
    Component(){};
    Component(const string &name,const string &n1,const string &n2,const double &value ){
        _identifier = name;
        _n1 = convert_node_to_int(n1);
        _n2 = convert_node_to_int(n2);
        _value = value;
    }
    ~Component(){};

    // order matters for the power source
    // for the consideration of super node
    // for judging the direction of current source
    int get_node(int n);

    //return the value of this component;
    virtual double get_value();

    //return the identifier of this component;
    string get_identifier();

    //tell whether the component is voltage_source;
    //TODO: not considered ac yet
    bool is_voltage();

    //tell whether the component is current_source;
    bool is_current();

    //check capacitors and inductors;
    bool is_passive();

    int convert_node_to_int(string a);

    bool is_grounded();

    virtual void set_time(double time){};
};


class SIN : public Component{
private:
    double dc_offset;
    double ac_amplitude;
    double frequency;

public:
    double _time = 0.0;
    // set initial value
    SIN(string name,string n1,string n2,double DC, double amplitude, double set_frequency ){
        _identifier = name;
        _n1 = convert_node_to_int(n1);
        _n2 = convert_node_to_int(n2);
        _value = DC;
        dc_offset = DC;
        ac_amplitude = amplitude;
        frequency = set_frequency;
    }
    double get_real_voltage(double time);

    void set_time(double time);

    double get_value();
};


#endif //TRANSIENT_SIMULATOR_COMPONENT_HPP
