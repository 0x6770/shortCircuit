#include "parser.hpp"

double parse_number(string input){
    //assert(!isalpha(input[0])); //question
    //assert(!input.empty());

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
    string name, pin1, pin2, type, value;
    ss >> name >> pin1 >> pin2 >> value;
    double real_value = parse_number(value);
    Component * single_component = new Component(name,pin1,pin2,real_value);
    return single_component;
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
    if(input[0] == '*' or input[0] == '.')
        return false;
    return true;
}
