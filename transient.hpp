#ifndef TRANSIENT_HPP
#define TRANSIENT_HPP

#include <iostream>
#include "Component.hpp"
#include "node.hpp"
#include "circuit.hpp"

using namespace std;

class transient{
private:
  vector<double> instant;

  vector<circuit*> simulation;

public:
    transient(){};

    ~transient(){};

    void set_instant(vector<double> temp);

    vector<double> get_instant();

    void set_simulation(circuit* temp);

    int get_simulation_size();


};

#endif
