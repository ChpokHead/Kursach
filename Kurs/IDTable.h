#pragma once

#include <string>
#include <vector>

using namespace std;

class IDTable
{
private:
    bool findFuncID(string str); // Поиск идент. функции
    bool findVarID(string str); // Поиск идент. переменной

    struct var
    {
        string name;
        bool init;
    };

    vector<string> funcIDList;
    vector<var> varIDList;

public:
    IDTable() {};
    ~IDTable() {};

    // Добавление индент. функции в таблицу, если имя добавляемоего элемента
    // есть в таблице, то возвращает false
    bool pushFuncID(string str);

    // Добавление индент. функции в таблицу, если имя добавляемоего элемента
    // есть в таблице, то возвращает false
    bool pushVarID(string _name, bool _init);

    // Проверка переменной на ее инициализацию
    bool checkInitVarID(string str);

    // Сеттер, добавляет поле инициализ. по идентификатору
    bool setInitVarID(string str);
};