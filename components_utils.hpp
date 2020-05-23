#ifndef components_utils_hpp
#define components_utils_hpp

#include <algorithm>
#include <iterator>
#include "components.hpp"

vector<string> remove_duplicates(vector<string> &nums);
vector<string> find_nodes(vector<Component *> circuit);
bool is_time_independent(Component *component);
bool is_passive(Component *component);
bool is_powersource(Component* component);
int demension(vector<string> nodes);




#endif