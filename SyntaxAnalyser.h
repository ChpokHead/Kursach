#include <vector>
#include <iostream>
#include "Token.h"
#include "ErrorHandler.h"

using namespace std;

class SyntaxAnalyser {
private:
    vector<Token>* tokenList;
    int it;
    ErrorHandler error;

    void optimization();
    bool on_P();
    bool on_Package();
    bool on_Import();

public:
    SyntaxAnalyser(vector<Token> *tokens);
    void analyse();
};
