#include "transient.hpp"

void transient::set_instant(vector<double> temp){
    instant = temp;
}

vector<double> transient::get_instant(){
    return instant;
}

void transient::set_simulation(circuit* temp){
    for(int i = 0; i < instant.size(); i++){
        circuit* y = new circuit(temp->get_freq(),temp->get_comp());
        y->set_time(instant[i]);
        simulation.push_back(y);
    }
}

int transient::get_simulation_size(){
    return simulation.size();
}