#include "SyntaxAnalyser.h"

SyntaxAnalyser::SyntaxAnalyser(vector<Token> *tokens): it(0)
{
     tokenList = tokens;
     optimization();
}

// ����������� - �������� ������ BSLASH � �������
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

// ������� ����� � �������� ���������� �������������� ������
void SyntaxAnalyser :: analyse() {
    if (on_P())
        cout << "\n�������������� ������ ������� �������!" << endl;
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

// ��������� �� package main � ������ ��������� 
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

// ��������� �� import()
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