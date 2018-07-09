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
		break;
	case 'I':
		//while
		cout << "\tѭ����ʼ" << endl;
		of_OutFile << "\tѭ����ʼ" << endl;
		_LoopHead();
		_Comment("ѭ����ʼ");
		b_Loop = true;
		break;
	case '(':
		//(����������
		break;
	case 'B':
		//Er
		cout << "\t�������ʽ" << endl;
		of_OutFile << "\t�������ʽ" << endl;
		_Comment("�������ʽ");
		i_Con++;
		break;
	case ')':
		//)����������
		break;
	case 'D':
		//S
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "��ֵ���" << endl;
		of_OutFile << "��ֵ���" << endl;
		_Comment("��ֵ���");
		b_Ass = true;
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
			_Push(tok);
			i_Con++;
		}
		else if (i_Con == 2)
		{
			cout << "\t\t������ֵΪ��";
			of_OutFile << "\t\t������ֵΪ��";
			cout << tok.getStr_RealString() << ", ";
			of_OutFile << tok.getStr_RealString() << ", ";
			i_Con = 0;
			_Push(tok);
			_Compare();
			_Comment("�������ʽ����");
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
		i_Cons = 1;
		break;
	case '>':
		//>
		cout << "\t\t�����ǣ�����ʱΪ��" << endl;
		of_OutFile << "\t\t�����ǣ�����ʱΪ��" << endl;
		i_Cons = 2;
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
			_ValDefine(pos);
			i_PosVal = pos;
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
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
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
		_ExprGo();
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t��ֵ������" << endl;
		of_OutFile << "\t��ֵ������" << endl;
		_Assign();
		_Comment("��ֵ������");
		if (b_Loop)
		{
			cout << "ѭ�������" << endl;
			of_OutFile << "ѭ�������" << endl;
			_LoopTail();
			_Comment("ѭ�������");
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
	str_Data = "D_";
	str_Label = "L_";
	b_Loop = false;
	i_Con = 0;
	b_Ass = false;
	b_Exp = false;
	v_Identifier.clear();
	i_Val = 0;
	i_Label = 0;
	i_Cons = 0;
	str_StackSegment =
		"STACKSG SEGMENT STACK \'S\'\n"
		"  DW 32 DUP(?)\n"
		"STACKSG ENDS\n";
	str_DataSegment =
		"DATA SEGMENT\n";
	str_CodeSegment =
		"CODE SEGMENT\n"
		"  ASSUME CS:CODE, DS:DATA, SS:STACKSG\n"
		"MAIN PROC FAR\n"
		"  MOV AX, DATA\n"
		"  MOV DS, AX\n";
}

void Generator::Close()
{
	of_AsmFile.close();
	of_OutFile.close();
}

void Generator::End()
{
	str_DataSegment +=
		"DATA ENDS\n";
	str_CodeSegment +=
		"  MOV AX, 4C00H\n"
		"  INT 21H\n"
		"MAIN ENDP\n"
		"CODE ENDS\n"
		"END MAIN\n";
}

void Generator::Print()
{
	of_AsmFile << str_StackSegment << endl;
	of_AsmFile << str_DataSegment << endl;
	of_AsmFile << str_CodeSegment << endl;
}

void Generator::_ValDefine(int pos)
{
	Token tok = v_Tokens[pos];
	int tag = _IsDefined(tok.getStr_RealString());
	if (tag == -1)
	{
		//δ���壬����������������ݶ�
		IDENTIFIER id(tok.getStr_RealString(), i_Val);
		v_Identifier.push_back(id);
		string idName = str_Data + to_string(i_Val);
		str_DataSegment +=
			"  " + idName + " DW ?\n";
		i_Val++;
	}
}

int Generator::_IsDefined(string name)
{
	if (v_Identifier.size() > 0)
	{
		for (int i = 0; i < v_Identifier.size(); i++)
		{
			string tmp = v_Identifier[i].getStr_Name();
			if (tmp == name)
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		return -1;
	}
}

void Generator::_ExprGo()
{
	//������ʽ
	int len = v_EXP.size();
	while (!s_OPD.empty())
	{
		s_OPD.pop();
	}
	while (!s_OPR.empty())
	{
		s_OPR.pop();
	}
	int i = 0;
	while (i < len)
	{
		Token tok = v_EXP[i];
		e_Attributes type = tok.getEa_Type();
		e_KeywordKind kind = tok.getEk_kind();
		if (type == A_LEX_IDENTITY || type == A_LEX_INT || type == A_LEX_HIGH_PRIORITY)
		{
			//������
			s_OPD.push(tok);
			_Push(tok);
			i++;
		}
		else
		{
			//���
			if (s_OPR.size() == 0)
			{
				s_OPR.push(tok);
				i++;
			}
			else
			{
				Token tmp = s_OPR.top();
				e_Attributes tmptype = tmp.getEa_Type();
				e_KeywordKind tmpkind = tmp.getEk_kind();
				if (type == A_LEX_MUL_DIV_MOD && tmptype == A_LEX_ADD_SUB)
				{
					//�˳��ȼӼ����ȼ��ߣ�ѹջ
					s_OPR.push(tok);
					i++;
				}
				else if (type == A_LEX_MUL_DIV_MOD && tmptype == A_LEX_MUL_DIV_MOD)
				{
					//ͬ����ջ����
					s_OPR.pop();
					if (tmpkind == K_OPR_MUL)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(2);
					}
					else
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(3);
					}
					s_OPD.push(Token(A_LEX_INT, K_CONSTANT_INTEGER, "0", Position(0, 0), Position(0, 0)));
				}
				else if (type == A_LEX_ADD_SUB && tmptype == A_LEX_MUL_DIV_MOD)
				{
					//�Ӽ��ȳ˳����ȼ��ͣ���ջ
					s_OPR.pop();
					if (tmpkind == K_OPR_MUL)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(2);
					}
					else
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(3);
					}
					s_OPD.push(Token(A_LEX_INT, K_CONSTANT_INTEGER, "0", Position(0, 0), Position(0, 0)));
				}
				else if (type == A_LEX_ADD_SUB && tmptype == A_LEX_ADD_SUB)
				{
					//ͬ����ջ����
					s_OPR.pop();
					if (tmpkind == K_OPR_ADD)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(0);
					}
					else
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(1);
					}
					s_OPD.push(Token(A_LEX_INT, K_CONSTANT_INTEGER, "0", Position(0, 0), Position(0, 0)));
				}
				else
				{
					//�ֺţ�ֱ�ӵ�����
					s_OPR.pop();
					if (tmpkind == K_OPR_ADD)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(0);
					}
					else if (tmpkind == K_OPR_SUB)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(1);
					}
					else if (tmpkind == K_OPR_MUL)
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(2);
					}
					else
					{
						s_OPD.pop();
						_Pop("BX");
						s_OPD.pop();
						_Pop("AX");
						_CAL(3);
					}
				}
			}
		}
	}
}

void Generator::_Push(Token tok)
{
	if (tok.getEa_Type() == A_LEX_IDENTITY)
	{
		//��ʶ��ѹջ��ȡ������
		int index = _IsDefined(tok.getStr_RealString());
		string tmp = str_Data + to_string(index);
		str_CodeSegment +=
			"  MOV DX, " + tmp + "\n"
			"  PUSH DX\n";
	}
	else
	{
		//����ѹջ��ֱ��ѹ
		string tmp = tok.getStr_RealString();
		str_CodeSegment +=
			"  MOV DX, " + tmp + "\n"
			"  PUSH DX\n";
	}
}

void Generator::_Pop(string reg)
{
	str_CodeSegment +=
		"  POP " + reg + "\n";
}

void Generator::_CAL(int opr)
{
	if (opr == 0)
	{
		//��
		str_CodeSegment +=
			"  ADD AX, BX\n";
	}
	else if (opr == 1)
	{
		//��
		str_CodeSegment +=
			"  SUB AX, BX\n";
	}
	else if (opr == 2)
	{
		//��
		str_CodeSegment +=
			"  XOR DX, DX\n"
			"  IMUL BX\n";
	}
	else
	{
		//��
		str_CodeSegment +=
			"  XOR DX, DX\n"
			"  IDIV BX\n";
	}
	str_CodeSegment +=
		"  PUSH AX\n";
}

void Generator::_Assign()
{
	int index = _IsDefined(v_Tokens[i_PosVal].getStr_RealString());
	_Pop("AX");
	string tmp = str_Data + to_string(index);
	str_CodeSegment +=
		"  MOV " + tmp + ", AX\n";
}

void Generator::_Comment(string comment)
{
	str_CodeSegment +=
		"  ;" + comment + "\n";
}

void Generator::_LoopHead()
{
	string str = str_Label + "S" + to_string(i_Label) + ":";
	str_CodeSegment +=
		str;
}

void Generator::_LoopTail()
{
	string stre = str_Label + "E" + to_string(i_Label) + ":";
	string strs = str_Label + "S" + to_string(i_Label);
	str_CodeSegment +=
		"  JMP " + strs + "\n" + stre;
	i_Label++;
}

void Generator::_Compare()
{
	_Pop("BX");
	_Pop("AX");
	str_CodeSegment +=
		"  CMP AX, BX\n";
	string stre = str_Label + "E" + to_string(i_Label);
	if (i_Cons == 1)
	{
		//С��Ϊ��
		str_CodeSegment +=
			"  JNL " + stre + "\n";
	}
	else
	{
		//����Ϊ��
		str_CodeSegment +=
			"  JNG " + stre + "\n";
	}
	i_Cons = 0;
}
