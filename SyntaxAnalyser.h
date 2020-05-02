#include <vector>
#include <iostream>
#include "Token.h"
using namespace std;

class SyntaxAnalyser {
private:
    vector<Token> *tokenList;
    //vector<Token>::iterator it;
    int it;
public:
    SyntaxAnalyser(vector<Token> *tokens);
    void analyse();
    bool on_P();
};
