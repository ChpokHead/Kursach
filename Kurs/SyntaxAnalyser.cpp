#include "SyntaxAnalyser.h"
#define outOfBounds  if (++it >= sizeList) return false

SyntaxAnalyser::SyntaxAnalyser(vector<Token> *tokens): it(0), saveIt(0)
{
    tokenList = tokens;
    optimization();
    sizeList = tokenList->size();
}

void SyntaxAnalyser::rollBack(int saveIt)
{
    it = saveIt;
}

// Оптимизация - удаление лишних BSLASH в векторе
void SyntaxAnalyser::optimization()
{
    bool flag = false;
    auto it = tokenList->begin();

    while (it->getType() == BSLASH || it->getType() == SCOL)
    {
        it = tokenList->erase(it);
        // Если вдруг программа состоит только из \n и ;
        if (it == tokenList->end()) throw error.syntaxError("Программа не имеет операторов.");
    }

    while (it != tokenList->end())
    {
        // Удаление \n и ; после открывающихся скобок
        if (it->getType() == LBR || it->getType() == LFBR)
        {
            if (++it == tokenList->end()) break;
            while (it->getType() == BSLASH || it->getType() == SCOL)
            {
                it = tokenList->erase(it);
                if (it == tokenList->end()) break;
            }
        }
            // Удаление \n и ; до закрывающихся скобок
        else if (it->getType() == RBR || it->getType() == RFBR)
        {
            if (it == tokenList->begin())
                break;
            else
                it--;
            while (it->getType() == BSLASH || it->getType() == SCOL)
            {
                it = tokenList->erase(it);
                if (it == tokenList->begin())
                    break;
                else
                    it--;
            }

            if (it->getType() != BSLASH || it->getType() != SCOL)
                it++;
        }

        if (it == tokenList->end())
            break;
        else
            it++;
    }

    it = tokenList->begin();

    while (it != tokenList->end()) {
        if (it->getType() == BSLASH || it->getType() == SCOL)
            flag = true;

        if (++it == tokenList->end())
            break;

        while (flag && it != tokenList->end())
        {
            if (it->getType() == BSLASH || it->getType() == SCOL)
                it = tokenList->erase(it);
            else
                flag = false;
        }
    }
}

// Главный метод, с которого начинается синтаксический анализ
void SyntaxAnalyser::analyse() {
    if (on_P()) {
        cout << endl << "-----------------------------------------";
        cout << "\nСИНТАКСИЧЕЙСКИЙ АНАЛИЗ ПРОЙДЕН УСПЕШНО! |" << endl;
        cout << "-----------------------------------------" << endl;
    }
    else
        throw error.syntaxError("");
}

// P -> PAC -> IMP -> MB
bool SyntaxAnalyser::on_P() {
    if (!on_PAC()) // OK
        throw error.syntaxError("Ошибка в объявлении package.");

    if (!on_IMP()) // OK
        throw error.syntaxError("Ошибка в объявлении import.");

    if(!on_MB())
        throw error.syntaxError("Ошибка в теле программы.");

    return true;
}


// PAC => "package" => I => NL
bool SyntaxAnalyser::on_PAC() {
    if (tokenList->at(it).getType() != PACKAGE)
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != MAIN)
        return false;

    if (!on_NL())
        return false;

    return true;
}

// IMP -> "import" => [NL] => "(" => [STR => {NL => STR}] => ")" => NL
bool SyntaxAnalyser::on_IMP() {
    outOfBounds;
    if (tokenList->at(it).getType() != IMPORT)
        return false;

    saveIt = it;
    if (!on_NL())
        rollBack(saveIt);

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        return false;

    saveIt = it;
    if (!on_ST())
        rollBack(saveIt);
    else
        while (1)
        {
            saveIt = it;

            if (!on_NL()) {
                rollBack(saveIt);
                break;
            }
            if (!on_ST()) {
                return false;
            }
        }

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        return false;

    if (!on_NL())
        return false;

    return true;
}


// [Тело программы] MB -> {FUN => NL} =>  MAIN => [NL]
bool SyntaxAnalyser::on_MB()
{
    while (1)
    {
        // Создаем tempSaveIt, т.к. в on_FUN saveIt изменяется и на выходе имеет другое значение
        int tempSaveIt = it;
        if (on_FUN() == 0) {
            rollBack(tempSaveIt);
            break;
        }
        if (!on_NL()) {
            return false;
        }
    }

    if (on_MAIN() == 0) {
        throw error.syntaxError("Ожидалась функция main.");
    }

    saveIt = it;
    if (!on_NL())
        rollBack(saveIt);

    return true;
}

// [Функция main] MAIN -> "func" => "main" => "(" => ")" => "{" => [BO] => "}"
bool SyntaxAnalyser::on_MAIN()
{
    int res;
    outOfBounds;
    if (tokenList->at(it).getType() != FUNC)
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != MAIN)
        throw error.syntaxError("Ошибка в объявлении main.");

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        throw error.syntaxError("Ошибка в объявлении main.");

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        throw error.syntaxError("Ошибка в объявлении main.");

    outOfBounds;
    if (tokenList->at(it).getType() != LFBR)
        throw error.syntaxError("Ошибка в объявлении main.");

    saveIt = it;
    res = on_BO();
    if (res == 0)
        rollBack(saveIt);
    else if(res == 2)
        throw error.syntaxError("Ошибка в теле main.");

    outOfBounds;
    if (tokenList->at(it).getType() != RFBR)
        throw error.syntaxError("Ошибка в теле main.");

    return true;
}

// [Функция] FUN -> "func" => I => "(" => [I => T => {"," => I => T}] =>")" => T => "{" => [BO] => "}"
bool SyntaxAnalyser::on_FUN()
{
    int res;
    outOfBounds;
    if (tokenList->at(it).getType() != FUNC)
        return false;

    if (!on_I() && tokenList->at(it).getType() != MAIN)
        throw error.syntaxError("Ошибка в объявлении функции.");
    else if(tokenList->at(it).getType() == MAIN)
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        throw error.syntaxError("Ошибка в объявлении функции.");

    saveIt = it;
    if (on_I()) {

        saveIt = it;
        if (!on_T())
            throw error.syntaxError("Ошибка в объявлении функции.");

        saveIt = it;
        while (1)
        {
            outOfBounds;
            if (tokenList->at(it).getType() == COMMA) {
                if (!on_I())
                    throw error.syntaxError("Ошибка в объявлении функции.");

                if (!on_T())
                    throw error.syntaxError("Ошибка в объявлении функции.");
            }
            else {
                rollBack(saveIt);
                break;
            }
        }
    }
    else {
        rollBack(saveIt);
    }

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        throw error.syntaxError("Ошибка в объявлении функции.");

    if (!on_T())
        throw error.syntaxError("Ошибка в объявлении функции.");

    outOfBounds;
    if (tokenList->at(it).getType() != LFBR)
        throw error.syntaxError("Ошибка в объявлении функции.");

    saveIt = it;
    res = on_BO();
    if (res == 0)
        rollBack(saveIt);
    else if(res == 2)
        throw error.syntaxError("Ошибка в теле функции.");

    outOfBounds;
    if (tokenList->at(it).getType() != RFBR)
        throw error.syntaxError("Ошибка в теле функции.");

    return true;
}


////////////////////////// Минимальные нетерминалы //////////////////////////

// [Строка] ST => STR
bool SyntaxAnalyser::on_ST()
{
    outOfBounds;

    if (tokenList->at(it).getType() == STR)
        return true;

    return false;
}

// [Число] N -> NUM
bool SyntaxAnalyser::on_N()
{
    outOfBounds;

    if (tokenList->at(it).getType() == DEC)
        return true;

    return false;
}

// [Идентификатор] I -> IDENT
bool SyntaxAnalyser::on_I()
{
    outOfBounds;

    if (tokenList->at(it).getType() == IDENT)
        return true;

    return false;
}

// [Тип] T -> INT | FLOAT64
bool SyntaxAnalyser::on_T()
{
    outOfBounds;

    if (tokenList->at(it).getType() == INT || tokenList->at(it).getType() == FLOAT64)
        return true;

    return false;
}

// [Знак числа] Z -> "+" | "-"
bool SyntaxAnalyser::on_Z()
{
    outOfBounds;

    if (tokenList->at(it).getType() == MINUS || tokenList->at(it).getType() == PLUS)
        return true;

    return false;
}

// [Знак множителей] M -> "*" | "/"
bool SyntaxAnalyser::on_M()
{
    outOfBounds;

    if (tokenList->at(it).getType() == DIV || tokenList->at(it).getType() == MUL)
        return true;

    return false;
}

// [Новая строка] NL -> "\n" | ";"
bool SyntaxAnalyser::on_NL()
{
    outOfBounds;

    if (tokenList->at(it).getType() == BSLASH || tokenList->at(it).getType() == SCOL)
        return true;

    return false;
}

// [Знак отношения] LO -> "==" | ">" | "<" | ">=" | "<=" | "!="
bool SyntaxAnalyser::on_LO()
{
    outOfBounds;

    if (tokenList->at(it).getType() == DEQUAL)
        return true;

    if (tokenList->at(it).getType() == MTHAN)
        return true;

    if (tokenList->at(it).getType() == LTHAN)
        return true;

    if (tokenList->at(it).getType() == MEQUAL)
        return true;

    if(tokenList->at(it).getType() == LEQUAL)
        return true;

    if(tokenList->at(it).getType() == EXEQUAL)
        return true;

    return  false;
}

// [Логические знаки] LZ -> "&&" | "||"
bool SyntaxAnalyser::on_LZ()
{
    outOfBounds;
    if(tokenList->at(it).getType() == AND)
        return true;

    if(tokenList->at(it).getType() == OR)
        return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////// Условный оператор ///////////////////////////////

// "else" пришлось вынуть из блока ELSE потому что конструкция if(){} else выдавалась правильной, хотя правильно else{}
// [Оператор IF] IF -> "if" => ["("] => CIF => { LZ => CIF} => [")"] => "{" => [BO] => "}" => [ "else" => ELSE]
bool SyntaxAnalyser::on_IF()
{
    int flag = 0; // Для проверки закрытия скобок

    outOfBounds;
    if (tokenList->at(it).getType() != IF)
        return false;

    saveIt = it;
    outOfBounds;
    if (tokenList->at(it).getType() != LBR) {
        rollBack(saveIt);
        flag++;
    }

    on_CIF();

    while (1)
    {
        saveIt = it;
        if (!on_LZ()) {
            rollBack(saveIt);
            break;
        }
        on_CIF();
    }

    saveIt = it;
    outOfBounds;
    if (tokenList->at(it).getType() != RBR) {
        rollBack(saveIt);
        flag++;
    }

    if (flag != 0 && flag != 2)
        throw error.syntaxError("Ошибка закрытия скобок в операторе if.");

    outOfBounds;
    if (tokenList->at(it).getType() != LFBR)
        throw error.syntaxError("Ошибка в операторе if.");

    saveIt = it;

    if (!on_BO())
        rollBack(saveIt);

    outOfBounds;
    if (tokenList->at(it).getType() != RFBR)
        throw error.syntaxError("Ошибка в операторе if.");

    saveIt = it;
    if (++it >= sizeList)
        return true;

    if (tokenList->at(it).getType() == ELSE) {
        if (on_ELSE() == 2) {
            throw error.syntaxError("Ошибка в операторе else.");
        }
    }
    else
        rollBack(saveIt);

    return true;
}

// [Условие IF] CIF -> BF => LO => BF
void SyntaxAnalyser::on_CIF()
{
    if(!on_BF())
        throw error.syntaxError("Ошибка в условии оператора if.");

    if (!on_LO())
        throw error.syntaxError("Ошибка в условии оператора if.");

    if (!on_BF())
        throw error.syntaxError("Ошибка в условии оператора if.");
}

// [Блок ELSE] ELSE -> ("{" => [BO] => "}") | IF
int SyntaxAnalyser::on_ELSE()
{
    saveIt = it;
    outOfBounds;
    if (tokenList->at(it).getType() == LFBR) {
        saveIt = it;
        if (!on_BO())
            rollBack(saveIt);

        outOfBounds;
        if (tokenList->at(it).getType() == RFBR)
            return 1;
    }
    else {
        rollBack(saveIt);
        if (on_IF() == 0)
            return 2;
    }

    return 1;
}

/////////////////////////////////////////////////////////////////////////////

///////////////////////// Циклический оператор //////////////////////////////

// [Условие FOR] CFOR -> I => (LO => I | N) | (":=" => I | N => ";" => I => LO => I | N => ";" => I => "=" => I => Z | M => I | N)
bool SyntaxAnalyser::on_CFOR()
{
    if(!on_I()){
        return false;
    }

    saveIt = it;
    if(on_LO()){
        saveIt = it;
        if (!on_I()) {
            rollBack(saveIt);
            if (!on_N())
                throw error.syntaxError("Ошибка в условии оператора for.");
        }
        return true;
    } else {
        rollBack(saveIt);

        outOfBounds;
        if(tokenList->at(it).getType() != ASS)
            throw error.syntaxError("Ошибка в условии оператора for.");

        saveIt = it;
        if(!on_I()){
            rollBack(saveIt);
            if(!on_N())
                throw error.syntaxError("Ошибка в условии оператора for.");
        }

        outOfBounds;
        if(tokenList->at(it).getType() != SCOL)
            throw error.syntaxError("Ошибка в условии оператора for.");

        if(!on_I()){
            throw error.syntaxError("Ошибка в условии оператора for.");
        }

        if(!on_LO())
            throw error.syntaxError("Ошибка в условии оператора for.");

        saveIt = it;
        if(!on_I()){
            rollBack(saveIt);
            if(!on_N())
                throw error.syntaxError("Ошибка в условии оператора for.");
        }

        outOfBounds;
        if(tokenList->at(it).getType() != SCOL)
            throw error.syntaxError("Ошибка в условии оператора for.");

        if(!on_I()){
            throw error.syntaxError("Ошибка в условии оператора for.");
        }

        outOfBounds;
        if (tokenList->at(it).getType() != EQUAL)
            throw error.syntaxError("Ошибка в условии оператора for.");

        if (!on_I()) {
            throw error.syntaxError("Ошибка в условии оператора for.");
        }

        saveIt = it;
        if (!on_Z()) {
            rollBack(saveIt);
            if (!on_M())
                throw error.syntaxError("Ошибка в условии оператора for.");
        }

        saveIt = it;
        if (!on_I()) {
            rollBack(saveIt);
            if (!on_N())
                throw error.syntaxError("Ошибка в условии оператора for.");
        }
    }

    return true;
}

//[Блок FOR] FOR -> "for" => [CFOR] => "{" => [BO] => "}"
bool SyntaxAnalyser::on_FOR()
{
    int res;
    outOfBounds;
    if(tokenList->at(it).getType() != FOR)
        return false;

    saveIt = it;
    if(on_CFOR() == 0)
        rollBack(saveIt);

    outOfBounds;
    if(tokenList->at(it).getType() != LFBR)
        throw error.syntaxError("Ошибка в операторе for.");

    saveIt = it;
    res = on_BO();
    if (res == 0)
        rollBack(saveIt);
    else if(res == 2)
        throw error.syntaxError("Ошибка в операторе for.");

    outOfBounds;
    if(tokenList->at(it).getType() != RFBR)
        throw error.syntaxError("Ошибка в операторе for.");

    return true;
}

/////////////////////////////////////////////////////////////////////////////

//////////////////////////// Блок операторов ////////////////////////////////

// [Блок операторов] BO -> {O}
int SyntaxAnalyser::on_BO()
{
    saveIt = it;
    int res = on_O();
    if (res == 0){
        rollBack(saveIt);
        return 0;
    }
    else if (res == 2)
        return 2;
    else
        while (1) {
            saveIt = it;
            res = on_O();
            if (res == 0) {
                rollBack(saveIt);
                break;
            } else if (res == 2)
                return 2;
        }

    return 1;
}

// [Оператор] O -> V | IF | FOR | CFUN => [NL]
int SyntaxAnalyser::on_O()
{
    saveIt = it;

    if(!on_FOR())
    {
        rollBack(saveIt);
        if(!on_V())
        {
            rollBack(saveIt);
            if(!on_IF())
            {
                rollBack(saveIt);
                if(!on_CFUN())
                {
                    rollBack(saveIt);
                    if (!on_PRINT())
                    {
                        rollBack(saveIt);
                        if (!on_SQRT())
                        {
                            rollBack(saveIt);
                            if (!on_RET())
                            {
                                rollBack(saveIt);
                                if (!on_MAS())
                                {
                                    rollBack(saveIt);
                                    if (!on_OASS())
                                    {
                                        rollBack(saveIt);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }

    if (tokenList->at(it + 1).getType() != RFBR)
        if (!on_NL())
            return 2;

    return 1;
}

/////////////////////////////////////////////////////////////////////////////


//////////////////////////// Объявление функции //////////////////////////////

// [Вызов функции] CFUN -> I => "(" => [PF] => ")"
bool SyntaxAnalyser::on_CFUN()
{
    if (!on_I())
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        return false;

    saveIt = it;
    if (on_PF() == 0)
        rollBack(saveIt);

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        throw error.syntaxError("Ошибка при вызове функции.");

    return true;
}

// [Параметры вызова функции] PF -> BF => {"," => BF}
bool SyntaxAnalyser::on_PF()
{
    saveIt = it;
    if (!on_BF())
    {
        rollBack(saveIt);
        return false;
    }

    while (1)
    {
        saveIt = it;
        outOfBounds;
        if (tokenList->at(it).getType() != COMMA) {
            rollBack(saveIt);
            break;
        }

        if (!on_BF())
        {
            throw error.syntaxError("Ошибка в параметрах вызываемой функции.");
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////


///////////////////////////// Print и Sqrt //////////////////////////////////

// [fmt.Println] PRINT -> "fmt.Println" => "(" => STR | CFUN | N | I => { "," => STR | CFUN | N | I} => ")"
bool SyntaxAnalyser::on_PRINT()
{
    outOfBounds;
    if (tokenList->at(it).getType() != FPRINTLN)
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        throw error.syntaxError("Ошибка в функции fmt.Prtintln.");

    saveIt = it;
    if(!on_ST())
    {
        rollBack(saveIt);
        if (!on_CFUN())
        {
            rollBack(saveIt);
            if (!on_N())
            {
                rollBack(saveIt);
                if (!on_I())
                    throw error.syntaxError("Ошибка в функции fmt.Prtintln.");
            }
        }
    }


    while(1)
    {
        saveIt = it;
        outOfBounds;
        if (tokenList->at(it).getType() != COMMA)
        {
            rollBack(saveIt);
            break;
        }
        saveIt = it;
        if(!on_ST())
        {
            rollBack(saveIt);
            if (!on_CFUN())
            {
                rollBack(saveIt);
                if (!on_N())
                {
                    rollBack(saveIt);
                    if (!on_I())
                        throw error.syntaxError("Ошибка в функции fmt.Prtintln.");
                }
            }
        }
    }

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        throw error.syntaxError("Ошибка в функции fmt.Prtintln.");

    return true;
}

// [math.Sqrt] SQRT -> "math.Sqrt" => "(" => I | N => ")"
bool SyntaxAnalyser::on_SQRT()
{
    outOfBounds;
    if (tokenList->at(it).getType() != FSQRT)
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != LBR)
        throw error.syntaxError("Ошибка в функции math.Sqrt.");

    saveIt = it;
    if (!on_I())
    {
        rollBack(saveIt);
        if (!on_N())
            throw error.syntaxError("Ошибка в функции math.Sqrt.");
    }

    outOfBounds;
    if (tokenList->at(it).getType() != RBR)
        throw error.syntaxError("Ошибка в функции math.Sqrt.");

    return true;
}

/////////////////////////////////////////////////////////////////////////////

//////////////////////// Объявление переменных //////////////////////////////

// V -> "var" => I => T | [T => "=" => [Z] = > N] | ({"," => I} => T)
bool SyntaxAnalyser::on_V()
{
    outOfBounds;
    if (tokenList->at(it).getType() != VAR)
        return false;

    if (!on_I())
        throw error.syntaxError("Ошибка в объявлении переменной.");

    // Проверка на пересечение с объявлением массива: если это оказалось объявление массива, то return false
    saveIt = it;
    if (!on_T() && tokenList->at(it).getType() != LSQBR && tokenList->at(it).getType() != COMMA)
        throw error.syntaxError("Ошибка в объявлении переменной.");
    else if (tokenList->at(it).getType() == LSQBR)
        return false;
    rollBack(saveIt); // it возвращается на прежнюю позицию после проверки

    if(!on_T())
    {
        rollBack(saveIt);
        outOfBounds;
        if(tokenList->at(it).getType() != COMMA)
        {
            throw error.syntaxError("Ошибка в объявлении переменной.");
        }
        if(!on_I())
        {
            throw error.syntaxError("Ошибка в объявлении переменной.");
        }

        while(1)
        {
            saveIt = it;
            outOfBounds;
            if(tokenList->at(it).getType() != COMMA)
            {
                rollBack(saveIt);
                break;
            }
            if(!on_I())
            {
                rollBack(saveIt);
                break;
            }
        }
        if(!on_T())
        {
            throw error.syntaxError("Ошибка в объявлении переменной.");
        }
    }
    else
    {
        saveIt = it;
        outOfBounds;
        if(tokenList->at(it).getType() != EQUAL)
        {
            rollBack(saveIt);
            return true;
        }
        saveIt = it;
        if(!on_Z())
            rollBack(saveIt);
        if(!on_N())
            throw error.syntaxError("Ошибка в объявлении переменной.");

    }

    return true;
}

// [Массив] MAS -> "var" => I => "[" => N => "]" => T
bool SyntaxAnalyser::on_MAS()
{
    outOfBounds;
    if (tokenList->at(it).getType() != VAR)
        return false;

    if (!on_I())
        throw error.syntaxError("Ошибка в объявлении массива.");

    outOfBounds;
    if (tokenList->at(it).getType() != LSQBR )
        return false;

    if (!on_N())
        throw error.syntaxError("Ошибка в объявлении массива.");

    outOfBounds;
    if (tokenList->at(it).getType() != RSQBR)
        return false;

    if (!on_T())
        throw error.syntaxError("Ошибка в объявлении массива.");

    return true;
}

/////////////////////////////////////////////////////////////////////////////

// [return] RET -> "return" => CFUN | N | I => {M | Z => CFUN | N | I}
bool SyntaxAnalyser::on_RET()
{
    outOfBounds;
    if (tokenList->at(it).getType() != RETURN)
        return false;

    saveIt = it;
    if (!on_CFUN())
    {
        rollBack(saveIt);
        if (!on_N())
        {
            rollBack(saveIt);
            if (!on_I())
                throw error.syntaxError("Ошибка возвращаемого значения.");
        }
    }

    while (1)
    {
        saveIt = it;
        if (!on_M())
        {
            rollBack(saveIt);
            if (!on_Z())
            {
                rollBack(saveIt);
                break;
            }
            else
            {
                mark: // Лейбл goto
                saveIt = it;
                if (!on_CFUN())
                {
                    rollBack(saveIt);
                    if (!on_N())
                    {
                        rollBack(saveIt);
                        if (!on_I())
                            throw error.syntaxError("Ошибка возвращаемого значения.");
                    }
                }
            }
        }
        else
        {
            goto mark; // Для избежания дублирования кода
        }
    }

    return true;
}



// [Элемент массива] EMAS -> I => "[" => N => "]"
bool SyntaxAnalyser::on_EMAS()
{
    if (!on_I())
        return false;

    outOfBounds;
    if (tokenList->at(it).getType() != LSQBR)
        return false;

    if (!on_N())
        throw error.syntaxError("Ошибка обращения к элементу массива.");

    outOfBounds;
    if (tokenList->at(it).getType() != RSQBR)
        throw error.syntaxError("Ошибка обращения к элементу массива.");

    return true;
}

// [Оператор присваивания] OASS -> ( I | EMAS ) => "=" => BF
bool SyntaxAnalyser::on_OASS()
{
    saveIt = it;
    if (!on_EMAS())
    {
        rollBack(saveIt);
        if (!on_I())
            return false;
    }

    outOfBounds;
    if (tokenList->at(it).getType() != EQUAL)
        throw error.syntaxError("Ошибка в операторе присваивания.");

    if (!on_BF())
        throw error.syntaxError("Ошибка в операторе присваивания.");

    return true;
}

// [Формула] BF -> [Z] => BS
bool SyntaxAnalyser::on_BF()
{
    saveIt = it;
    if (!on_Z())
        rollBack(saveIt);

    if (!on_BS())
        throw error.syntaxError("Ошибка в формуле.");

    return true;
}

// [Слагаемое] BS -> BM => [(M | Z) => BS]
bool SyntaxAnalyser::on_BS()
{
    if (!on_BM())
        return false;

    saveIt = it;
    if (!on_M())
    {
        rollBack(saveIt);
        if (!on_Z())
        {
            rollBack(saveIt);
            return true;
        }
    }

    if (!on_BS())
        throw error.syntaxError("Ошибка в слагаемом.");

    return true;
}

// [Множитель] BM -> I | N | EMAS | SQRT | "(" => BF => ")"
bool SyntaxAnalyser::on_BM()
{
    saveIt = it;
    if (!on_EMAS())
    {
        rollBack(saveIt);
        if (!on_N())
        {
            rollBack(saveIt);
            if (!on_I())
            {
                rollBack(saveIt);
                if (!on_SQRT())
                {
                    rollBack(saveIt);
                    outOfBounds;
                    if (tokenList->at(it).getType() != LBR)
                        throw error.syntaxError("Ошибка в множителе.");

                    if (!on_BF())
                        throw error.syntaxError("Ошибка в множителе.");

                    outOfBounds;
                    if (tokenList->at(it).getType() != RBR)
                        throw error.syntaxError("Ошибка в множителе.");
                }

            }
        }
    }

    return true;
}