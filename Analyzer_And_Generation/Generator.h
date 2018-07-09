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
	 * ��������
	 */
	void Generate(char c, int pos);
	/**
	 * ��ʼ��
	 */
	void Init(string fileName);
	void Close();
private:
	string str_AsmFileName;//��������ļ���
	string str_FilePath;//�ļ�·��
	string str_OutFileName;//Դ�����﷨�����ļ���

	ofstream of_AsmFile;//����������ļ�
	ofstream of_OutFile;//�﷨��������ļ�

	string str_StackSegment;//��ջ��
	string str_DataSegment;//���ݶ�
	string str_CodeSegment;//�����
	string str_Data;
	string str_Label;

	bool b_Loop;//ѭ��״̬��
	int i_Con;//����״̬��
	bool b_Ass;//��ֵ��ֵ״̬��
	bool b_Exp;//��ֵ��ֵ״̬��

	stack<Token> s_OPD;
	stack<Token> s_OPR;
	vector<Token> v_EXP;
};

