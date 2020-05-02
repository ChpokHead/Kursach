//Users/danilihsanov/CLionProjects/untitled3/in.txt
#include "LexAnalyser.h"
#include "SyntaxAnalyser.h"

int main(void)
{
    setlocale(LC_ALL, "Russian");

    Token token;
    
    try
    {
        LexAnalyser lex("/Users/danilihsanov/CLionProjects/untitled3/in.txt");
        SyntaxAnalyser syn(lex.getTokenList());

        while (lex.getToken(token))
        {
            cout << "Лексемма: '" << token.getValue() << "' --- "; token.printToken();
        }
        syn.analyse();
    }
    catch (LexError err)
    {
        exit(1);
    }

    return 0;
}