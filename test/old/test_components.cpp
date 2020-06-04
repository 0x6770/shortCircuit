#include "parser.hpp"
#include "linear_components.hpp"
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

    Node *a = new Node("a");
    Node *b = new Node("b");
    Node *c = new Node("c");
    Node *d = new Node("d");
    Node *e = new Node("e");

    // test instantiation for every kind of component
    cout << "🧪 Testing instantiation" << endl;
    Component *V1 = new Voltage("V1", a, b, A * 2);
    Component *V2 = new Voltage("V2", a, c, A);
    Component *V_sin1 = new SINE_Voltage("V_sin1", b, e, bias * 2, A, f);
    Component *V_sin2 = new SINE_Voltage("V_sin2", a, e, bias, A, f);
    Component *R = new Resistor("R", a, b, f);
    Component *C = new Capacitor("C", d, e, f);
    Component *L = new Inductor("L", a, d, f);
    Component *D = new Diode_D("D", a, d);

    // test get_conductance for every kind of component
    cout << "🧪 Testing member function" << endl;
    cout << setw(12) << "get_type()" << setw(20) << "get_conductance()" << setw(16) << "get_node(\"p\")" << setw(18) << "get_node(\"n\")" << setw(18) << "get_current(t)" << setw(18) << "get_voltage_across(t)" << setw(18) << "check_grounded()" << endl;
    cout << setw(12) << V1->get_type() << setw(20) << V1->get_conductance() << setw(16) << V1->get_node("p")->get_name() << setw(18) << V1->get_node("n")->get_name() << setw(18) << V1->get_current(V1->get_node("p")) << setw(18) << V1->get_voltage_across(t, V1->get_node("p")) << setw(18) << V1->check_grounded() << endl;
    cout << setw(12) << V2->get_type() << setw(20) << V2->get_conductance() << setw(16) << V2->get_node("p")->get_name() << setw(18) << V2->get_node("n")->get_name() << setw(18) << V2->get_current(V2->get_node("p")) << setw(18) << V2->get_voltage_across(t, V2->get_node("p")) << setw(18) << V2->check_grounded() << endl;
    cout << setw(12) << V_sin1->get_type() << setw(20) << V_sin1->get_conductance() << setw(16) << V_sin1->get_node("p")->get_name() << setw(18) << V_sin1->get_node("n")->get_name() << setw(18) << V_sin1->get_current(V_sin1->get_node("p")) << setw(18) << V_sin1->get_voltage_across(t, V_sin1->get_node("p")) << setw(18) << V_sin1->check_grounded() << endl;
    cout << setw(12) << V_sin2->get_type() << setw(20) << V_sin2->get_conductance() << setw(16) << V_sin2->get_node("p")->get_name() << setw(18) << V_sin2->get_node("n")->get_name() << setw(18) << V_sin2->get_current(V_sin2->get_node("p")) << setw(18) << V_sin2->get_voltage_across(t, V_sin2->get_node("p")) << setw(18) << V_sin2->check_grounded() << endl;
    cout << setw(12) << R->get_type() << setw(20) << R->get_conductance() << setw(16) << R->get_node("p")->get_name() << setw(18) << R->get_node("n")->get_name() << setw(18) << R->get_current(R->get_node("p")) << setw(18) << R->get_voltage_across(t, R->get_node("p")) << setw(18) << R->check_grounded() << endl;
    cout << setw(12) << C->get_type() << setw(20) << C->get_conductance() << setw(16) << C->get_node("p")->get_name() << setw(18) << C->get_node("n")->get_name() << setw(18) << C->get_current(C->get_node("p")) << setw(18) << C->get_voltage_across(t, C->get_node("p")) << setw(18) << C->check_grounded() << endl;
    cout << setw(12) << L->get_type() << setw(20) << L->get_conductance() << setw(16) << L->get_node("p")->get_name() << setw(18) << L->get_node("n")->get_name() << setw(18) << L->get_current(L->get_node("p")) << setw(18) << L->get_voltage_across(t, L->get_node("p")) << setw(18) << L->check_grounded() << endl;
    cout << setw(12) << D->get_type() << setw(20) << D->get_conductance() << setw(16) << D->get_node("p")->get_name() << setw(18) << D->get_node("n")->get_name() << setw(18) << D->get_current(D->get_node("p")) << setw(18) << D->get_voltage_across(t, D->get_node("p")) << setw(18) << D->check_grounded() << endl;
};