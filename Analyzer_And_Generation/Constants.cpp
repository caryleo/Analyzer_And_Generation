//
// Created by Gary on 2018.7.4.
//
#include "stdafx.h"
#include "Constants.h"


//关键词对应的char数组
char ca_Keyword[100][13] = {
        "abstract", "boolean", "break",
        "byte", "case", "catch", "char",
        "class", "const", "continue",
        "default", "do", "double", "else",
        "extends", "false", "final", "finally",
        "float", "for", "goto", "if",
        "implements", "import", "instanceof",
        "int", "interface", "long", "native",
        "new", "null", "package", "private",
        "protected", "public", "return", "short",
        "static", "super", "switch", "synchronized",
        "this", "throw", "throws", "transient",
        "true", "try", "void", "volatile", "while",
        "{", "}", "[", "]", "(", ")", ",", ".", ";",
        "=", "+", "-", "*", "/", "%",
        ">", ">=", "==", "!=", "<", "<=",
        "&&", "||", "!",
        "&", "|", "^", "~",
        "+=", "-=", "*=", "/=", "%=",
        "++", "--",
        "&=", "|=", "^=",
        "<<", ">>", ">>>",
        "<<=", ">>=", ">>>=",
        "?", ":"
};

//等值替代：Sw-A Er-B Er'-C S-D Vc-E Ex-F Ex'-G P-H while-I ID-J INT-K epsilon-M
string sa_Syntex[15] = {
	"I(B)D",
	"EC",
	"<E",
	">E",
	"J=F;",
	"J",
	"K",
	"EG",
	"HF",
	"M",
	"+",
	"-",
	"*",
	"/"
};

//对应关系：
//行：Sw-0 Er-1 Er'-2 S-3 Vc-4 Ex-5 Ex'-6 P-7
//列：while-0 ID-1 <-2 >-3 INT-4 +-5 --6 *-7 /-8 ;-9
int ia_LLONE[9][11] = {
	 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60,
	61,  1, 61, 61,  1, 61, 61, 61, 61, 61, 60,
	62, 62,  2,  3, 62, 62, 62, 62, 62, 62, 60,
	-1,  4, -1, -1, -1, -1, -1, -1, -1, -1, 60,
	63,  5, 63, 63,  6, 63, 63, 63, 63, 63, 60,
	64,  7, 64, 64,  7, 64, 64, 64, 64, 64, 60,
	65, 65, 65, 65, 65,  8,  8,  8,  8,  9, 60,
	66, 66, 66, 66, 66, 10, 11, 12, 13, 66, 60,
	60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60
};
