#include "components_utils.hpp"

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
