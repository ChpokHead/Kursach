#include "LexAnalyser.h"

map<Input, Result> M; // Таблица переходов КА
map<string, Output> Keywords; // Таблица ключевых слов (while, if, return...)

//Функция-помощник, удаляет отступы в строке
string trim(string& str) // Принимает на вход строку
{
    bool strConst = false;
    string::const_iterator it = str.begin(); // Итератор it1 указывает на начало строки

    // Удаляет все отступы до строковой константы и после нее, если лексема - это строковая константа
    // иначе удаляет все отступы, которые видит
    while (it != str.end()){
        if (*it == '\"')
            strConst = (strConst == true) ? false : true;
        if((*it == ' '|| *it == '\t' || *it == '\n') && !strConst)
            str.erase(it);
        else
            it++;
    }

    return str; // Создаем строку без пробелов, табуляций и переносов строки
}

LexAnalyser::LexAnalyser(const char* fname) : isLast(false), isStrCon(false) //Конструктор принимает на вход имя файла с входной цепочкой
{
    _file.open(fname, ifstream::in); // Пытаемся открыть файл в поток
    if (!_file.is_open()) throw error.fileError(("Ошибка открытия файла")); //Если неудача, возбуждаем исключительную ситуацию
    _file.unsetf(ios::skipws);

    // Заполнение таблицы переходов КА

    //Буквы A-Z
    for (int i = 65; i <= 90; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }

    //Буквы a-z
    for (int i = 97; i <= 122; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }

    //Цифры 0-9
    for (int i = 48; i <= 57; i++) {
        M.insert(Item(Input(S0, i), Result(S4, O2)));
        M.insert(Item(Input(S4, i), Result(S4, O2)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
        M.insert(Item(Input(S5, i), Result(S5, O1)));
    }

    /*––––––––––––––––––––––––– РАЗДЕЛИТЕЛИ ДЛЯ ИДЕНТИФИКАТОРОВ ––––––––––––––––––––––––––––*/
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    M.insert(Item(Input(S2, '\n'), Result(S6, O1)));
    M.insert(Item(Input(S2, '\t'), Result(S6, O1)));
    M.insert(Item(Input(S2, '{'), Result(S6, O1)));
    M.insert(Item(Input(S2, '}'), Result(S6, O1)));
    M.insert(Item(Input(S2, '|'), Result(S6, O1)));
    M.insert(Item(Input(S2, '['), Result(S6, O1)));
    M.insert(Item(Input(S2, ']'), Result(S6, O1)));
    /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

    /*–––––––––––––––––––––––––––––––– РАЗДЕЛИТЕЛИ ДЛЯ ЧИСЕЛ –––––––––––––––––––––––––––––––*/
    for (int i = 32; i <= 47; i++) {
        if (i != 46) M.insert(Item(Input(S4, i), Result(S6, O2))); // Кроме точки
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
    M.insert(Item(Input(S5, '|'), Result(S6, O2)));
    M.insert(Item(Input(S4, '\n'), Result(S6, O2)));
    M.insert(Item(Input(S4, '\t'), Result(S6, O2)));
    M.insert(Item(Input(S4, '{'), Result(S6, O2)));
    M.insert(Item(Input(S4, '}'), Result(S6, O2)));
    M.insert(Item(Input(S4, '|'), Result(S6, O2)));
    M.insert(Item(Input(S4, '['), Result(S6, O2)));
    M.insert(Item(Input(S4, ']'), Result(S6, O2)));

    /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

    /*––––––––––––––––––––––––––––––- СТРОКОВАЯ КОНСТАНТА -–––––––––––––––––––––––––––––––––*/
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
    M.insert(Item(Input(S1, '&'), Result(S1, O3)));
    M.insert(Item(Input(S1, '|'), Result(S1, O3)));
    M.insert(Item(Input(S1, '['), Result(S1, O3)));
    M.insert(Item(Input(S1, ']'), Result(S1, O3)));

    /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

    /*–––––––––––––––––––––––––––––– ОПЕРАТОРЫ РАЗДЕЛИТЕЛИ –––––––––––––––––––––––––––––––––*/
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
    M.insert(Item(Input(S0, '&'), Result(S3, O31)));
    M.insert(Item(Input(S0, '|'), Result(S3, O32)));
    M.insert(Item(Input(S0, '['), Result(S3, O41)));
    M.insert(Item(Input(S0, ']'), Result(S3, O42)));

    /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

    M.insert(Item(Input(S0, '\t'), Result(S0, O0))); // Tab после очередной лексемы
    M.insert(Item(Input(S0, ' '), Result(S0, O0))); // Пробел после очередной лексемы
    M.insert(Item(Input(S0, '\n'), Result(S6, O20))); // Enter после очередной лексемы

    // Заполнение таблицы ключевых слов

    /*––––––––––––––––––––––––-–––––---- КЛЮЧЕВЫЕ СЛОВА –---––––––––––––––––––––––––––––––––*/
    Keywords.insert({ "package", Output(O21) });
    Keywords.insert({ "func", Output(O22) });
    Keywords.insert({ "var", Output(O23) });
    Keywords.insert({ "float64", Output(O24) });
    Keywords.insert({ "int", Output(O25) });
    Keywords.insert({ ":=", Output(O26) });
    Keywords.insert({ "return", Output(O27) });
    Keywords.insert({ "for", Output(O28) });
    Keywords.insert({ "import", Output(O29) });
    Keywords.insert({ "if", Output(O30) });
    Keywords.insert({ "&&", Output(O31) });
    Keywords.insert({ "||", Output(O32) });
    Keywords.insert({ "else", Output(O33) });
    Keywords.insert({ "<=", Output(O34) });
    Keywords.insert({ ">=", Output(O35) });
    Keywords.insert({ "==", Output(O36) });
    Keywords.insert({ "!=", Output(O37) });
    Keywords.insert({ "fmt.Println", Output(O38) });
    Keywords.insert({ "math.Sqrt", Output(O39) });
    Keywords.insert({ "main", Output(O40) });

    /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
}

LexAnalyser::~LexAnalyser()
{
    _file.close(); //Деструктор закрывает файловый поток
}

bool LexAnalyser::getToken(Token& token)
{
    Statement current = S0; // Начальное состояние - S0
    TokenType type; // Тип лексемы
    string value;
    Result res;
    char symbol;
    map<Input, Result>::const_iterator it; // Итератор для таблицы КА
    map<string, Output>::const_iterator kIt; // Итератор для таблицы ключевых слов

    while (!isLast) //Пока не конец файла
    {
        _file.get(symbol); // Получаем очередной символ
        if (_file.peek() == EOF) isLast = true;

        // Если кавычка остается без пары, то будет true
        if (symbol == '\"')
            isStrCon = !isStrCon;

        it = M.find(Input(current, symbol)); // Пытаемся найти ячейку таблицы, соответствующую ключу Текущее Состояние current, Входной Символ symbol
        if (it == M.end()) // Если такой ячейки нет, возбуждаем исключительную ситуацию
            if (isStrCon)
                throw error.lexError(("Незакрытые кавычки"));
            else
                throw error.lexError(("Некорректный символ"));

        res = it->second; // Получаем пару (Новое Состояние & Выходной сигнал)

        // Если это не буква, не цифра, не строка или не конец файла
        if ((res.first != S2 && res.first != S4 && res.first != S5 && res.first != S1 && res.first != S0 )|| isLast)
        {
            //Текущее состояние финальное, либо текущий символ кавычка или перенос строки
            if (res.first != S6 || symbol == '\"' || symbol == '\n')
                value += symbol;

            // Проверка на :=
            if (symbol == ':')
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на >=
            if (symbol == '>')
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на <=
            if (symbol == '<')
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на ==
            if (symbol == '=')
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на !=
            if (symbol == '!')
            {
                _file.get(symbol);
                if (symbol == '=') {
                    value += symbol;
                    res.second = O1;
                }
                else  _file.seekg(-1, ios::cur);
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на &&
            if (symbol == '&')
            {
                _file.get(symbol);
                if (symbol == '&') {
                    value += symbol;
                    res.second = O1;
                }
                    // Т.к. не может быть одиночного & вне строковой константы
                else  throw error.lexError(("Некорректный символ"));
                if (_file.peek() == EOF) isLast = true;
            }

            // Проверка на ||
            if (symbol == '|')
            {
                _file.get(symbol);
                if (symbol == '|') {
                    value += symbol;
                    res.second = O1;
                }
                    // Т.к. не может быть одиночного | вне строковой константы
                else  throw error.lexError(("Некорректный символ"));
                if (_file.peek() == EOF) isLast = true;
            }

            switch (res.second) //Выходной сигнал
            {
                // Если \n или \t, то цикл можно не продолжать
                case O0:
                    continue;
                case O1:
                    value = trim(value);
                    // Проверка, необходимая для считывания fmt.Println и math.Sqrt в виде одной лексемы
                    if(symbol == '.' && (value.compare("fmt") == 0 || value.compare("math") == 0)) {
                        res.first = S2;
                        value += symbol;
                        continue;
                    }
                    kIt = Keywords.find(value); // Поиск ячейки в таблице ключевых слов
                    if (kIt == Keywords.end()) // Если не нашел, то это обычный идентификатор
                        type = IDENT;
                    else // Иначе определяем какое это ключевое слово
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
                                type = FOR; // "while"
                                break;
                            case O29:
                                type = IMPORT; // "import"
                                break;
                            case O30:
                                type = IF; // "if"
                                break;
                            case O31:
                                type = AND; // &&
                                break;
                            case O32:
                                type = OR; // ||
                                break;
                            case O33:
                                type = ELSE; // "else"
                                break;
                            case O34:
                                type = LEQUAL; // <=
                                break;
                            case O35:
                                type = MEQUAL; // >=
                                break;
                            case O36:
                                type = DEQUAL; // ==
                                break;
                            case O37:
                                type = EXEQUAL; // !=
                                break;
                            case O38:
                                type = FPRINTLN; // fmt.Println
                                break;
                            case O39:
                                type = FSQRT; // math.Sqrt
                                break;
                            case O40:
                                type = MAIN; // main
                                break;
                        }
                    break;
                case O2:
                    type = DEC; // Десятичное число
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
                case O41:
                    type = LSQBR; // [
                    break;
                case O42:
                    type = RSQBR; // ]
                    break;
                default:
                    throw  error.lexError(("Лексическая ошибка"));
            }

            // Проверка осталась ли кавычка без пары
            if (isStrCon) {
                throw error.lexError(("Незакрытые кавычки"));
            }

            // Формируем лексему
            token.setType(type);

            // Если лексема не ключевое ключевое слово, то обрезаем \n \t _ в этой строке
            if (token.getType() > 39 || token.getType() < 21 && token.getType() != 0)
                token.setValue(trim(value));
            else // Иначе оставляем как есть (т.к. обрезали раньше)
                token.setValue(value);

            tokenList.push_back(token); // Добавляем токен в вектор лексем

            // Если лексема не разделитель, то возвращаем захваченный нами лишний символ
            // Условие такое длинное, потому что типы стоят не по порядку, они добавлялись в процессе написания программы
            if (!_file.eof() && ((type == IDENT || type == DEC) || (type == 19 || (type >= 21 && type <= 39) && (type != 25 && type != 30 && type != 31 && (type <= 32 || type >= 37)))))
                _file.seekg(-1, ios::cur); // Возвращаем захваченный нами лишний символ
            return true;
        }
        current = res.first; // Меняем текущее состояние

        value += symbol; //Накапливаем строковое значение
    }
    return false;
}
