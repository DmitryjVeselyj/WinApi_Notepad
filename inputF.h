#pragma once
#include"errors.h"
typedef struct{
    char* text;//�������� ������
    unsigned int textSize;//������ ������
    unsigned int* pos;//������ ��������, � ������� ���������� ������
    unsigned int posSize;//������ ������� ��������
}inBuff;


/*
void initBuff(inBuff** buffer) - ������������� ���������
inBuff** buffer - ��������� �� ��������� ���������
�� ������: ������(�� ������ (*buffer))
*/
void initBuff(inBuff** buffer);

/*
void destroyBuff(inBuff* buffer) - ����������� ���������
inBuff** buffer - ��������� �� ��������� ���������
�� ������: ������(�� ����������� ������, ���������� ��� ���� � ���������)
*/
void destroyBuff(inBuff* buffer);

/*
void readFile(char* name, inBuff* buffer) - ������ �����
char* name - ��� �����
inBuff* buffer - ��������� �� ���������
�� ������: ������(����������(������������� � �������� ������) � ���� ��������� �����, ������, ������� ������ �����)
*/
void readFile(char* name, inBuff* buffer);

/*
unsigned int maxStrLength(inBuff* buffer) - ����������� ������������ ����� ������
inBuff* buffer - ��������� �� ���������
�� ������: ������������ ����� ������
*/
unsigned int maxStrLength(inBuff* buffer);

