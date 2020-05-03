#include "SyntaxAnalyser.h"

SyntaxAnalyser::SyntaxAnalyser(vector<Token> *tokens): it(0)
{
     tokenList = tokens;
     optimization();
}

// Оптимизация - удаление лишних BSLASH в векторе
void SyntaxAnalyser::optimization()
{
    bool flag = false;

    for (auto it = tokenList->begin(); it != tokenList->end();)
    {
        if (it->getType() == BSLASH) {
            flag = true;
        }

        it++;

        while (flag) 
        {
            if (it->getType() == BSLASH) 
                it = tokenList->erase(it);
            else 
                flag = false;        
        }
    }
}

// Главный метод с которого начинается синтаксический анализ
void SyntaxAnalyser :: analyse() {
    if (on_P())
        cout << "\nСинтаксический анализ пройден успешно!" << endl;
    else
        throw error.syntaxError("");
}

bool SyntaxAnalyser::on_P() {
    if (!on_Package())
        return false;
    if (!on_Import())
        return false;

    return true;
}

// Проверяем на package main в начале программы 
bool SyntaxAnalyser::on_Package() {
    if (tokenList->at(it).getType() != PACKAGE) it++;
 

    if (tokenList->at(it++).getType() != PACKAGE)
        return false;

    if (tokenList->at(it++).getType() != IDENT)
        return false;

    if (tokenList->at(it++).getType() != BSLASH)
        return false;

    return true;
}

// Проверяем на import()
bool SyntaxAnalyser::on_Import() {
    if (tokenList->at(it++).getType() != IMPORT)
        return false;
    if (tokenList->at(it++).getType() != LBR)
        return false;
    
    while (tokenList->at(it).getType() == STR || tokenList->at(it).getType() == BSLASH) {
        it++;
    }

    if (tokenList->at(it++).getType() != RBR)
        return false;

    return true;
}

// IDENT, DEC, STR, COMMA, PLUS, MINUS, MUL, DIV, LBR, RBR, LFBR, RFBR, COL, SCOL, MTHAN, 
// LTHAN, EQUAL, DOT, EXC, PACKAGE, BSLASH, FUNC, VAR, FLOAT64, INT, ASS, RETURN, WHILE, IMPORT, IF