#ifndef components_utils_hpp
#define components_utils_hpp

#include <algorithm>
#include <iterator>
#include "components.hpp"

vector<Node *> remove_duplicates(vector<Node *> &nums);

vector<Node *> find_nodes(const vector<Component *> &circuit);

vector<Node *> remove_ground(const vector<Node *> &circuit);

#endif