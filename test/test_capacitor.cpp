#include "linear_components.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(capacitor_test, capacitor_get_name)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_name(), "C1");
}

TEST(capacitor_test, capacitor_get_type)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_type(), "C");
}

TEST(capacitor_test, capacitor_get_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_node("p"), p);
    EXPECT_EQ(C->get_node("n"), n);
}

TEST(capacitor_test, capacitor_contain_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_TRUE(C->contain_node("p"));
    EXPECT_FALSE(C->contain_node("c"));
}

TEST(capacitor_test, capacitor_get_property)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_property(), 1.0e-6);
}

TEST(capacitor_test, capacitor_get_conductance)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_conductance(), 0.0);
}

TEST(capacitor_test, capacitor_get_current)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_current(p), 0.0);
    EXPECT_EQ(C->get_current(n), 0.0);
}

TEST(capacitor_test, capacitor_get_current_through)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_current_through(p), 0.0);
    EXPECT_EQ(C->get_current_through(n), 0.0);
}

TEST(capacitor_test, capacitor_get_voltage_across)
{
    // _voltage_across of capacitor is only changed by set_voltage_across()
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    EXPECT_EQ(C->get_voltage_across(1.1, p), 0.0);
    EXPECT_EQ(C->get_voltage_across(1.1, n), 0.0);
}

TEST(capacitor_test, capacitor_set_current_through)
{
    // set_current_through() should not work for resistor
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    C->set_current_through(0.25);
    EXPECT_EQ(C->get_current_through(p), 0.25);
}

TEST(capacitor_test, capacitor_set_voltage_across)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    C->set_voltage_across(0.25);
    EXPECT_EQ(C->get_voltage_across(0.1, p), 0.25);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};