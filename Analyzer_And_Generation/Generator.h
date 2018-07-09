#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Token.h"
#include "IDENTIFIER.h"
using namespace std;

class Generator
{
public:
	Generator();
	~Generator();

	vector<Token> v_Tokens;
	/**
	 * 代码生成
	 */
	void Generate(char c, int pos);
	/**
	 * 初始化
	 */
	void Init(string fileName);
	void Close();
	void End();
	void Print();
private:
	string str_AsmFileName;//汇编语言文件名
	string str_FilePath;//文件路径
	string str_OutFileName;//源程序语法分析文件名

	ofstream of_AsmFile;//输出汇编代码文件
	ofstream of_OutFile;//语法分析输出文件

	string str_StackSegment;//堆栈段
	string str_DataSegment;//数据段
	string str_CodeSegment;//程序段
	string str_Data;
	string str_Label;

	bool b_Loop;//循环状态量
	int i_Con;//条件状态量
	bool b_Ass;//赋值左值状态量
	bool b_Exp;//赋值右值状态量

	stack<Token> s_OPD;
	stack<Token> s_OPR;
	vector<Token> v_EXP;

	vector<IDENTIFIER> v_Identifier;
	int i_Val;//变量
	int i_Label;//标签
	int i_PosVal;//赋值左值所在位置
	int i_Cons;//当前条件表达式的目标


	void _ValDefine(int pos);
	int _IsDefined(string name);
	void _ExprGo();
	void _Push(Token tok);
	void _Pop(string reg);
	void _CAL(int opr);
	void _Assign();
	void _Comment(string comment);
	void _LoopHead();
	void _LoopTail();
	void _Compare();
};

