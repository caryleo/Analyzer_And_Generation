//
// Created by Gary on 2018.7.4.
//
#include "stdafx.h"
#include "Token.h"

void Token::Set(e_Attributes ea, e_KeywordKind ek, string str, Position stp, Position edp) {
    ea_Type = ea;
    ek_kind = ek;
    str_RealString = str;
    pos_StartPos = stp;
    pos_EndPos = edp;
}

e_Attributes Token::getEa_Type() const {
    return ea_Type;
}

void Token::setEa_Type(e_Attributes ea_Type) {
    Token::ea_Type = ea_Type;
}

e_KeywordKind Token::getEk_kind() const {
    return ek_kind;
}

void Token::setEk_kind(e_KeywordKind ek_kind) {
    Token::ek_kind = ek_kind;
}

string Token::getStr_RealString() {
    return str_RealString;
}

void Token::setStr_RealString(const string &str_RealString) {
    Token::str_RealString = str_RealString;
}

const Position &Token::getPos_StartPos() const {
    return pos_StartPos;
}

void Token::setPos_StartPos(const Position &pos_StartPos) {
    Token::pos_StartPos = pos_StartPos;
}

Position Token::getPos_EndPos() {
    return pos_EndPos;
}

void Token::setPos_EndPos(const Position &pos_EndPos) {
    Token::pos_EndPos = pos_EndPos;
}

Token::Token(e_Attributes ea, e_KeywordKind ek, string str, Position stp, Position edp) {
    ea_Type = ea;
    ek_kind = ek;
    str_RealString = str;
    pos_StartPos = stp;
    pos_EndPos = edp;
}

Token::~Token() {

}

Token::Token() {}
