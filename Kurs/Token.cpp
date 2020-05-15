#include "Token.h"

// Вывод типов токенов
void Token::printToken()
{
    switch (_type)
    {
        case IDENT:
            cout << "Тип: IDENT" << endl;
            break;
        case DEC:
            cout << "Тип: DEC" << endl;
            break;
        case STR:
            cout << "Тип: STR" << endl;
            break;
        case COMMA:
            cout << "Тип: COMMA" << endl;
            break;
        case PLUS:
            cout << "Тип: PLUS" << endl;
            break;
        case MINUS:
            cout << "Тип: MINUS" << endl;
            break;
        case MUL:
            cout << "Тип: MUL" << endl;
            break;
        case DIV:
            cout << "Тип: DIV" << endl;
            break;
        case LBR:
            cout << "Тип: LBR" << endl;
            break;
        case RBR:
            cout << "Тип: RBR" << endl;
            break;
        case LFBR:
            cout << "Тип: LFBR" << endl;
            break;
        case RFBR:
            cout << "Тип: RFBR" << endl;
            break;
        case COL:
            cout << "Тип: COL" << endl;
            break;
        case SCOL:
            cout << "Тип: SCOL" << endl;
            break;
        case MTHAN:
            cout << "Тип: MTHAN" << endl;
            break;
        case LTHAN:
            cout << "Тип: LTHAN" << endl;
            break;
        case EQUAL:
            cout << "Тип: EQUAL" << endl;
            break;
        case DOT:
            cout << "Тип: DOT" << endl;
            break;
        case EXC:
            cout << "Тип: EXC" << endl;
            break;
        case PACKAGE:
            cout << "Тип: PACKAGE" << endl;
            break;
        case BSLASH:
            cout << "Тип: BSLASH" << endl;
            break;
        case FUNC:
            cout << "Тип: FUNC" << endl;
            break;
        case VAR:
            cout << "Тип: VAR" << endl;
            break;
        case FLOAT64:
            cout << "Тип: FLOAT64" << endl;
            break;
        case INT:
            cout << "Тип: INT" << endl;
            break;
        case ASS:
            cout << "Тип: ASS" << endl;
            break;
        case RETURN:
            cout << "Тип: RETURN" << endl;
            break;
        case FOR:
            cout << "Тип: FOR" << endl;
            break;
        case IMPORT:
            cout << "Тип: IMPORT" << endl;
            break;
        case IF:
            cout << "Тип: IF" << endl;
            break;
        case AND:
            cout << "Тип: AND" << endl;
            break;
        case OR:
            cout << "Тип: OR" << endl;
            break;
        case ELSE:
            cout << "Тип: ELSE" << endl;
            break;
        case LEQUAL:
            cout << "Тип: LEQUAL" << endl;
            break;
        case MEQUAL:
            cout << "Тип: MEQUAL" << endl;
            break;
        case DEQUAL:
            cout << "Тип: DEQUAL" << endl;
            break;
        case EXEQUAL:
            cout << "Тип: EXEQUAL" << endl;
            break;
        case FPRINTLN:
            cout << "Тип: FPRINTLN" << endl;
            break;
        case FSQRT:
            cout << "Тип: FSQRT" << endl;
            break;
        case MAIN:
            cout << "Тип: MAIN" << endl;
            break;
        case LSQBR:
            cout << "Тип: LSQBR" << endl;
            break;
        case RSQBR:
            cout << "Тип: RSQBR" << endl;
            break;
    }
}
