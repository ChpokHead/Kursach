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

bool IDTable::pushVarID(string _name, bool _init)
{
	if (findVarID(_name))
		return false;

	var v;
	v.name = _name;
	v.init = _init;
	varIDList.push_back(v);
	return true;
}

bool IDTable::findVarID(string str)
{
	for (int i = 0; i < varIDList.size(); i++) 
	{
		if (str == varIDList[i].name)
			return true;
	}

	return false;
}

bool IDTable::checkInitVarID(string str)
{
	for (int i = 0; i < varIDList.size(); i++)
	{
		if (str == varIDList[i].name && varIDList[i].init)
		{
			return true;
		}
	}

	return false;
}

bool IDTable::setInitVarID(string str)
{
	for (int i = 0; i < varIDList.size(); i++)
	{
		if (str == varIDList[i].name)
		{
			varIDList[i].init = true;
			return true;
		}
	}

	return false;
}
