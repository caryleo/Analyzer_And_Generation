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
		cout << "ѭ����" << endl;
		of_OutFile << "ѭ����" << endl;
		b_Loop = true;
		break;
	case 'I':
		//while
		cout << "\tѭ����ʼ" << endl;
		of_OutFile << "\tѭ����ʼ" << endl;
		break;
	case '(':
		//(����������
		break;
	case 'B':
		//Er
		cout << "\t�������ʽ" << endl;
		of_OutFile << "\t�������ʽ" << endl;
		i_Con++;
		break;
	case ')':
		//)����������
		break;
	case 'D':
		//S
		if (b_Loop)
		{
			cout << "\tѭ������Ϊ��ֵ���" << endl;
			of_OutFile << "\tѭ������Ϊ��ֵ���" << endl;
			b_Ass = true;
		}
		else
		{
			cout << "��ֵ���" << endl;
			of_OutFile << "��ֵ���" << endl;
			b_Ass = true;
		}
		break;
	case 'E':
		//Vc
		tok = v_Tokens[pos];
		if (i_Con == 1)
		{
			cout << "\t\t������ֵΪ��";
			of_OutFile << "\t\t������ֵΪ��";
			cout << tok.getStr_RealString() << ", ";
			of_OutFile << tok.getStr_RealString() << ", ";
			i_Con++;
		}
		else if (i_Con == 2)
		{
			cout << "\t\t������ֵΪ��";
			of_OutFile << "\t\t������ֵΪ��";
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
		//cout << "\t�����Ҳ���" << endl;
		break;
	case '<':
		//<
		cout << "\t\t�����ǣ�С��ʱΪ��" << endl;
		of_OutFile << "\t\t�����ǣ�С��ʱΪ��" << endl;
		break;
	case '>':
		//>
		cout << "\t\t�����ǣ�����ʱΪ��" << endl;
		of_OutFile << "\t\t�����ǣ�����ʱΪ��" << endl;
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
			cout << "\t��ֵ�����ֵΪ: ";
			of_OutFile << "\t��ֵ�����ֵΪ: ";
			cout << v_Tokens[pos].getStr_RealString() << ", ";
			of_OutFile << v_Tokens[pos].getStr_RealString() << ", ";
			b_Ass = false;
		}
		if (!b_Exp)
		{
			cout << "�����ǣ���ʶ��" << endl;
			of_OutFile << "�����ǣ���ʶ��" << endl;
		}
		break;
	case 'K':
		//INT
		if (!b_Exp)
		{
			cout << "�����ǣ�����" << endl;
			of_OutFile << "�����ǣ�����" << endl;
		}
		break;
	case 'F':
		//Ex
		//cout << "���ʽ" << endl;
		break;
	case 'G':
		//Ex'
		//cout << "���ʽ�Ҳ�" << endl;
		break;
	case 'H':
		//P
		//cout << "���" << endl;
		break;
	case 'M':
		//epsilon
		//cout << "��" << endl;
		b_Exp = false;
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t��ֵ�����ֵ���ʽΪ��";
		of_OutFile << "\t��ֵ�����ֵ���ʽΪ��";
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
		//cout << "�Ӻ�" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '-':
		//-
		//cout << "����" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '*':
		//*
		//cout << "�˺�" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '/':
		///
		//cout << "����" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		break;
	case '=':
		//=
		//cout << "�Ⱥ�" << endl;
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
		//׼��������ʽ
		v_EXP.clear();
		b_Exp = true;
		break;
	case ';':
		//;
		//cout << "�ֺ�" << endl;
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t��ֵ������" << endl;
		of_OutFile << "\t��ֵ������" << endl;
		if (b_Loop)
		{
			cout << "ѭ�������" << endl;
			of_OutFile << "ѭ�������" << endl;
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