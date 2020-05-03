//Класс "Лексема"
#pragma once
#include "Enums.h"
#include <string>
#include <iostream>
using namespace std;

class Token {
private:
    string _value; // Строковое значение
    TokenType _type; //Тип лексемы
public:
    string getValue() { return this->_value; }
    TokenType getType() { return this->_type; }
    void setValue(string v) { this->_value = v; }
    void setType(TokenType t) { this->_type = t; }
    void printToken();
};
