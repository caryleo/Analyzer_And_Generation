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
		break;
	case 'I':
		//while
		cout << "\t循环开始" << endl;
		of_OutFile << "\t循环开始" << endl;
		_LoopHead();
		_Comment("循环开始");
		b_Loop = true;
		break;
	case '(':
		//(，不做动作
		break;
	case 'B':
		//Er
		cout << "\t条件表达式" << endl;
		of_OutFile << "\t条件表达式" << endl;
		_Comment("条件表达式");
		i_Con++;
		break;
	case ')':
		//)，不做动作
		break;
	case 'D':
		//S
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "赋值语句" << endl;
		of_OutFile << "赋值语句" << endl;
		_Comment("赋值语句");
		b_Ass = true;
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
			_Push(tok);
			i_Con++;
		}
		else if (i_Con == 2)
		{
			cout << "\t\t条件右值为：";
			of_OutFile << "\t\t条件右值为：";
			cout << tok.getStr_RealString() << ", ";
			of_OutFile << tok.getStr_RealString() << ", ";
			i_Con = 0;
			_Push(tok);
			_Compare();
			_Comment("条件表达式结束");
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
		i_Cons = 1;
		break;
	case '>':
		//>
		cout << "\t\t条件是：大于时为真" << endl;
		of_OutFile << "\t\t条件是：大于时为真" << endl;
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
			cout << "\t赋值语句左值为: ";
			of_OutFile << "\t赋值语句左值为: ";
			cout << v_Tokens[pos].getStr_RealString() << ", ";
			of_OutFile << v_Tokens[pos].getStr_RealString() << ", ";
			_ValDefine(pos);
			i_PosVal = pos;
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
		tok = v_Tokens[pos];
		v_EXP.push_back(tok);
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
		_ExprGo();
		if (b_Loop)
		{
			cout << '\t';
			of_OutFile << '\t';
		}
		cout << "\t赋值语句结束" << endl;
		of_OutFile << "\t赋值语句结束" << endl;
		_Assign();
		_Comment("赋值语句结束");
		if (b_Loop)
		{
			cout << "循环体结束" << endl;
			of_OutFile << "循环体结束" << endl;
			_LoopTail();
			_Comment("循环体结束");
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
		//未定义，定义这个变量于数据段
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
	//处理表达式
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
			//操作数
			s_OPD.push(tok);
			_Push(tok);
			i++;
		}
		else
		{
			//算符
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
					//乘除比加减优先级高，压栈
					s_OPR.push(tok);
					i++;
				}
				else if (type == A_LEX_MUL_DIV_MOD && tmptype == A_LEX_MUL_DIV_MOD)
				{
					//同级出栈先算
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
					//加减比乘除优先级低，出栈
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
					//同级出栈先算
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
					//分号，直接弹出算
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
		//标识符压栈，取定义名
		int index = _IsDefined(tok.getStr_RealString());
		string tmp = str_Data + to_string(index);
		str_CodeSegment +=
			"  MOV DX, " + tmp + "\n"
			"  PUSH DX\n";
	}
	else
	{
		//数字压栈，直接压
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
		//加
		str_CodeSegment +=
			"  ADD AX, BX\n";
	}
	else if (opr == 1)
	{
		//减
		str_CodeSegment +=
			"  SUB AX, BX\n";
	}
	else if (opr == 2)
	{
		//乘
		str_CodeSegment +=
			"  XOR DX, DX\n"
			"  IMUL BX\n";
	}
	else
	{
		//除
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
		//小于为真
		str_CodeSegment +=
			"  JNL " + stre + "\n";
	}
	else
	{
		//大于为真
		str_CodeSegment +=
			"  JNG " + stre + "\n";
	}
	i_Cons = 0;
}
