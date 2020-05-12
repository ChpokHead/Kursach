#include "Token.h"

// ����� ����� �������
void Token::printToken()
{
    switch (_type)
    {
        case IDENT:
            cout << "���: IDENT" << endl;
            break;
        case DEC:
            cout << "���: DEC" << endl;
            break;
        case STR:
            cout << "���: STR" << endl;
            break;
        case COMMA:
            cout << "���: COMMA" << endl;
            break;
        case PLUS:
            cout << "���: PLUS" << endl;
            break;
        case MINUS:
            cout << "���: MINUS" << endl;
            break;
        case MUL:
            cout << "���: MUL" << endl;
            break;
        case DIV:
            cout << "���: DIV" << endl;
            break;
        case LBR:
            cout << "���: LBR" << endl;
            break;
        case RBR:
            cout << "���: RBR" << endl;
            break;
        case LFBR:
            cout << "���: LFBR" << endl;
            break;
        case RFBR:
            cout << "���: RFBR" << endl;
            break;
        case COL:
            cout << "���: COL" << endl;
            break;
        case SCOL:
            cout << "���: SCOL" << endl;
            break;
        case MTHAN:
            cout << "���: MTHAN" << endl;
            break;
        case LTHAN:
            cout << "���: LTHAN" << endl;
            break;
        case EQUAL:
            cout << "���: EQUAL" << endl;
            break;
        case DOT:
            cout << "���: DOT" << endl;
            break;
        case EXC:
            cout << "���: EXC" << endl;
            break;
        case PACKAGE:
            cout << "���: PACKAGE" << endl;
            break;
        case BSLASH:
            cout << "���: BSLASH" << endl;
            break;
        case FUNC:
            cout << "���: FUNC" << endl;
            break;
        case VAR:
            cout << "���: VAR" << endl;
            break;
        case FLOAT64:
            cout << "���: FLOAT64" << endl;
            break;
        case INT:
            cout << "���: INT" << endl;
            break;
        case ASS:
            cout << "���: ASS" << endl;
            break;
        case RETURN:
            cout << "���: RETURN" << endl;
            break;
        case FOR:
            cout << "���: FOR" << endl;
            break;
        case IMPORT:
            cout << "���: IMPORT" << endl;
            break;
        case IF:
            cout << "���: IF" << endl;
            break;
        case AND:
            cout << "���: AND" << endl;
            break;
        case OR:
            cout << "���: OR" << endl;
            break;
        case ELSE:
            cout << "���: ELSE" << endl;
            break;
        case LEQUAL:
            cout << "���: LEQUAL" << endl;
            break;
        case MEQUAL:
            cout << "���: MEQUAL" << endl;
            break;
        case DEQUAL:
            cout << "���: DEQUAL" << endl;
            break;
        case EXEQUAL:
            cout << "���: EXEQUAL" << endl;
            break;
        case FPRINTLN:
            cout << "���: FPRINTLN" << endl;
            break;
        case FSQRT:
            cout << "���: FSQRT" << endl;
            break;
        case MAIN:
            cout << "���: MAIN" << endl;
            break;
        case LSQBR:
            cout << "���: LSQBR" << endl;
            break;
        case RSQBR:
            cout << "���: RSQBR" << endl;
            break;
    }
}
