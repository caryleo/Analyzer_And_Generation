#pragma once
#include <string>

using namespace std;

class IDENTIFIER
{
public:
	IDENTIFIER();
	IDENTIFIER(string name, int index);
	~IDENTIFIER();

	string getStr_Name();
	void setStr_Name(string name);
	int getI_Index();
	void setI_Index(int index);

private:
	string str_Name;
	int i_Index;
};

