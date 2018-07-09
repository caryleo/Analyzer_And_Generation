#include "stdafx.h"
#include "Analyzer.h"


Analyzer::Analyzer()
{
}

Analyzer::Analyzer(Generator *gen)
{
	this->g_Gen = gen;
}


Analyzer::~Analyzer()
{
}

void Analyzer::Init(string fileName)
{
	str_FileName = fileName;
	str_LexFileName = fileName + "_Out.txt";
	
	str_ErrFileName = fileName + "_SynErr.txt";
	str_FilePath = ".\\Data\\";
	v_Tokens.clear();
	b_EOFFlag = false;
	b_EndFlag = false;
	i_CurToken = 0;
}

void Analyzer::Execute()
{
	string file = str_FilePath + str_LexFileName;
	cout << "���ڶ�ȡ��" << file << endl;
	if_InFile.open(file, ios::in);
	if (if_InFile.good())
	{
		
		string errFile = str_FilePath + str_ErrFileName;
		cout << "���ڷ��������Ժ�" << endl;

		of_ErrFile.open(errFile, ios::out);
		_GetTokens();
		g_Gen->v_Tokens = v_Tokens;
		cout << "��ȡ�ʷ��������" << endl;
		_PrintTokens();
		cout << "��ʼ�﷨����" << endl;
		int len = v_Tokens.size();
		bool flag = true;
		while (i_CurToken < len && flag)
		{
			flag = _Analyze();
		}
		_ErrOutput();
		of_ErrFile.close();
		g_Gen->End();
		g_Gen->Print();
		cout << "�������" << endl;
	}
	else
	{
		cerr << "�ļ���ȡ���󣡣��ļ�������޴��ļ���" << endl;
	}
	if_InFile.close();
}

void Analyzer::_GetTokens()
{
	string tmp;
	while (!if_InFile.eof())
	{
		tmp.clear();
		getline(if_InFile, tmp);
		if (tmp.size() == 0)
		{
			break;
		}
		char line[1024];
		Token tok;
		int countn = 0;
		int offset = 0;
		char ch;
		//��ʼ�к�
		ch = tmp.at(countn++);
		memset(line, 0, sizeof(line));
		while (ch != '\t') 
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int stLine = atoi(line);
		//��ʼ�к�
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		while (ch != '\t')
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int stCol = atoi(line);
		//��ֹ�к�
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		while (ch != '\t')
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int edLine = atoi(line);
		//��ֹ�к�
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		while (ch != '\t')
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int edCol = atoi(line);
		//����
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		while (ch != '\t')
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int t = atoi(line);
		e_Attributes type = e_Attributes(t);
		if (type == A_LEX_COMMENT || type == A_LEX_SPACE)
		{
			//�˵��ո��ע��
			continue;
		}
		//����
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		while (ch != '\t')
		{
			line[offset++] = ch;
			ch = tmp.at(countn++);
		}
		int k = atoi(line);
		e_KeywordKind kind = e_KeywordKind(k);
		//����
		ch = tmp.at(countn++);
		offset = 0;
		memset(line, 0, sizeof(line));
		int len = tmp.size();
		line[offset++] = ch;
		while (countn < len)
		{
			ch = tmp.at(countn++);
			line[offset++] = ch;
		}
		string str(line);
		tok.Set(type, kind, str, Position(stLine, stCol), Position(edLine, edCol));
		v_Tokens.push_back(tok);
	}
}

void Analyzer::_PrintTokens()
{
	int len = v_Tokens.size();
	for (int i = 0; i < len; ++i)
	{
		Token tok = v_Tokens[i];
		cout << tok.getPos_StartPos().getI_Line() << '\t';
		cout << tok.getPos_StartPos().getI_Col() << '\t';
		cout << tok.getPos_EndPos().getI_Line() << '\t';
		cout << tok.getPos_EndPos().getI_Col() << '\t';
		cout << tok.getEa_Type() << '\t';
		cout << tok.getEk_kind() << '\t';
		cout << tok.getStr_RealString() << '\n';
	}
}

bool Analyzer::_Analyze()
{
	Token tok = v_Tokens[i_CurToken];
	tok_CurToken = tok;
	//��ʼ������ջ
	while (!s_AnalyzingStack.empty())
	{
		s_AnalyzingStack.pop();
	}
	s_AnalyzingStack.push('#');
	if (tok.getEa_Type() == A_LEX_IDENTITY)
	{
		//��һ���������Ǳ�ʶ�������ʽ
		s_AnalyzingStack.push('D');
	}
	else if (tok.getEa_Type() == A_LEX_KEYWORD && tok.getEk_kind() == K_KEYWORD_WHILE)
	{
		//������whileѭ��
		s_AnalyzingStack.push('A');
	}
	else
	{
		//����
		_SyntexError(67, tok);
		return false;
	}
	//��ʼ����
	while (true)
	{
		char ch1 = s_AnalyzingStack.top();
		if (ch1 == '#' && s_AnalyzingStack.size() == 1)
		{
			//����ջ��ֻʣ#�������ɹ�
			return true;
		}
		else if (b_EndFlag)
		{
			//���������﷨�ṹ
			return false;
		}
		char ch2 = _GetTokenChar(tok);
		int i1 = _GetVnInt(ch1);
		int i2 = _GetVnInt(ch2);
		if (!(ch1 >= 'A' && ch1 <= 'H'))
		{
			//ջ���ַ���һ���ս��
			if (ch1 == ch2)
			{
				g_Gen->Generate(ch1, i_CurToken);
				//�ɵ���ջ����ָ�����
				s_AnalyzingStack.pop();
				i_CurToken++;
				if (i_CurToken == v_Tokens.size())
				{
					b_EndFlag = true;
				}
				else
				{
					tok = v_Tokens[i_CurToken];
				}
				
				continue;
			}
			else if (ch1 == 'M')
			{
				//ջ��Ϊepsilon��ֱ�ӵ���
				s_AnalyzingStack.pop();
				g_Gen->Generate(ch1, i_CurToken);
				continue;
			}
			else
			{
				return false;
			}
		}
		int r = ia_LLONE[i1][i2];
		if (r != -1 && r < 60)
		{
			//���ڿ���ƥ��
			g_Gen->Generate(ch1, i_CurToken);
			s_AnalyzingStack.pop();
			string tmp = sa_Syntex[r];
			int size = tmp.size();
			for (int i = size - 1; i >= 0; --i)
			{
				s_AnalyzingStack.push(tmp.at(i));
			}
		}
		else if (r >= 60)
		{
			_SyntexError(r, tok);
			return false;
		}
		else
		{
			//û�к��ʷ���ʽ��ֱ�ӳ���
			cerr << "�����﷨��������" << endl;
			break;
		}
	}
	return false;
}


int Analyzer::_GetVnInt(char VN)
{
	if (VN == 'A')
	{
		return 0;
	}
	else if (VN == 'B')
	{
		return 1;
	}
	else if (VN == 'C')
	{
		return 2;
	}
	else if (VN == 'D')
	{
		return 3;
	}
	else if (VN == 'E')
	{
		return 4;
	}
	else if (VN == 'F')
	{
		return 5;
	}
	else if (VN == 'G')
	{
		return 6;
	}
	else if (VN == 'H')
	{
		return 7;
	}
	else if (VN == 'I')
	{
		return 0;
	}
	else if (VN == 'J')
	{
		return 1;
	}
	else if (VN == '<')
	{
		return 2;
	}
	else if (VN == '>')
	{
		return 3;
	}
	else if (VN == 'K')
	{
		return 4;
	}
	else if (VN == '+')
	{
		return 5;
	}
	else if (VN == '-')
	{
		return 6;
	}
	else if (VN == '*')
	{
		return 7;
	}
	else if (VN == '/')
	{
		return 8;
	}
	else if (VN == ';')
	{
		return 9;
	}
	return -1;
}

char Analyzer::_GetTokenChar(Token tok)
{
	e_Attributes type = tok.getEa_Type();
	e_KeywordKind kind = tok.getEk_kind();
	if (type == A_LEX_IDENTITY)
	{
		return 'J';
	}
	else if (type == A_LEX_KEYWORD && kind == K_KEYWORD_WHILE)
	{
		return 'I';
	}
	else if (type == A_LEX_INT || (type == A_LEX_HIGH_PRIORITY && kind == K_CONSTANT_POSITIVE_INTEGER) || (type == A_LEX_HIGH_PRIORITY && kind == K_CONSTANT_NEGATIVE_INTEGER))
	{
		//��������������
		return 'K';
	}
	else if (type == A_LEX_COMPARE)
	{
		if (kind == K_OPR_LT)
		{
			return '<';
		}
		else
		{
			return '>';
		}
	}
	else if (type == A_LEX_ADD_SUB)
	{
		if (kind == K_OPR_ADD)
		{
			return '+';
		}
		else
		{
			return '-';
		}
	}
	else if (type == A_LEX_MUL_DIV_MOD)
	{
		if (kind == K_OPR_MUL)
		{
			return '*';
		}
		else
		{
			return '/';
		}
	}
	else if (type == A_LEX_ASSIGN && kind == K_OPR_ASSIGN)
	{
		return '=';
	}
	else if (type == A_LEX_BOUNDARY)
	{
		if (kind == K_BOUNDARY_PARENTHESES_LEFT)
		{
			return '(';
		}
		else
		{
			return ')';
		}
	}
	else
	{
		return ';';
	}
	return 0;
}

void Analyzer::_SyntexError(int errorCode, Token tok)
{
	v_ErrTokens.push_back(tok);
	string err;
	switch (errorCode)
	{
	case 60:
		err = "�Ƿ�����";
		break;
	case 61:
		err = "�ڴ�һ���Ƚ�ֵ";
		break;
	case 62:
		err = "�ڴ�һ���ȽϷ���<��>";
		break;
	case 63:
		err = "�������Ƿ�";
		break;
	case 64:
		err = "�ڴ�һ��������";
		break;
	case 65:
		err = "�ڴ�һ�����";
		break;
	case 66:
		err = "�Ƿ����";
		break;
	case 67:
		err = "�Ƿ������ʼ����";
		break;
	default:
		err = "λ�ô���";
		break;
	}
	v_Err.push_back(err);
}

void Analyzer::_ErrOutput() {
	int len = v_ErrTokens.size();
	if (len == 0)
	{
		cout << "---NO-ERROR---" << endl;
		of_ErrFile << "---NO-ERROR---" << endl;
		return;
	}
	for (int i = 0; i < len; ++i)
	{
		Token tmp = v_ErrTokens[i];
		string err = v_Err[i];
		Position pos = tmp.getPos_StartPos();
		of_ErrFile << "Error: " << err << endl;
		cerr << "Error: " << err << endl;
		of_ErrFile << "\tAt Line " << pos.getI_Line() << ", Column " << pos.getI_Col() << endl;
		cerr << "\tAt Line " << pos.getI_Line() << ", Column " << pos.getI_Col() << endl;
	}
}
