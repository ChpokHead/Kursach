#pragma once

#include <string>
#include <vector>

using namespace std;

class IDTable
{
private:
    vector<string> funcIDList;
    vector<string> varIDList;

public:
    IDTable() {};
    ~IDTable() {};

    // Добавление индент. функции в таблицу, если имя добавляемоего элемента
    // есть в таблице, то возвращает false
    bool pushFuncID(string str);

    // Поиск идент. функции
    bool findFuncID(string str);

    // Добавление индент. функции в таблицу, если имя добавляемоего элемента
    // есть в таблице, то возвращает false
    bool pushVarID(string str);

    // Поиск идент. переменной
    bool findVarID(string str);

    // Очистка вектора
    void clearVarId() { varIDList.clear(); };
};