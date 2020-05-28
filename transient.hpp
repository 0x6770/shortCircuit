#ifndef SHORTCIRCUIT_TRANSIENT_HPP
#define SHORTCIRCUIT_TRANSIENT_HPP

#include <iostream>
#include <vector>
using namespace std;

class transient {
private:
    double stop_time;
    double time_step;
public:

    transient(double stop, double step){
        stop_time = stop;
        time_step = step;
    }

    double get_stop_time();

    double get_time_step();

};


#endif //SHORTCIRCUIT_TRANSIENT_HPP
