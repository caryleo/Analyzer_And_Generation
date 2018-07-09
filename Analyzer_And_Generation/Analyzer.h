#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "Token.h"
#include <vector>
#include <stack>
#include "Generator.h"
using namespace std;

class Analyzer
{
public:
	Analyzer();
	Analyzer(Generator *gen);
	~Analyzer();
	/**
	 * 初始化函数
	 * @param fileName 文件名
	 */
	void Init(string fileName);
	/**
	 * 执行函数
	 */
	void Execute();
private:
	Generator *g_Gen;//代码生成器

	string str_FileName;//源程序文件名
	string str_LexFileName;//源程序词法分析文件名
	
	string str_ErrFileName;//源程序语法错误文件名
	string str_FilePath;//文件路径

	ifstream if_InFile;//输入文件
	ofstream of_ErrFile;//输出文件和错误文件
	ofstream of_AsmFile;//汇编语言文件

	vector<Token> v_Tokens;//属性字流
	vector<Token> v_ErrTokens;
	vector<string> v_Err;
	bool b_EOFFlag;//文件读取结束

	bool b_EndFlag;//属性读取结束
	int i_CurToken;//当前读取Token
	Token tok_CurToken;//当前Token

	stack<char> s_AnalyzingStack;//分析栈
	

	
	/**
	 * 从词法分析文件中拿到属性字
	 */
	void _GetTokens();
	/**
	 * 输出属性字
	 */
	void _PrintTokens();
	/**
	 * 分析主方法
	 */
	bool _Analyze();
	/**
	 * 获取非终结符对应的数字，用于分析表
	 * @param VN 非终结符字段
	 * @return 对应的数字
	 */
	int _GetVnInt(char VN);
	/**
	 * 返回指定属性字对应的字符
	 */
	char _GetTokenChar(Token tok);
	/**
	 * 报错
	 * @param errorcode 错误代码
	 */
	void _SyntexError(int errorCode, Token tok);
	/**
	 * 错误
	 */
	void _ErrOutput();
};

