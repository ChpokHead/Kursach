#pragma once

#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include "Token.h"
using namespace std;



typedef pair<Statement, Output> Result; // ���� (����� ��������� & �������� ������)
typedef pair<Statement, char> Input; // ��������� ���� (������� ��������� & ������� ������)
typedef pair<Input, Result> Item; //������� ������� ���������
extern map<Input, Result> M; // ������� ��������� ��
extern map<string, Output> Keywords; //������� ��������� ����

//�����-���������� ������ ������������ �����������
class LexError {
public:
    inline LexError(string str)
    {
        cout << "������ ������������ �����������: " << str << endl;
    }
};


//����� ������������ �����������
class LexAnalyser {
public:
    LexAnalyser(const char* fname); //�����������
    ~LexAnalyser(); //����������
    bool getToken(Token& token); //������� ��������� ��������� �������
    vector<Token>* getTokenList();
private:
    ifstream _file; //�������� ����� ��� ������ c������� ������� �������
    bool isLast, isStrCon;
    vector<Token> tokenList;
};