#include "LexAnalyser.h"
#include "SyntaxAnalyser.h"
#include "ErrorHandler.h"

int main (int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    Token token;
    
    try
    {
        LexAnalyser lex("in.txt");

        while (lex.getToken(token))
        {
            cout << "Лексемма: '" << token.getValue() << "' --- "; 
            token.printToken();
        }

        SyntaxAnalyser syn(lex.getTokenList());
        syn.analyse();
    }
    catch (string str)
    {
        cout << str << endl;
        exit(1);
    }

    return 0;
}