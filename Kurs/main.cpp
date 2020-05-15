#include "LexAnalyser.h"
#include "SyntaxAnalyser.h"
#include "ErrorHandler.h"

int main (int argc, char* argv[])
{
    Token token;
    
    try
    {
        LexAnalyser lex("/Users/danilihsanov/CLionProjects/Kursach/Kurs/in.txt");

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