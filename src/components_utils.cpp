#include "components_utils.hpp"

// vector<Node *> remove_duplicates(vector<Node *> &nums)
// {
//     for (int i = 0; i < nums.size() - 1; i++)
//     {
//         if (nums[i] == nums[i + 1])
//         {
//             nums.erase(nums.begin() + i);
//             return remove_duplicates(nums);
//         }
//     }
//     return nums;
// }

// vector<Node *> find_nodes(const vector<Component *> &circuit)
// {
//     vector<Node *> nodes;
//     for (auto it = circuit.begin(); it != circuit.end(); it++)
//     {
//         nodes.push_back((*it)->get_node("p"));
//         nodes.push_back((*it)->get_node("n"));
//     }
//     sort(nodes.begin(), nodes.end());
//     auto it = find(nodes.begin(), nodes.end(), "0");
//     if (it == nodes.end())
//     {
//         cerr << endl;
//         cerr << "🚧 ERROR: circuit is not grounded. " << endl;
//         cerr << endl;
//     }

//     return remove_duplicates(nodes);
// }

vector<Node *> remove_ground(const vector<Node *> &nodes)
{
    vector<Node *> res_nodes = nodes;
    res_nodes.erase(res_nodes.begin());
    return res_nodes;
}

int demension(vector<string> nodes)
{
    return nodes.size() - 1;
}

bool is_powersource(Component *component)
{
    if (component->get_type() == "power_source")
    {
        return true;
    }
    return false;
}

//map<string,string> nodes;
pair<string, string> nodes;

complex<double> find_conductance(Node *node1, Node *node2, vector<Component *> circuit, double f, double t)
{
    vector<Component *> temp;
    if (node1 == node2)
    {
        for (int i = 0; i < circuit.size(); i++)
        {
            if (!is_powersource(circuit[i]))
            {
                if (circuit[i]->get_node("p") == node1 or circuit[i]->get_node("n") == node2)
                {
                    temp.push_back(circuit[i]);
                }
            }
        }
        complex<double> result = complex<double>(0.0, 0.0);
        for (int i = 0; i < temp.size(); i++)
        {
            result = result + temp[i]->get_conductance(f);
        }
        return result;
    }
}