#include "parser.hpp"
#include "components.hpp"
#include "components_utils.hpp"
#include "circuit.hpp"

#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

int main()
{
    double t = 1.1;
    double f = 150;
    double A = 2.5;
    double bias = 0.5;

    // test instantiation for every kind of component
    cout << "🧪 Testing instantiation" << endl;
    Component *V1 = new Voltage("5", "3", A);
    Component *V2 = new Voltage("5", "0", A);
    Component *V_sin1 = new SINE_Voltage("9", "2", bias, A, f);
    Component *V_sin2 = new SINE_Voltage("9", "2", bias, A, f);
    Component *R = new Resistor("1", "2", f);
    Component *C = new Capacitor("23", "2", f);
    Component *L = new Inductor("3", "100", f);

    // test get_conductance for every kind of component
    cout << "🧪 Testing member function" << endl;
    cout << setw(12) << "get_type()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage(t)" << setw(18) << "check_grounded()" << endl;
    cout << setw(12) << V1->get_type() << setw(20) << V1->get_conductance(1000) << setw(16) << V1->get_node("p") << setw(18) << V1->get_node("n") << setw(18) << V1->get_current(t) << setw(18) << V1->get_voltage(t) << setw(18) << V1->check_grounded() << endl;
    cout << setw(12) << V2->get_type() << setw(20) << V2->get_conductance(1000) << setw(16) << V2->get_node("p") << setw(18) << V2->get_node("n") << setw(18) << V2->get_current(t) << setw(18) << V2->get_voltage(t) << setw(18) << V2->check_grounded() << endl;
    cout << setw(12) << V_sin1->get_type() << setw(20) << V_sin1->get_conductance(1000) << setw(16) << V_sin1->get_node("p") << setw(18) << V_sin1->get_node("n") << setw(18) << V_sin1->get_current(t) << setw(18) << V_sin1->get_voltage(t) << setw(18) << V_sin1->check_grounded() << endl;
    cout << setw(12) << V_sin2->get_type() << setw(20) << V_sin2->get_conductance(1000) << setw(16) << V_sin2->get_node("p") << setw(18) << V_sin2->get_node("n") << setw(18) << V_sin2->get_current(t) << setw(18) << V_sin2->get_voltage(t) << setw(18) << V_sin2->check_grounded() << endl;
    cout << setw(12) << R->get_type() << setw(20) << R->get_conductance(1000) << setw(16) << R->get_node("p") << setw(18) << R->get_node("n") << setw(18) << R->get_current(t) << setw(18) << R->get_voltage(t) << setw(18) << R->check_grounded() << endl;
    cout << setw(12) << C->get_type() << setw(20) << C->get_conductance(1000) << setw(16) << C->get_node("p") << setw(18) << C->get_node("n") << setw(18) << C->get_current(t) << setw(18) << C->get_voltage(t) << setw(18) << C->check_grounded() << endl;
    cout << setw(12) << L->get_type() << setw(20) << L->get_conductance(1000) << setw(16) << L->get_node("p") << setw(18) << L->get_node("n") << setw(18) << L->get_current(t) << setw(18) << L->get_voltage(t) << setw(18) << L->check_grounded() << endl;
};