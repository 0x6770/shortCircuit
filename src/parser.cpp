#include "parser.hpp"

double parse_number(string input)
{
    // 1p, 1n, 1μ, 1m, 1, 1k, 1Meg
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
    else if (multiplier == "μ" || multiplier == "u")
    {
        result *= 1.0e-6;
    }
    else if (multiplier == "m")
    {
        result *= 1.0e-3;
    }
    else if (multiplier == "k" || multiplier == "K")
    {
        result *= 1.0e3;
    }
    else if (multiplier == "meg" || multiplier == "Meg")
    {
        result *= 1.0e6;
    }
    else if (multiplier == "g" || multiplier == "G")
    {
        result *= 1.0e6;
    }
    else if (multiplier == "t" || multiplier == "T")
    {
        result *= 1.0e9;
    }
    else if (multiplier == "")
    {
    }
    else
    {
        cerr << "ERROR: invalid syntax, cannot parse " << input << endl;
        exit(0);
    }

    return result;
};

Component *parse_component(string input)
{
    stringstream ss;
    ss << input;
    string name, pin1, pin2, resistance, capacitance, inductance, voltage_type;
    double real_resistance, real_capacitance, real_inductance;
    if (input[0] == 'R')
    {
        ss >> name >> pin1 >> pin2 >> resistance;
        real_resistance = parse_number(resistance);
        // cout << "type: " << input[0] << "\tname: " << name << "\tpin1: " << pin1 << "\tpin2: " << pin2 << "\tresistance: " << real_resistance << endl;
        Component *result = new Resistor(pin1, pin2, real_resistance);
        return result;
    }
    else if (input[0] == 'L')
    {
        ss >> name >> pin1 >> pin2 >> inductance;
        real_inductance = parse_number(inductance);
        // cout << "type: " << input[0] << "\tname: " << name << "\tpin1: " << pin1 << "\tpin2: " << pin2 << "\tinductance: " << real_inductance << endl;
        Component *result = new Inductor(pin1, pin2, real_inductance);
        return result;
    }
    else if (input[0] == 'C')
    {
        ss >> name >> pin1 >> pin2 >> capacitance;
        real_capacitance = parse_number(capacitance);
        // cout << "type: " << input[0] << "\tname: " << name << "\tpin1: " << pin1 << "\tpin2: " << pin2 << "\tcapacitance: " << real_capacitance << endl;
        Component *result = new Capacitor(pin1, pin2, real_capacitance);
        return result;
    }
};

vector<double> generate_instants(string directive)
{
    vector<double> result;
    istringstream iss(directive);
    string tag, start, end, placeholder, step;
    if (!(iss >> tag >> start >> end >> placeholder >> step))
    {
        cerr << "unknown format for component" << endl;
        exit(1);
    }
    iss >> tag >> start >> end >> placeholder >> step;
    // cout << "start: " << start << "\tend: " << end << "\tstep: " << step << endl;
    end.pop_back();  // delete the "s" at the end
    step.pop_back(); // delete the "s" at the end
    double real_end = parse_number(end);
    double real_step = parse_number(step);
    // cout << "start: " << start << "\tend: " << real_end << "\tstep: " << real_step << endl;
    for (double i = 0; i <= real_end; i += real_step)
    {
        result.push_back(i);
    }
    return result;
};

bool is_comment(string input)
{
    if (input[0] == '*')
    {
        return true;
    }
    return false;
};

bool is_directive(string input)
{
    if (input.substr(0, 5) == ".tran")
    {
        return true;
    }
    return false;
};

bool is_end(string input)
{
    if (input.substr(0, 4) == ".end")
    {
        return true;
    }
    return false;
};

bool is_component(string input)
{
    if (is_end(input) | is_directive(input) | is_comment(input))
    {
        return false;
    }
    return true;
};