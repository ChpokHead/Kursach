#include "SyntaxAnalyser.h"

SyntaxAnalyser::SyntaxAnalyser(vector<Token> *tokens): it(0) {
     tokenList = tokens;
}

// Главный метод с которого начинается синтаксический анализ
void SyntaxAnalyser :: analyse() {
    if(on_P())
        cout << "Синтаксический анализ пройден успешно!" << endl;
    else
        cout << "Ошибка синтаксического анализа!" << endl;
}

// Проверяем на главный пакет в начале программы
bool SyntaxAnalyser::on_P() {
    if(tokenList->at(it).getType() != PACKAGE)
        return false;
    return true;
}