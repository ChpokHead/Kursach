#pragma once

#include<iostream>

// ласс-исключение ошибки этапов компил€ции
class ErrorHandler
{
public:
    ErrorHandler() {};
    inline string lexError(std::string str)
    {
        std::cout << "ќшибка лексического анализатора: ";
        return str;
    }

    inline string syntaxError(std::string str)
    {
        std::cout << "\nќшибка синтаксического анализатора.";
        return str;
    }

    inline string fileError(std::string str)
    {
        return str;
    }
};

