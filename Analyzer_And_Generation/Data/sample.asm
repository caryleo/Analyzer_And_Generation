STACKSG SEGMENT STACK 'S'
  DW 32 DUP(?)
STACKSG ENDS

DATA SEGMENT
  D_0 DW ?
  D_1 DW ?
  D_2 DW ?
DATA ENDS

CODE SEGMENT
  ASSUME CS:CODE, DS:DATA, SS:STACKSG
MAIN PROC FAR
  MOV AX, DATA
  MOV DS, AX
  ;��ֵ���
  MOV DX, 10
  PUSH DX
  POP AX
  MOV D_0, AX
  ;��ֵ������
  ;��ֵ���
  MOV DX, -6
  PUSH DX
  POP AX
  MOV D_1, AX
  ;��ֵ������
L_S0:  ;ѭ����ʼ
  ;�������ʽ
  MOV DX, D_1
  PUSH DX
  MOV DX, D_0
  PUSH DX
  POP BX
  POP AX
  CMP AX, BX
  JNL L_E0
  ;�������ʽ����
  ;��ֵ���
  MOV DX, D_1
  PUSH DX
  MOV DX, 3
  PUSH DX
  POP BX
  POP AX
  ADD AX, BX
  PUSH AX
  POP AX
  MOV D_1, AX
  ;��ֵ������
  JMP L_S0
L_E0:  ;ѭ�������
L_S1:  ;ѭ����ʼ
  ;�������ʽ
  MOV DX, 200
  PUSH DX
  MOV DX, D_0
  PUSH DX
  POP BX
  POP AX
  CMP AX, BX
  JNG L_E1
  ;�������ʽ����
  ;��ֵ���
  MOV DX, D_0
  PUSH DX
  MOV DX, D_1
  PUSH DX
  MOV DX, 3
  PUSH DX
  POP BX
  POP AX
  XOR DX, DX
  IMUL BX
  PUSH AX
  POP BX
  POP AX
  ADD AX, BX
  PUSH AX
  MOV DX, -7
  PUSH DX
  POP BX
  POP AX
  SUB AX, BX
  PUSH AX
  POP AX
  MOV D_0, AX
  ;��ֵ������
  JMP L_S1
L_E1:  ;ѭ�������
  ;��ֵ���
  MOV DX, D_0
  PUSH DX
  MOV DX, 5
  PUSH DX
  POP BX
  POP AX
  XOR DX, DX
  IDIV BX
  PUSH AX
  MOV DX, 5
  PUSH DX
  MOV DX, D_1
  PUSH DX
  POP BX
  POP AX
  XOR DX, DX
  IMUL BX
  PUSH AX
  POP BX
  POP AX
  ADD AX, BX
  PUSH AX
  MOV DX, 8
  PUSH DX
  POP BX
  POP AX
  SUB AX, BX
  PUSH AX
  MOV DX, 6
  PUSH DX
  POP BX
  POP AX
  ADD AX, BX
  PUSH AX
  POP AX
  MOV D_2, AX
  ;��ֵ������
  MOV AX, 4C00H
  INT 21H
MAIN ENDP
CODE ENDS
END MAIN

