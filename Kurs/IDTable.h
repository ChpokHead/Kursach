#pragma once

#include <string>
#include <vector>

using namespace std;

class IDTable
{
private:
	bool findFuncID(string str); // ����� �����. �������
	bool findVarID(string str); // ����� �����. ����������

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

	// ���������� ������. ������� � �������, ���� ��� ������������� �������� 
	// ���� � �������, �� ���������� false
	bool pushFuncID(string str); 

	// ���������� ������. ������� � �������, ���� ��� ������������� �������� 
	// ���� � �������, �� ���������� false
	bool pushVarID(string _name, bool _init);

	// �������� ���������� �� �� �������������
	bool checkInitVarID(string str); 

	// ������, ��������� ���� ���������. �� ��������������
	bool setInitVarID(string str);
};