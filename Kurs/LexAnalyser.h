#pragma once

#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include "Token.h"
#include "ErrorHandler.h"

using namespace std;

typedef pair<Statement, Output> Result; // Пара (Новое Состояние & Выходной сигнал)
typedef pair<Statement, char> Input; // Составной ключ (Текущее Состояние & Входной символ)
typedef pair<Input, Result> Item; //Элемент таблицы переходов
extern map<Input, Result> M; // Таблица переходов КА
extern map<string, Output> Keywords; //Таблица служебных слов

//Класс лексического анализатора
class LexAnalyser {
public:
    LexAnalyser(const char* fname); //Конструктор
    ~LexAnalyser(); //Деструктор
    bool getToken(Token& token); //Функция получения очередной лексемы
    vector<Token>& getTokenList() { return tokenList; };

private:
    ifstream _file; //Файловый поток для чтения cимволов входной цепочки
    bool isLast, isStrCon;
    vector<Token> tokenList;
    ErrorHandler error;
};