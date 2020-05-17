#include <vector>
#include <iostream>
#include "Token.h"
#include "ErrorHandler.h"
#include "IDTable.h"
#include "Tree.h"

using namespace std;

class SyntaxAnalyser {
private:
    int it, sizeList, saveIt;
    vector<Token>& tokenList;
    ErrorHandler error;
    IDTable idTable;
    Tree tokenTree;

    void rollBack(int saveIt);
    void optimization();

    // Минимальные нетерминалы
    bool on_ST();    // [Строка] ST -> STR
    bool on_N();     // [Число] N -> NUM
    bool on_I();     // [Идентификатор] I -> IDENT
    bool on_T();     // [Тип] T -> INT | FLOAT64
    bool on_Z();     // [Знак числа] Z -> "+" | "-"
    bool on_M();     // [Знак множителей] M -> "*" | "/"
    bool on_NL();    // [Новая строка] NL -> "\n" | ";"
    bool on_LO();    // [Знак отношения] LO -> "==" | ">"  | "<" | ">=" | "<="
    bool on_LZ();    // [Логические знаки] LZ -> "&&" | "||"

    // Условный оператор
    void on_CIF();   // [Условие IF] CIF -> BF => LO => BF
    bool on_IF();    // [Блок IF] IF -> "if" => ["("] => CIF => {LZ => CIF} => [")"] => "{" => [BO] => "}" [ "else" => ELSE]
    int on_ELSE();   // [Блок ELSE] ELSE -> IF | ("{" => [BO] => "}")

    // Циклический оператор
    bool on_CFOR();  // [Условие FOR] CFOR -> I => (LO => I | N) | (":=" => I | N => ";" => I => LO => I | N => ";" => I => "=" => I => Z | M => I | N)
    bool on_FOR();   // [Блок FOR] FOR -> "for" => [CFOR] => "{" => [BO] => "}"

    // Составной оператор
    int on_O();      // [Оператор] O -> O | F | W | WR | RR => [NL]
    int on_BO();     // [Блок операторов] BO -> [O => {NL => O}]

    // Объявление переменных
    bool on_V();     // V -> "var" => I => T => ["=" => N] | {"," => I}
    bool on_MAS();   // [Массив] MAS -> "var" => I => "[" => N => "]" => T

    bool on_P();     // [Главное правило] P => PAC => IMP => MB
    bool on_PAC();   // [package main] on_Pac => "package" -> I => NL
    bool on_IMP();   // [import] IMP -> "(" => STR | NL => ")" => NL
    bool on_MB();    // [Тело программы] MB -> {FUN} => MAIN => {FUN}

    bool on_CFUN();  // [Вызов функции] CFUN -> I => "(" => [PF] => ")"
    bool on_PF();    // [Параметры вызова функции] PF -> BF => {"," => BF}

    // Объявление функций
    bool on_MAIN();  // [Функция main] MAIN -> "func" => "main" => "(" => ")" => "{" => [BO] => "}"
    bool on_FUN();   // [Функция] FUN -> "func" => I => "(" => [I => T => {"," => I => T}] =>")" => T => "{" => [BO] => "}"

    bool on_PRINT(); // [fmt.Println] PRINT -> "fmt.Println" => "(" => STR | CFUN | N | I => { "," => STR | CFUN | N | I} => ")"
    bool on_SQRT();  // [math.Sqrt] SQRT -> "math.Sqrt" => "(" => I | N => ")"
    bool on_RET();   // [return] RET -> "return" => CFUN | N | I => {M | Z => CFUN | N | I}

    bool on_EMAS();  // [Элемент массива] EMAS -> I => "[" => N => "]"

    bool on_OASS();  // [Оператор присваивания] OASS -> ( I | EMAS ) => "=" => BF

    // Арифметические выражения
    bool on_BM();    // [Множитель] BM -> I | N | EMAS | "(" => BF => ")"
    bool on_BS();    // [Слагаемое] BS -> BM | [(M | Z) => BS]
    bool on_BF();    // [Формула] BF -> [Z] => BS

public:
    SyntaxAnalyser(vector<Token> &tokens);
    ~SyntaxAnalyser() {};
    void analyse();
};