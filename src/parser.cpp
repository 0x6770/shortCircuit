#include "parser.hpp"

//* tested and Done
double parse_number(string input)
{
    // 1p, 1n, 1μ, 1m, 1, 1k, 1Meg
    // cerr << "paring number: " << input << endl;
    assert(!isalpha(input[0])); // input should not be started by alphabet
    assert(!input.empty());     // input should not be empty

    double result = 0.0;
    string multiplier = "";

    stringstream ss;
    ss << input;
    ss >> result >> multiplier;

    if (multiplier == "p")
    {
        result *= 1.0e-12;
    }
    else if (multiplier == "n")
    {
        result *= 1.0e-9;
    }
    else if (multiplier == "\u03bc" or multiplier == "\u00b5" or multiplier == "u")
    {
        result *= 1.0e-6;
    }
    else if (multiplier == "m")
    {
        result *= 1.0e-3;
    }
    else if (multiplier == "k" or multiplier == "K")
    {
        result *= 1.0e3;
    }
    else if (multiplier == "meg" or multiplier == "Meg")
    {
        result *= 1.0e6;
    }
    else if (multiplier == "g" or multiplier == "G")
    {
        result *= 1.0e6;
    }
    else if (multiplier == "t" or multiplier == "T")
    {
        result *= 1.0e9;
    }
    else if (multiplier == "")
    {
    }
    else
    {
        cerr << endl;
        cerr << "🚧 ERROR: invalid syntax, cannot parse " << input << endl;
        cerr << endl;
        exit(1);
    }

    return result;
};

//* tested for R,C,L
Component *parse_component(string input, vector<Node *> &nodes)
{
    stringstream ss;
    ss << input;
    string name, node_p, node_n, property, model_name, voltage_type, bias, amplitude, frequency, buffer1, buffer2, buffer3;
    double real_property, real_bias, real_amplitude, real_frequency;
    if (input[0] == 'R')
    {
        ss >> name >> node_p >> node_n >> property;
        real_property = parse_number(property);
        Node *real_node_p = get_or_create_node(nodes, node_p);
        Node *real_node_n = get_or_create_node(nodes, node_n);
        // cout << "type: " << input[0] << "\tname: " << name << "\tnode1: " << node1 << "\tnode2: " << node2 << "\tresistance: " << real_resistance << endl;
        Component *result = new Resistor(name, real_node_p, real_node_n, real_property);
        real_node_p->add_component(result);
        real_node_n->add_component(result);
        return result;
    }
    else if (input[0] == 'L')
    {
        ss >> name >> node_p >> node_n >> property;
        real_property = parse_number(property);
        Node *real_node_p = get_or_create_node(nodes, node_p);
        Node *real_node_n = get_or_create_node(nodes, node_n);
        // cout << "type: " << input[0] << "\tname: " << name << "\tnode1: " << node1 << "\tnode2: " << node2 << "\tinductance: " << real_inductance << endl;
        Component *result = new Inductor(name, real_node_p, real_node_n, real_property);
        real_node_p->add_component(result);
        real_node_n->add_component(result);
        return result;
    }
    else if (input[0] == 'C')
    {
        ss >> name >> node_p >> node_n >> property;
        real_property = parse_number(property);
        Node *real_node_p = get_or_create_node(nodes, node_p);
        Node *real_node_n = get_or_create_node(nodes, node_n);
        // cout << "type: " << input[0] << "\tname: " << name << "\tnode1: " << node1 << "\tnode2: " << node2 << "\tcapacitance: " << real_capacitance << endl;
        Component *result = new Capacitor(name, real_node_p, real_node_n, real_property);
        real_node_p->add_component(result);
        real_node_n->add_component(result);
        return result;
    }
    else if (input[0] == 'D')
    {
        ss >> name >> node_p >> node_n >> model_name;
        Node *real_node_p = get_or_create_node(nodes, node_p);
        Node *real_node_n = get_or_create_node(nodes, node_n);
        // cout << "type: " << input[0] << "\tname: " << name << "\tnode1: " << node1 << "\tnode2: " << node2 << "\tmodal_name: " << modal_name << endl;
        Component *result = nullptr;
        if (model_name == "D")
        {
            Component *result = new Diode_D(name, real_node_p, real_node_n);
            real_node_p->add_component(result);
            real_node_n->add_component(result);
            return result;
        }
        else
        {
            cerr << endl;
            cerr << "🚧  ERROR: unsupported modal_name for Diode " << model_name << endl;
            cerr << endl;
            exit(1);
        }
    }
    else if (input[0] == 'V')
    {
        if (ss >> name >> node_p >> node_n >> buffer1 >> buffer2 >> buffer3)
        {
            // cerr << "SINE " << name << " " << node_p << " " << node_n << " " << buffer1 << " " << buffer2 << " " << buffer3 << endl;
            real_bias = parse_number(buffer1.substr(5));
            real_amplitude = parse_number(buffer2);
            // cout << "buffer3.substr(0, (buffer3.size() - 1))" << buffer3.substr(0, (buffer3.size() - 1)) << endl;
            real_frequency = parse_number(buffer3.substr(0, (buffer3.size() - 1)));
            Node *real_node_p = get_or_create_node(nodes, node_p);
            Node *real_node_n = get_or_create_node(nodes, node_n);
            Component *result = new SINE_Voltage(name, real_node_p, real_node_n, real_bias, real_amplitude, real_frequency);
            real_node_p->add_component(result);
            real_node_n->add_component(result);
            return result;
        }
        else
        {
            // cerr << "DC " << name << " " << node_p << " " << node_n << " " << buffer1 << endl;
            real_amplitude = parse_number(buffer1);
            Node *real_node_p = get_or_create_node(nodes, node_p);
            Node *real_node_n = get_or_create_node(nodes, node_n);
            Component *result = new Voltage(name, real_node_p, real_node_n, real_amplitude);
            real_node_p->add_component(result);
            real_node_n->add_component(result);
            return result;
        }
    }
    else if (input[0] == 'I')
    {
        ss >> name >> node_p >> node_n >> amplitude;
        real_amplitude = parse_number(amplitude);
        Node *real_node_p = get_or_create_node(nodes, node_p);
        Node *real_node_n = get_or_create_node(nodes, node_n);
        // cout << "type: " << input[0] << "\tname: " << name << "\tnode1: " << node1 << "\tnode2: " << node2 << "\tcapacitance: " << real_capacitance << endl;
        Component *result = new Current(name, real_node_p, real_node_n, real_amplitude);
        real_node_p->add_component(result);
        real_node_n->add_component(result);
        return result;
    }
    cerr << endl;
    cerr << "🚧  ERROR: unsupported component type" << endl;
    cerr << endl;
    exit(1);
};

vector<double> parse_tran(string tran)
{
    istringstream iss(tran);
    string tag, start, end, placeholder, step;
    if (!(iss >> tag >> start >> end >> placeholder >> step))
    {
        cerr << "unknown format for component" << endl;
        cerr << " => " << tran << endl;
        exit(1);
    }
    double real_end = parse_number(end);
    double real_step = parse_number(step);
    vector<double> result = {real_step, real_end};
    return result;
}

//* tested and Done
bool is_comment(string input)
{
    if (input[0] == '*')
    {
        return true;
    }
    return false;
};

//* tested and Done
bool is_directive(string input)
{
    if (input[0] == '.')
    {
        return true;
    }
    return false;
};

//* tested and Done
bool is_tran(string directive)
{
    if (directive.substr(0, 5) == ".tran")
    {
        return true;
    }
    return false;
};

//* tested and Done
bool is_end(string input)
{
    if (input.substr(0, 4) == ".end")
    {
        return true;
    }
    return false;
};

//* tested and Done
bool is_component(string input)
{
    if (is_end(input) | is_directive(input) | is_comment(input))
    {
        return false;
    }
    return true;
};