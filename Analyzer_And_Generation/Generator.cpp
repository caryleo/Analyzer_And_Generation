#include "stdafx.h"
#include "Generator.h"


Generator::Generator()
{
}


Generator::~Generator()
{
}

void Generator::Generate(char c, int pos)
{
	Token tok;
	Token tmp1;
	Token tmp2;
	int len;
	switch (c)
	{
	case 'A':
		//Sw
		cout << "循环体" << endl;
		of_OutFile << "循环体" << endl;
		b_Loop = true;
		break;
	case 'I':
		//while
		cout << "\t循环开始" << endl;
		of_OutFile << "\t循环开始" << endl;
		break;
	case '(':
		//(，不做动作
		break;
	case 'B':
		//Er
		cout << "\t条件表达式" << endl;
		of_OutFile << "\t条件表达式" << endl;
		i_Con++;
		break;
	case ')':
		//)，不做动作
		break;
	case 'D':
		//S
		if (b_Loop)
		{
			cout << "\t循环内容为赋值语句" << endl;
			of_OutFile << "\t循环内容为赋值语句" << endl;
			b_Ass = true;
		}
		else
		{
			cout << "赋值语句" << endl;
			of_OutFile << "赋值语句" << endl;
			b_Ass = true;
		}
		break;
	case 'E':
		//Vc
		tok = v_Tokens[pos];
		if (i_Con == 1)
		{
			cout << "\t\t条件左值为：";
			of_OutFile << "\t\t条件左值为：";
			cout << tok.getStr_RealString() << ", ";
			of_OutFile << tok.getStr_RealString() << ", ";
			i_Con++;
		}
		else if (i_Con == 2)
		{
			cout << "\t\t条件右值为：";
			of_OutFile << "\t\t条件右值为：";
			cout << tok.getStr_RealString() << ", ";
			of_OutFile << tok.getStr_RealString() << ", ";
			i_Con = 0;
		}
		else if (b_Exp)
		{
			v_EXP.push_back(tok);
		}
		break;
	case 'C':
		//Er'
		//cout << "\t条件右部分" << endl;
		break;
	case '<':
		//<
		cout << "\t\t条件是：小于时为真" << endl;
		of_OutFile << "\t\t条件是：小于时为真" << endl;
		break;
	case '>':
		//>
		cout << "\t\t条件是：大于时为真" << endl;
		of_OutFile << "\t\t条件是：大于时为真" << endl;
		break;
	case 'J':
		//ID
		
		if (b_Ass)
		{
			if (b_Loop)
			{
				cout << '\t';
				of_OutFile << '\t';
			}
			cout << "\t赋值语句左值为: ";
			of_OutFile << "\t赋值语句左值为: ";
			cout << v_Tokens[pos].getStr_RealString() << ", ";
			of_OutFile << v_Tokens[pos].getStr_RealString() << ", ";
			b_Ass = false;
		}
		if (!b_Exp)
		{
			cout << "类型是：标识符" << endl;
			of_OutFile << "类型是：标识符" << endl;
		}
		break;
	case 'K':
		//INT
		if (!b_Exp)
		{
			cout << "类型是：整数" << endl;
			of_OutFile << "类型是：整数" << endl;
		}
		break;
	case 'F':
		//Ex
		//cout << "表达式" << endl;
		break;
	case 'G':
		//Ex'
		//cout << "表达式右部" << endl;
		break;
	case 'H':
		//P
		//cout << "算符" << endl;
		break;
	case 'M':
		//epsilon
		//cout << "空" << endl;
		b_Exp = false;
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t赋值语句右值表达式为：";
		of_OutFile << "\t赋值语句右值表达式为：";
		len = v_EXP.size();
		for (int i = 0; i < len; ++i)
		{
			cout << " " << v_EXP[i].getStr_RealString();
			of_OutFile << " " << v_EXP[i].getStr_RealString();
		}
		cout << endl;
		of_OutFile << endl;
		break;
	case '+':
		//+
		//cout << "加号" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '-':
		//-
		//cout << "减号" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '*':
		//*
		//cout << "乘号" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '/':
		///
		//cout << "除号" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '=':
		//=
		//cout << "等号" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		//准备处理表达式
		v_EXP.clear();
		b_Exp = true;
		break;
	case ';':
		//;
		//cout << "分号" << endl;
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t赋值语句结束" << endl;
		of_OutFile << "\t赋值语句结束" << endl;
		if (b_Loop)
		{
			cout << "循环体结束" << endl;
			of_OutFile << "循环体结束" << endl;
			b_Loop = false;
		}
		break;
	default:
		break;
	}
}

void Generator::Init(string fileName)
{
	str_AsmFileName = fileName + ".asm";
	str_OutFileName = fileName + "_SynOut.txt";
	str_FilePath = ".\\Data\\";
	string outFile = str_FilePath + str_OutFileName;
	string asmFile = str_FilePath + str_AsmFileName;
	of_OutFile.open(outFile, ios::out);
	of_AsmFile.open(asmFile, ios::out);
	b_Loop = false;
	i_Con = 0;
	b_Ass = false;
	b_Exp = false;
	str_StackSegment =
		"STACKSG SEGMENT STACK \'S\'\n"
		"  DW 32 DUP(?)\n"
		"STACKSG ENDS\n";
	str_DataSegment =
		"DATA SEGMENT\n";
	str_CodeSegment =
		"CODE SEGMENT\n"
		"  ASSUME CS:CODE, DS:DATA, SS:STACKSG\n"
		"MAIN PROC\n"
		"  MOV AX, DATA\n"
		"  MOV DS, AX\n";
}

void Generator::Close()
{
	of_AsmFile.close();
	of_OutFile.close();
}