//
// Created by Gary on 2018.7.4.
//
#include "stdafx.h"
#include "Position.h"

void Position::Set(int x, int y) {
    i_Line = x;
    i_Col = y;
}

Position::Position(int x, int y) {
    i_Line = x;
    i_Col = y;
}

Position::~Position() {

}

Position::Position() {}

int Position::getI_Line() const {
    return i_Line;
}

void Position::setI_Line(int i_Line) {
    Position::i_Line = i_Line;
}

int Position::getI_Col() const {
    return i_Col;
}

void Position::setI_Col(int i_Col) {
    Position::i_Col = i_Col;
}
