#include "linear_components.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(node_test, node_get_name)
{
    Node *p = new Node("p");
    EXPECT_EQ(p->get_name(), "p");
}

TEST(node_test, node_add_component)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    p->add_component(L);
    EXPECT_EQ(p->get_components().size(), 1);
    // Node::add_component is not charged for filering out repeated components
    p->add_component(L);
    EXPECT_EQ(p->get_components().size(), 2);
}

TEST(node_test, node_get_components)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R1", p, n, 100);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    Component *L = new Inductor("L1", p, n, 1.0e-1);
    p->add_component(R);
    p->add_component(C);
    p->add_component(L);
    EXPECT_EQ(p->get_components().size(), 3);
}

TEST(node_test, node_get_conductance)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *R = new Resistor("R1", p, n, 100);
    Component *R2 = new Resistor("R2", p, n, 200);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    Component *L = new Inductor("L1", p, n, 1.0e-1);
    p->add_component(R);
    p->add_component(R2);
    p->add_component(C);
    p->add_component(L);
    EXPECT_DOUBLE_EQ(p->get_conductance(p), (1.0 / 100.0 + 1.0 / 200.0));
    EXPECT_DOUBLE_EQ(p->get_conductance(n), -(1.0 / 100.0 + 1.0 / 200.0));
}

TEST(node_test, node_get_current)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *I = new Current("I1", p, n, 2);
    Component *I2 = new Current("I2", p, n, 0.5);
    Component *R = new Resistor("R1", p, n, 100);
    Component *R2 = new Resistor("R2", p, n, 200);
    Component *C = new Capacitor("C1", p, n, 1.0e-6);
    Component *L = new Inductor("L1", p, n, 1.0e-1);
    Component *V = new Voltage("V1", p, n, 2);
    p->add_component(I);
    p->add_component(I2);
    p->add_component(R);
    p->add_component(R2);
    p->add_component(C);
    p->add_component(L);
    p->add_component(V);
    EXPECT_DOUBLE_EQ(p->get_current(), -2.5);
}

TEST(node_test, node_set_get_node_voltage)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    EXPECT_DOUBLE_EQ(p->get_node_voltage(), 1.0);
    p->set_node_voltage(11.5);
    EXPECT_DOUBLE_EQ(p->get_node_voltage(), 11.5);
}

TEST(node_test, node_compare_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    EXPECT_TRUE(compare_node(n, p));
    EXPECT_FALSE(compare_node(p, n));
}

TEST(node_test, node_get_or_create_node)
{
    Node *a = new Node("a");
    Node *b = new Node("b");
    Node *c = new Node("c");
    vector<Node *> nodes = {a, b, c};
    Node *d = get_or_create_node(nodes, "d");
    EXPECT_EQ(d->get_name(), "d");
    EXPECT_EQ(nodes.size(), 4);
    Node *d2 = get_or_create_node(nodes, "d");
    EXPECT_EQ(d, d2);
    EXPECT_EQ(nodes.size(), 4);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};