#ifndef components_hpp
#define components_hpp

#include "component.hpp"

#include <iostream>
#include <complex>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>

using namespace std;

class Inductor : public Component
{
public:
    Inductor(string name, string node_p, string node_n, double property);

    complex<double> get_conductance(double f);
};

class Capacitor : public Component
{
public:
    Capacitor(string name, string node_p, string node_n, double property);

    complex<double> get_conductance(double f);
};

class Resistor : public Component
{
public:
    Resistor(string name, string node_p, string node_n, double property);

    complex<double> get_conductance(double f);
};

class Voltage : public Component
{
public:
    Voltage(string name, string node_p, string node_n, double amplitude);

    double get_voltage(double t, string node);
};

class SINE_Voltage : public Component
{
public:
    SINE_Voltage(string name, string node_p, string node_n, double bias, double amplitude, double frequency);

    double get_voltage(double t, string node);
};

class Current : public Component
{
protected:
public:
    Current(string name, string node_p, string node_n, double amplitude);

    double get_current(double t, string node);
};

#endif
