#include "stdafx.h"
#include "IDENTIFIER.h"


IDENTIFIER::IDENTIFIER()
{
}

IDENTIFIER::IDENTIFIER(string name, int index)
{
	str_Name = name;
	i_Index = index;
}


IDENTIFIER::~IDENTIFIER()
{
}

string IDENTIFIER::getStr_Name()
{
	return str_Name;
}

void IDENTIFIER::setStr_Name(string name)
{
	str_Name = name;
}

int IDENTIFIER::getI_Index()
{
	return i_Index;
}

void IDENTIFIER::setI_Index(int index)
{
	i_Index = index;
}
