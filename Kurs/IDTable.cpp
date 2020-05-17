#include "IDTable.h"

bool IDTable::pushFuncID(string str)
{
    if (findFuncID(str))
        return false;

    funcIDList.push_back(str);
    return true;
}

bool IDTable::findFuncID(string str)
{
    for (int i = 0; i < funcIDList.size(); i++)
    {
        if (str == funcIDList[i])
            return true;
    }

    return false;
}

/////////////////////////////////////////////////////////

bool IDTable::pushVarID(string str)
{
    if (findVarID(str))
        return false;

    varIDList.push_back(str);
    return true;
}

bool IDTable::findVarID(string str)
{
    for (int i = 0; i < varIDList.size(); i++)
    {
        if (str == varIDList[i])
            return true;
    }

    return false;
}
