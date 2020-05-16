#pragma once

#include<iostream>

//Класс-исключение ошибки этапов компиляции
class ErrorHandler
{
public:
    ErrorHandler() {};
    inline string lexError(std::string str)
    {
        std::cout << "\nОШИБКА ЛЕКСИЧЕСКОГО АНАЛИЗАТОРА: ";
        return str;
    }

    inline string syntaxError(std::string str)
    {
        std::cout << "\nОШИБКА СИНТАКСИЧЕСКОГО АНАЛИЗАТОРА. ";
        return str;
    }

    inline string fileError(std::string str)
    {
        return str;
    }

    inline string semanticError(std::string str)
    {
        std::cout << "\nОШИБКА СЕМАНТИЧЕСКОГО АНАЛИЗА. ";
        return str;
    }
};

