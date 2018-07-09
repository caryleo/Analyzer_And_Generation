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
	 * ��ʼ������
	 * @param fileName �ļ���
	 */
	void Init(string fileName);
	/**
	 * ִ�к���
	 */
	void Execute();
private:
	Generator *g_Gen;//����������

	string str_FileName;//Դ�����ļ���
	string str_LexFileName;//Դ����ʷ������ļ���
	
	string str_ErrFileName;//Դ�����﷨�����ļ���
	string str_FilePath;//�ļ�·��

	ifstream if_InFile;//�����ļ�
	ofstream of_ErrFile;//����ļ��ʹ����ļ�
	ofstream of_AsmFile;//��������ļ�

	vector<Token> v_Tokens;//��������
	vector<Token> v_ErrTokens;
	vector<string> v_Err;
	bool b_EOFFlag;//�ļ���ȡ����

	bool b_EndFlag;//���Զ�ȡ����
	int i_CurToken;//��ǰ��ȡToken
	Token tok_CurToken;//��ǰToken

	stack<char> s_AnalyzingStack;//����ջ
	

	
	/**
	 * �Ӵʷ������ļ����õ�������
	 */
	void _GetTokens();
	/**
	 * ���������
	 */
	void _PrintTokens();
	/**
	 * ����������
	 */
	bool _Analyze();
	/**
	 * ��ȡ���ս����Ӧ�����֣����ڷ�����
	 * @param VN ���ս���ֶ�
	 * @return ��Ӧ������
	 */
	int _GetVnInt(char VN);
	/**
	 * ����ָ�������ֶ�Ӧ���ַ�
	 */
	char _GetTokenChar(Token tok);
	/**
	 * ����
	 * @param errorcode �������
	 */
	void _SyntexError(int errorCode, Token tok);
	/**
	 * ����
	 */
	void _ErrOutput();
};

