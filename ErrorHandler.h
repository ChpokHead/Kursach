#pragma once

#include<iostream>

//�����-���������� ������ ������ ����������
class ErrorHandler
{
public:
    ErrorHandler() {};
    inline string lexError(std::string str)
    {
        std::cout << "������ ������������ �����������: ";
        return str;
    }

    inline string syntaxError(std::string str)
    {
        std::cout << "\n������ ��������������� �����������.";
        return str;
    }

    inline string fileError(std::string str)
    {
        return str;
    }
};

