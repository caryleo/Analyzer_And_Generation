//
// Created by Gary on 2018.7.4.
// 属性字类
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
     * 设置属性字属性
     * @param ea type类型
     * @param ek kind具体类型
     * @param str 对于常量和表示符的具体内容，否则就是保留字项
     * @param stp 词素的位置
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
