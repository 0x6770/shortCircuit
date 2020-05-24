#include "components_parser.hpp"

double parse_number(string input){
    //assert(!isalpha(input[0])); //question
    assert(!input.empty());

    double result = 0.0;
    string multiplier = "";

    stringstream ss;
    ss << input;
    ss >> result >> multiplier;

    if(multiplier == "p"){
        result *= 1.0e-12;
    }else if(multiplier == "n"){
        result *= 1.0e-9;
    }else if(multiplier == "u" or multiplier == "μ"){
        result *= 1.0e-6;
    }else if(multiplier == "m"){
        result *= 1.0e-3;
    }else if(multiplier == "k" or multiplier == "K"){
        result *= 1.0e3;
    }else if(multiplier == "Meg" or multiplier == "meg"){
        result *= 1.0e6;
    }else if(multiplier == "G" or multiplier == "g"){
        result *= 1.0e9;
    }else if(multiplier == ""){}
    else{
        cerr << "ERROR: invalid syntax, cannot parse" << input << endl;
        exit(1);
    }
    return result;
}

Component *parse_component(string input){
    stringstream ss;
    ss << input;
    Component *temp = new Component();
    Node *t0 = new Node();
    Node *t1 = new Node();
    string name, pin1, pin2, type, value;
    ss >> name >> pin1 >> pin2 >> value;
    double real_value = parse_number(value);

    if(name[0] == 'V'){
        type = "voltage_source";
    }else if(name[0] == 'I'){
        type = "current_source";
    }else if(name[0] == 'R'){
        type = "resistor";
    }else if(name[0] == 'L'){
        type = "inductor";
    }else if(name[0] == 'C'){
        type = "capacitor";
    }else{
        cerr << "unrecognised type" << name << endl;
        exit(1);
    }

    t0->set_name(pin1);
    t1->set_name(pin2);
    temp->set_comp(type,real_value,t0,t1);
    return temp;
}

vector<double> generate_instants(string directive){
    vector<double> result;
    istringstream iss(directive);
    string tag, start, end, placeholder, step;

    if(!(iss >> tag >> start >> end >> placeholder >> step)){
        cerr << "unknown format for component";
        exit(1);
    }
    iss >> tag >> start >> end >> placeholder >> step;

    end.pop_back();
    step.pop_back();

    double real_end = parse_number(end);
    double real_step = parse_number(step);

    for(double i = 0; i <= real_end; i += real_step){
        result.push_back(i);
    }
    return result;
}

bool is_comment(string input){
    if(input[0] == '*'){
        return true;
    }
    return false;
}

bool is_directive(string input){
    if(input.substr(0,5) == ".tran"){
        return true;
    }
    return false;
}

bool is_end(string input){
    if(input.substr(0,4) == ".end"){
        return true;
    }
    return false;
}

bool is_component(string input){
    if(is_end(input) or is_directive(input) or is_comment(input)){
        return false;
    }
    return true;
}