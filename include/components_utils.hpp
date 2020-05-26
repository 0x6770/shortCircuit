#ifndef components_utils_hpp
#define components_utils_hpp

#include <algorithm>
#include <iterator>
#include "components.hpp"

vector<string> remove_duplicates(vector<string> &nums);

vector<string> find_nodes(const vector<Component *> &circuit);

vector<string> remove_ground(const vector<string> &circuit);

#endif