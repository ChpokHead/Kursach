#include "Token.h"

// ¬ывод типов токенов
void Token::printToken()
{
    switch (_type)
    {
        case IDENT:
            cout << "“ип: IDENT" << endl;
            break;
        case DEC:
            cout << "“ип: DEC" << endl;
            break;
        case STR:
            cout << "“ип: STR" << endl;
            break;
        case COMMA:
            cout << "“ип: COMMA" << endl;
            break;
        case PLUS:
            cout << "“ип: PLUS" << endl;
            break;
        case MINUS:
            cout << "“ип: MINUS" << endl;
            break;
        case MUL:
            cout << "“ип: MUL" << endl;
            break;
        case DIV:
            cout << "“ип: DIV" << endl;
            break;
        case LBR:
            cout << "“ип: LBR" << endl;
            break;
        case RBR:
            cout << "“ип: RBR" << endl;
            break;
        case LFBR:
            cout << "“ип: LFBR" << endl;
            break;
        case RFBR:
            cout << "“ип: RFBR" << endl;
            break;
        case COL:
            cout << "“ип: COL" << endl;
            break;
        case SCOL:
            cout << "“ип: SCOL" << endl;
            break;
        case MTHAN:
            cout << "“ип: MTHAN" << endl;
            break;
        case LTHAN:
            cout << "“ип: LTHAN" << endl;
            break;
        case EQUAL:
            cout << "“ип: EQUAL" << endl;
            break;
        case DOT:
            cout << "“ип: DOT" << endl;
            break;
        case EXC:
            cout << "“ип: EXC" << endl;
            break;
        case PACKAGE:
            cout << "“ип: PACKAGE" << endl;
            break;
        case BSLASH:
            cout << "“ип: BSLASH" << endl;
            break;
        case FUNC:
            cout << "“ип: FUNC" << endl;
            break;
        case VAR:
            cout << "“ип: VAR" << endl;
            break;
        case FLOAT64:
            cout << "“ип: FLOAT64" << endl;
            break;
        case INT:
            cout << "“ип: INT" << endl;
            break;
        case ASS:
            cout << "“ип: ASS" << endl;
            break;
        case RETURN:
            cout << "“ип: RETURN" << endl;
            break;
        case WHILE:
            cout << "“ип: WHILE" << endl;
            break;
        case IMPORT:
            cout << "“ип: IMPORT" << endl;
            break;
        case IF:
            cout << "“ип: IF" << endl;
            break;
    }
}
