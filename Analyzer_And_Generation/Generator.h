#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Token.h"
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
};

