//
// Created by Gary on 2018.7.4.
// ����λ����
//

#ifndef SCANNER_POSITION_H
#define SCANNER_POSITION_H


class Position {
public:
    /**
     * ����λ��
     * @param x �к�
     * @param y �к�
     */
    void Set(int x, int y);
    Position(int x, int y);

    Position();

    int getI_Line() const;

    void setI_Line(int i_Line);

    int getI_Col() const;

    void setI_Col(int i_Col);

    ~Position();

private:
    int i_Line;
    int i_Col;
};


#endif //SCANNER_POSITION_H
