#include "LexAnalyser.h"

map<Input, Result> M; // ������� ��������� ��
map<string, Output> Keywords; // ������� �������� ���� (while, if, return...)

//�������-��������, ������� ������� � ������
string trim(string& str) // ��������� �� ���� ������
{
    bool strConst = false;
    string::const_iterator it = str.begin(); // �������� it1 ��������� �� ������ ������
    
    // ������� ��� ������� �� ��������� ��������� � ����� ���, ���� ������� - ��� ��������� ���������
    // ����� ������� ��� �������, ������� �����
    while (it != str.end()){
        if (*it == '\"') 
            strConst = (strConst == true) ? false : true; 
        if((*it == ' '|| *it == '\t' || *it == '\n') && !strConst)
            str.erase(it);
        else
            it++;
    }

    return str; // ������� ������ ��� ��������, ��������� � ��������� ������
}

LexAnalyser::LexAnalyser(const char* fname): isLast(false), isStrCon(false) //����������� ��������� �� ���� ��� ����� � ������� ��������
{
    _file.open(fname, ifstream::in); // �������� ������� ���� � �����
    if (!_file.is_open()) throw LexError("������ �������� �����"); //���� �������, ���������� �������������� ��������
    _file.unsetf(ios::skipws);

    // ���������� ������� ��������� ��

    //����� A-Z
    for (int i = 65; i <= 90; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }

    //����� a-z
    for (int i = 97; i <= 122; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }

    //����� 0-9
    for (int i = 48; i <= 57; i++) {
        M.insert(Item(Input(S0, i), Result(S4, O2)));
        M.insert(Item(Input(S4, i), Result(S4, O2)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
        M.insert(Item(Input(S5, i), Result(S5, O1)));
    }

    /*������������������������� ����������� ��� ��������������� ����������������������������*/
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    M.insert(Item(Input(S2, '\n'), Result(S6, O1)));
    M.insert(Item(Input(S2, '\t'), Result(S6, O1)));
    M.insert(Item(Input(S2, '{'), Result(S6, O1)));
    M.insert(Item(Input(S2, '}'), Result(S6, O1)));
    /*��������������������������������������������������������������������������������������*/

    /*�������������������������������� ����������� ��� ����� �������������������������������*/
    for (int i = 32; i <= 47; i++) {
        if (i != 46) M.insert(Item(Input(S4, i), Result(S6, O2))); // ����� �����
        M.insert(Item(Input(S5, i), Result(S6, O2)));
    }
    for (int i = 59; i <= 63; i++) {
        M.insert(Item(Input(S4, i), Result(S6, O2)));
        M.insert(Item(Input(S5, i), Result(S6, O2)));
    }

    M.insert(Item(Input(S4, '.'), Result(S5, O2)));
    M.insert(Item(Input(S5, '\n'), Result(S6, O2)));
    M.insert(Item(Input(S5, '\t'), Result(S6, O2)));
    M.insert(Item(Input(S5, '{'), Result(S6, O2)));
    M.insert(Item(Input(S5, '}'), Result(S6, O2)));

    M.insert(Item(Input(S4, '\n'), Result(S6, O2)));
    M.insert(Item(Input(S4, '\t'), Result(S6, O2)));
    M.insert(Item(Input(S4, '{'), Result(S6, O2)));
    M.insert(Item(Input(S4, '}'), Result(S6, O2)));
    /*��������������������������������������������������������������������������������������*/

    /*������������������������������- ��������� ��������� -���������������������������������*/
    M.insert(Item(Input(S0, '"'), Result(S1, O3)));
    M.insert(Item(Input(S1, '"'), Result(S6, O3)));
    for (int i = 65; i <= 90; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 97; i <= 122; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 48; i <= 57; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    M.insert(Item(Input(S1, '\t'), Result(S1, O3)));
    M.insert(Item(Input(S1, ','), Result(S1, O3)));
    M.insert(Item(Input(S1, '+'), Result(S1, O3)));
    M.insert(Item(Input(S1, '-'), Result(S1, O3)));
    M.insert(Item(Input(S1, '*'), Result(S1, O3)));
    M.insert(Item(Input(S1, '/'), Result(S1, O3)));
    M.insert(Item(Input(S1, '('), Result(S1, O3)));
    M.insert(Item(Input(S1, ')'), Result(S1, O3)));
    M.insert(Item(Input(S1, '{'), Result(S1, O3)));
    M.insert(Item(Input(S1, '}'), Result(S1, O3)));
    M.insert(Item(Input(S1, ':'), Result(S1, O3)));
    M.insert(Item(Input(S1, ';'), Result(S1, O3)));
    M.insert(Item(Input(S1, '>'), Result(S1, O3)));
    M.insert(Item(Input(S1, '<'), Result(S1, O3)));
    M.insert(Item(Input(S1, '='), Result(S1, O3)));
    M.insert(Item(Input(S1, '.'), Result(S1, O3)));
    M.insert(Item(Input(S1, '!'), Result(S1, O3)));
    /*��������������������������������������������������������������������������������������*/

    /*������������������������������ ��������� ����������� ���������������������������������*/
    M.insert(Item(Input(S0, ','), Result(S3, O4)));
    M.insert(Item(Input(S0, '+'), Result(S3, O5)));
    M.insert(Item(Input(S0, '-'), Result(S3, O6)));
    M.insert(Item(Input(S0, '*'), Result(S3, O7)));
    M.insert(Item(Input(S0, '/'), Result(S3, O8)));
    M.insert(Item(Input(S0, '('), Result(S3, O9)));
    M.insert(Item(Input(S0, ')'), Result(S3, O10)));
    M.insert(Item(Input(S0, '{'), Result(S3, O11)));
    M.insert(Item(Input(S0, '}'), Result(S3, O12)));
    M.insert(Item(Input(S0, ':'), Result(S3, O13)));
    M.insert(Item(Input(S0, ';'), Result(S3, O14)));
    M.insert(Item(Input(S0, '>'), Result(S3, O15)));
    M.insert(Item(Input(S0, '<'), Result(S3, O16)));
    M.insert(Item(Input(S0, '='), Result(S3, O17)));
    M.insert(Item(Input(S0, '.'), Result(S3, O18)));
    M.insert(Item(Input(S0, '!'), Result(S3, O19)));
    /*��������������������������������������������������������������������������������������*/

    M.insert(Item(Input(S0, '\t'), Result(S0, O0))); // Tab ����� ��������� �������
    M.insert(Item(Input(S0, ' '), Result(S0, O0))); // ������ ����� ��������� �������
    M.insert(Item(Input(S0, '\n'), Result(S6, O20))); // Enter ����� ��������� �������

    // ���������� ������� �������� ����

    /*������������������������-�����---- �������� ����� �---��������������������������������*/
    Keywords.insert({ "package", Output(O21) });
    Keywords.insert({ "func", Output(O22) });
    Keywords.insert({ "var", Output(O23) });
    Keywords.insert({ "float64", Output(O24) });
    Keywords.insert({ "int", Output(O25) });
    Keywords.insert({ ":=", Output(O26) });
    Keywords.insert({ "return", Output(O27) });
    Keywords.insert({ "while", Output(O28) });
    Keywords.insert({ "import", Output(O29) });
    Keywords.insert({ "if", Output(O30) });
    /*��������������������������������������������������������������������������������������*/

}

LexAnalyser::~LexAnalyser()
{
    _file.close(); //���������� ��������� �������� �����
}

vector<Token>* LexAnalyser::getTokenList() {
    return &tokenList;
}

bool LexAnalyser::getToken(Token& token)
{
    Statement current = S0; // ��������� ��������� - S0
    TokenType type; // ��� �������
    string value;
    Result res;
    char symbol;
    map<Input, Result>::const_iterator it; // �������� ��� ������� ��
    map<string, Output>::const_iterator kIt; // �������� ��� ������� �������� ����

    while (!isLast) //���� �� ����� �����
    {
        _file.get(symbol); // �������� ��������� ������
        if (_file.peek() == EOF) isLast = true;

        // ���� ������� �������� ��� ����, �� ����� true 
        if (symbol == '\"')
            isStrCon = (isStrCon == true) ? false : true; 

        it = M.find(Input(current, symbol)); // �������� ����� ������ �������, ��������������� ����� ������� ��������� current, ������� ������ symbol
        if (it == M.end()) throw LexError("������������ ������"); // ���� ����� ������ ���, ���������� �������������� ��������
        res = it->second; // �������� ���� (����� ��������� & �������� ������)

        // ���� ��� �� �����, �� �����, �� ������ ��� �� ����� �����
        if ((res.first != S2 && res.first != S4 && res.first != S5 && res.first != S1 && res.first != S0 )|| isLast) 
        {
            //������� ��������� ���������, ���� ������� ������ ������� ��� ������� ������
            if (res.first != S6 || symbol == '\"' || symbol == '\n') 
                value += symbol;

            // �������� �� :=
            if (res.second == O13)
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
            }

            switch (res.second) //�������� ������
            {
                case O1:
                    value = trim(value);
                    kIt = Keywords.find(value); // ����� ������ � ������� �������� ����
                    if (kIt == Keywords.end()) // ���� �� �����, �� ��� ������� �������������
                        type = IDENT;
                    else // ����� ���������� ����� ��� �������� �����
                        switch(kIt->second)
                        {
                            case O21:
                                type = PACKAGE; // "package"
                                break; 
                            case O22:
                                type = FUNC; // "func"
                                break;
                            case O23:
                                type = VAR; // "var"
                                break;
                            case O24:
                                type = FLOAT64; // "float64"
                                break;
                            case O25:
                                type = INT; // "int"
                                break;
                            case O26:
                                type = ASS; // :=
                                break;
                            case O27:
                                type = RETURN; // "return"
                                break;
                            case O28:
                                type = WHILE; // "while"
                                break;
                            case O29:
                                type = IMPORT; // "import"
                                break;
                            case O30:
                                type = IF; // "if"
                                break;
                        }
                    break;
                case O2:
                    type = DEC; // ���������� �����
                    break;
                case O3:
                    type = STR; // "..."
                    break;
                case O4:
                    type = COMMA; // ,
                    break;
                case O5:
                    type = PLUS; // +
                    break;
                case O6:
                    type = MINUS; // -
                    break;
                case O7:
                    type = MUL; // *
                    break;
                case O8:
                    type = DIV; // /
                    break;
                case O9:
                    type = LBR; // (
                    break;
                case O10:
                    type = RBR; // )
                    break;
                case O11:
                    type = LFBR; // {
                    break;
                case O12:
                    type = RFBR; // }
                    break;
                case O13:
                    type = COL; // :
                    break;
                case O14:
                    type = SCOL; // ;
                    break;
                case O15:
                    type = MTHAN; // >
                    break;
                case O16:
                    type = LTHAN; // <
                    break;
                case O17:
                    type = EQUAL; // =
                    break;
                case O18:
                    type = DOT; // .
                    break;
                case O19:
                    type = EXC; // !
                    break;
                case O20:
                    type = BSLASH; // \n
                    break;
                default:
                    throw LexError("����������� ������");
            }

            // �������� �������� �� ������� ��� ����
            if (isStrCon) {
                throw LexError("���������� �������");
            }

            // ��������� �������
            token.setType(type);

            // ���� ������� �� �������� �������� �����, �� �������� \n \t _ � ���� ������
            if (token.getType() < 21 && token.getType() != 0)
                token.setValue(trim(value));
            else // ����� ��������� ��� ���� (�.�. �������� ������)
                token.setValue(value);

            tokenList.push_back(token); // ��������� ����� � ������ ������

            // ���� ������� �� �����������, �� ���������� ����������� ���� ������ ������
            if (!_file.eof() && ((type == IDENT || type == DEC) || (type == 19 || (type >= 21 && type <= 29) && type != 25)))
                _file.seekg(-1, ios::cur); // ���������� ����������� ���� ������ ������
            return true;
        }
        current = res.first; // ������ ������� ���������

        value += symbol; //����������� ��������� ��������
    }
    return false;
}
