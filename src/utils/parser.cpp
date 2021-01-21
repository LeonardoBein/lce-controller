#include "../../include/utils/parser.h"

float Parser::Float(char* string){
    return std::stof(string);
}
int Parser::Interger(char* string){
    return std::stod(string);
}