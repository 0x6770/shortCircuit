#include "helper_function.hpp"



double integrate(double a, double b){
    double step = 1000.00;
    double h = (b-a)/step;
    double s = f(a) + f(b);
    for(int i = 1; i < step; i++){
        s += 2*f(a+i*h);
    }
    return (h/2)*s;
}