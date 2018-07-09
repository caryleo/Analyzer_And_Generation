//
// Created by Gary on 2018.7.4.
// ��������
//

#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H
#include "Constants.h"
#include "Position.h"
#include <string>

using namespace std;

class Token {
public:
    /**
     * ��������������
     * @param ea type����
     * @param ek kind��������
     * @param str ���ڳ����ͱ�ʾ���ľ������ݣ�������Ǳ�������
     * @param stp ���ص�λ��
     */
    void Set(e_Attributes ea, e_KeywordKind ek, string str, Position stp, Position edp);

    Token(e_Attributes ea, e_KeywordKind ek, string str, Position stp, Position edp);

    Token();

    ~Token();

    e_Attributes getEa_Type() const;

    void setEa_Type(e_Attributes ea_Type);

    e_KeywordKind getEk_kind() const;

    void setEk_kind(e_KeywordKind ek_kind);

    string getStr_RealString();

    void setStr_RealString(const string &str_RealString);

    const Position &getPos_StartPos() const;

    void setPos_StartPos(const Position &pos_StartPos);

    Position getPos_EndPos();

    void setPos_EndPos(const Position &pos_EndPos);

private:
    e_Attributes ea_Type;
    e_KeywordKind ek_kind;
    string str_RealString;
    Position pos_StartPos;
    Position pos_EndPos;
};


#endif //SCANNER_TOKEN_H
