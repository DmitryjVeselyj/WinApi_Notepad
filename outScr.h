#pragma once
#include"errors.h"
#include"inputF.h"
#include"style.h"

typedef struct{
    unsigned int numPtr;//������ ������� ��������
    unsigned int* strPos;//������ �������� ������ �����(������� ���������� � ������ ��������������)
}outBuf;

/*
void outBufInit(outBuf** outBuffer) - ������������� ���������, ������������� �� �������� �������� ��������� �� ������
�� �����:
outBuf** outBuffer - ��������� �� ��������� ���������
�� ������: ������(�� �������� ������ ��� ���������)
*/
void outBufInit(outBuf** outBuffer);

/*
void outBufDestoy(outBuf** outBuffer) - ����������� ���������
�� �����:
outBuf* outBuffer - ��������� �� ���������
�� ������: ������(������� ������, ���������� ��� ��������� � � ����)
*/
void outBufDestroy(outBuf* outBuffer);

/*
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view) - �������� �������� ����� ���������
�� �����:
outBuf** outBuffer - ��������� �� ��������� ���������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������: ������(�� ������� ������ ��� ���� ���������, ������� ���������� ��� �������)
*/
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view);

/*
void printText(HDC hdc, outBuf* outBuffer,inBuff* buffer, mView* view, unsigned int iPaintBeg,unsigned int iPaintEnd, unsigned int iPaintLeft, unsigned int iPaintRight);
� ���� ������� ��� ��� ��������� �����
HDC hdc - ��������� ��������� ����������
outBuf* outBuffer - ��������� , �������� ��������� �� ������ ����� � ��������������� ������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
unsigned int iPaintBeg- ������ ������, � ������� �������� ��������
unsigned int iPaintEnd- ������ ������, �� ������� �������
unsigned int iPaintLeft- ������ �������, � �������� �������� ��������(�� ��� �������������� �������)
unsigned int iPaintRight- ������ �������, �� �������� ��������(�� ��� �������������� �������)
�� ������: ������(��� ���� ������� �����)
*/
void printText(HDC hdc, outBuf* outBuffer,inBuff* buffer, mView* view, unsigned int iPaintBeg,unsigned int iPaintEnd, unsigned int iPaintLeft, unsigned int iPaintRight);

/*
int numlinesScr(inBuff* buffer, mView* view) - ������� ���������� ����� � ������ ��������������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������: ����� �����
*/
unsigned int numlinesScr(inBuff* buffer, mView* view);

/*
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view) - ���������� ������������ ������(������������ ��� ��������� �������)
outBuf* outBuffer - ��������� , �������� ��������� �� ������ ����� � ��������������� ������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������:
����� ������
*/
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view);

/*
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view) - ���������� �������� ��� ��������� ������� ������
outBuf* outBuffer - ��������� , �������� ��������� �� ������ ����� � ��������������� ������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������:
��������
*/
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view);

/*
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth) - ���������� ���������� �������� � ������
inBuff* buffer - ���������, ���������� ������������ �����
unsigned int lineInd - ����� ������
unsigned int wth - ������ ���������� �������
�� ������:  ���������� �������� � ������
*/
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth);
