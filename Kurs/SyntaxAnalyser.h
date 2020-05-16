#include <vector>
#include <iostream>
#include "Token.h"
#include "ErrorHandler.h"
#include "IDTable.h"

using namespace std;

class SyntaxAnalyser {
private:
    int it, sizeList, saveIt;
    vector<Token>& tokenList;
    ErrorHandler error;
    IDTable idTable;

    void rollBack(int saveIt);
    void optimization();

    // ����������� �����������
    bool on_ST();    // [������] ST -> STR
    bool on_N();     // [�����] N -> NUM
    bool on_I();     // [�������������] I -> IDENT
    bool on_T();     // [���] T -> INT | FLOAT64
    bool on_Z();     // [���� �����] Z -> "+" | "-"
    bool on_M();     // [���� ����������] M -> "*" | "/"
    bool on_NL();    // [����� ������] NL -> "\n" | ";"
    bool on_LO();    // [���� ���������] LO -> "==" | ">"  | "<" | ">=" | "<="
    bool on_LZ();    // [���������� �����] LZ -> "&&" | "||"

    // �������� ��������
    void on_CIF();   // [������� IF] CIF -> BF => LO => BF
    bool on_IF();    // [���� IF] IF -> "if" => ["("] => CIF => {LZ => CIF} => [")"] => "{" => [BO] => "}" [ "else" => ELSE]
    int on_ELSE();   // [���� ELSE] ELSE -> IF | ("{" => [BO] => "}")

    // ����������� ��������
    bool on_CFOR();  // [������� FOR] CFOR -> I => (LO => I | N) | (":=" => I | N => ";" => I => LO => I | N => ";" => I => "=" => I => Z | M => I | N)
    bool on_FOR();   // [���� FOR] FOR -> "for" => [CFOR] => "{" => [BO] => "}"

    // ��������� ��������
    int on_O();      // [��������] O -> O | F | W | WR | RR => [NL]
    int on_BO();     // [���� ����������] BO -> [O => {NL => O}]

    // ���������� ����������
    bool on_V();     // V -> "var" => I => T => ["=" => N] | {"," => I}
    bool on_MAS();   // [������] MAS -> "var" => I => "[" => N => "]" => T

    bool on_P();     // [������� �������] P => PAC => IMP => MB
    bool on_PAC();   // [package main] on_Pac => "package" -> I => NL
    bool on_IMP();   // [import] IMP -> "(" => STR | NL => ")" => NL
    bool on_MB();    // [���� ���������] MB -> {FUN} => MAIN => {FUN}

    bool on_CFUN();  // [����� �������] CFUN -> I => "(" => [PF] => ")"
    bool on_PF();    // [��������� ������ �������] PF -> BF => {"," => BF}

    // ���������� �������
    bool on_MAIN();  // [������� main] MAIN -> "func" => "main" => "(" => ")" => "{" => [BO] => "}"
    bool on_FUN();   // [�������] FUN -> "func" => I => "(" => [I => T => {"," => I => T}] =>")" => T => "{" => [BO] => "}"

    bool on_PRINT(); // [fmt.Println] PRINT -> "fmt.Println" => "(" => STR | CFUN | N | I => { "," => STR | CFUN | N | I} => ")"
    bool on_SQRT();  // [math.Sqrt] SQRT -> "math.Sqrt" => "(" => I | N => ")"
    bool on_RET();   // [return] RET -> "return" => CFUN | N | I => {M | Z => CFUN | N | I}

    bool on_EMAS();  // [������� �������] EMAS -> I => "[" => N => "]"

    bool on_OASS();  // [�������� ������������] OASS -> ( I | EMAS ) => "=" => BF

    // �������������� ���������
    bool on_BM();    // [���������] BM -> I | N | EMAS | "(" => BF => ")"
    bool on_BS();    // [���������] BS -> BM | [(M | Z) => BS]
    bool on_BF();    // [�������] BF -> [Z] => BS

public:
    SyntaxAnalyser(vector<Token> &tokens);
    ~SyntaxAnalyser() {};
    void analyse();
};