#pragma once

#include<iostream>

//Êëàññ-èñêëş÷åíèå îøèáêè ıòàïîâ êîìïèëÿöèè
class ErrorHandler
{
public:
    ErrorHandler() {};
    inline string lexError(std::string str)
    {
        std::cout << "\nÎØÈÁÊÀ ËÅÊÑÈ×ÅÑÊÎÃÎ ÀÍÀËÈÇÀÒÎĞÀ: ";
        return str;
    }

    inline string syntaxError(std::string str)
    {
        std::cout << "\nÎØÈÁÊÀ ÑÈÍÒÀÊÑÈ×ÅÑÊÎÃÎ ÀÍÀËÈÇÀÒÎĞÀ. ";
        return str;
    }

    inline string fileError(std::string str)
    {
        return str;
    }

    inline string semanticError(std::string str)
    {
        std::cout << "\nÎØÈÁÊÀ ÑÅÌÀÍÒÈ×ÅÑÊÎÃÎ ÀÍÀËÈÇÀ. ";
        return str;
    }
};

