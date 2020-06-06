#include "linear_components.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(resistor_test, resistor_get_name)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R1", p, n, 100);
    EXPECT_EQ(R->get_name(), "R1");
}

TEST(resistor_test, resistor_get_type)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100);
    EXPECT_EQ(R->get_type(), "R");
}

TEST(resistor_test, resistor_get_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_node("p"), p);
    EXPECT_EQ(R->get_node("n"), n);
}

TEST(resistor_test, resistor_contain_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_TRUE(R->contain_node("p"));
    EXPECT_FALSE(R->contain_node("c"));
}

TEST(resistor_test, resistor_get_property)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_property(), 100.0);
}

TEST(resistor_test, resistor_get_conductance)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_conductance(), 1.0 / 100.0);
}

TEST(resistor_test, resistor_get_current)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_current(p), 0.0);
    EXPECT_EQ(R->get_current(n), 0.0);
}

TEST(resistor_test, resistor_get_current_through)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_current_through(p), -0.1);
    EXPECT_EQ(R->get_current_through(n), 0.1);
}

TEST(resistor_test, resistor_get_voltage_across)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    EXPECT_EQ(R->get_voltage_across(1.1, p), 0.0);
    EXPECT_EQ(R->get_voltage_across(1.1, n), 0.0);
}

TEST(resistor_test, resistor_set_current_through)
{
    // set_current_through() should not work for resistor
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *R = new Resistor("R", p, n, 100.0);
    R->set_current_through(0.25);
    EXPECT_NE(R->get_current_through(p), 0.25);
    EXPECT_EQ(R->get_current_through(p), -0.1);
}

TEST(resistor_test, resistor_set_voltage_across)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R", p, n, 100.0);
    R->set_voltage_across(0.25);
    EXPECT_EQ(R->get_voltage_across(0.1, p), 0.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    // test instantiation for every kind of component
    // cout << "🧪 Testing instantiation" << endl;
    // Component *V1 = new Voltage("V1", a, b, A * 2);
    // Component *V2 = new Voltage("V2", a, c, A);
    // Component *V_sin1 = new SINE_Voltage("V_sin1", b, e, bias * 2, A, f);
    // Component *V_sin2 = new SINE_Voltage("V_sin2", a, e, bias, A, f);
    // Component *R = new Resistor("R", a, b, f);
    // Component *C = new Capacitor("C", d, e, f);
    // Component *L = new Inductor("L", a, d, f);
    // Component *D = new Diode_D("D", a, d);

    return RUN_ALL_TESTS();
};