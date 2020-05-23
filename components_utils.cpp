#include "components_utils.hpp"
#include "components.hpp"
#include "circuit.hpp"
#include <map>
#include <utility>

vector<string> remove_duplicates(vector<string> &nums)
{
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] == nums[i + 1])
        {
            nums.erase(nums.begin() + i);
            return remove_duplicates(nums);
        }
    }
    return nums;
}

vector<string> find_nodes(vector<Component *> circuit)
{
    vector<string> nodes;
    for (auto it = circuit.begin(); it != circuit.end(); it++)
    {
        nodes.push_back((*it)->getPin(1));
        nodes.push_back((*it)->getPin(2));
    }
    sort(nodes.begin(), nodes.end());

    return remove_duplicates(nodes);
}

int demension(vector<string> nodes){
    return nodes.size()-1;
}

bool is_powersource(Component* component){
    if(component->get_type() == "power_source"){
        return true;
    }
    return false;
}

bool is_passive(Component *component){
    if(component->get_type() == "inductor" or component->get_type() == "capacitor"){
        return true;
    }
    return false;
}

bool is_time_independent(Component *component){
    if(component->get_type() == "resistor" or component->get_type() == "power_source_independent"){
        return true;
    }
    return false;
}