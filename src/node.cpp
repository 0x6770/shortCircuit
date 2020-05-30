#include "node.hpp"

double Node::get_voltage()
{
    return _voltage;
}

double Node::get_current()
{
    return _current;
}

void Node::add_branches(Component *branch)
{
    _branches.push_back(branch);
    if (branch->get_type() == "I")
    {
        _is_connected_current = true;
    }
    if (branch->get_type() == "V")
    {
        _is_connected_voltage = true;
    }
}

vector<Component *> Node::get_branches()
{
    return _branches;
}

string Node::get_name()
{
    return _name;
}

int Node::get_index()
{
    return _index;
}

bool Node::operator==(Node *a)
{
    if (_name == a->get_name())
        return true;
    return false;
}

// bool Node::is_super_node()
// {
//     if (connected_voltage)
//     {
//         for (int i = 0; i < _branches.size(); i++)
//         {
//             if (_branches[i]->is_grounded() && _branches[i]->is_voltage())
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
//     return false;
// }

// bool Node::is_connected_current()
// {
//     for (int i = 0; i < _branches.size(); i++)
//     {
//         if (_branches[i]->is_current())
//             return true;
//     }
//     return false;
// }

bool Node::get_is_connected_voltage()
{
    return _is_connected_voltage;
}

//useful when setting the Ax = b, b_column matrix
void Node::set_current()
{
    if (_is_connected_current && !(_is_connected_voltage))
    {
        for (auto branch = _branches.begin(); branch != _branches.end(); branch++)
        {
            if ((*branch)->get_type() == "I")
            {
                if ((*branch)->get_node("n") == _name)
                {
                    _current = _current + (*branch)->get_property();
                }
                else if ((*branch)->get_node("p") == _name)
                {
                    _current = _current - (*branch)->get_property();
                }
            }
        }
    }
}
