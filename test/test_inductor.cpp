#include "linear_components.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(inductor_test, inductor_get_name)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_name(), "L1");
}

TEST(inductor_test, inductor_get_type)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_type(), "L");
}

TEST(inductor_test, inductor_get_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_node("p"), p);
    EXPECT_EQ(L->get_node("n"), n);
}

TEST(inductor_test, inductor_contain_node)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_TRUE(L->contain_node("p"));
    EXPECT_FALSE(L->contain_node("c"));
}

TEST(inductor_test, inductor_get_property)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_property(), 0.1);
}

TEST(inductor_test, inductor_get_conductance)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_conductance(), 0.0);
}

TEST(inductor_test, inductor_get_current)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_current(p), 0.0);
    EXPECT_EQ(L->get_current(n), 0.0);
}

TEST(inductor_test, inductor_get_current_through)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_current_through(p), 0.0);
    EXPECT_EQ(L->get_current_through(n), 0.0);
}

TEST(inductor_test, inductor_get_voltage_across)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *L = new Inductor("L1", p, n, 0.1);
    EXPECT_EQ(L->get_voltage_across(1.1, p), 0.0);
    EXPECT_EQ(L->get_voltage_across(1.1, n), 0.0);
}

TEST(inductor_test, inductor_set_current_through)
{
    Node *p = new Node("p");
    Node *n = new Node("n");
    p->set_node_voltage(1.0);
    n->set_node_voltage(11.0);
    Component *L = new Inductor("L1", p, n, 0.1);
    L->set_current_through(0.25);
    EXPECT_EQ(L->get_current_through(p), 0.25);
}

TEST(inductor_test, inductor_set_voltage_across)
{
    // _voltage_across of inductor cannot be set
    Node *p = new Node("p");
    Node *n = new Node("n");
    Component *L = new Inductor("L1", p, n, 0.1);
    L->set_voltage_across(0.25);
    EXPECT_EQ(L->get_voltage_across(0.1, p), 0.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};