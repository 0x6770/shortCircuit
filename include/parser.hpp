#ifndef parser_hpp
#define parser_hpp

#include "components.hpp"

/**
 * @brief parser text based number to double
 * 
 * @param input a text based number likes 1p, 1n, 1μ, 1m, 1, 1k, 1Meg
 * @return double result number
 */
double
parse_number(string input);

/**
 * @brief create component from given string
 * 
 * @param input a string which defines a component
 * @return Component* a pointer to Component
 */
Component *parse_component(string input);

/**
 * @brief generate instants from given directive
 * 
 * @param directive .tran 0 <stop time> 0 <timestep>
 * @return vector<double> vector containing instants (0, <stop time>, <timestep>)
 */
vector<double> generate_instants(string directive);

/**
 * @brief determine whether a given string is comment or not
 * 
 * @param input the given string
 * @return true if input is comment 
 * @return false if input is not comment 
 */
bool is_comment(string input);

/**
 * @brief determine whether a given string is directive or not
 * 
 * @param input the given string
 * @return true if input is directive 
 * @return false if input is not directive 
 */
bool is_directive(string input);

/**
 * @brief determine whether a given directive is .tran or not
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool is_tran(string directive);

/**
 * @brief determine whether a given string is end or not
 * 
 * @param input the given string
 * @return true if input is end 
 * @return false if input is not end 
 */
bool is_end(string input);

/**
 * @brief determine whether a given string is component or not
 * 
 * @param input the given string
 * @return true if input is component 
 * @return false if input is not component 
 */
bool is_component(string input);

#endif // parser_hpp