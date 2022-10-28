#pragma once
#include"errors.h"
#include"inputF.h"
#define SCROLL 0
#define FORMAT 1
#define MAX_SCROLL_POS 65535
typedef struct{
    HFONT hfont;
    unsigned int cxChar, cyChar;//������ � ������ �������
    COLORREF bkColor;//���� ���� ������
    COLORREF textColor;//���� ������
}mFont;//��������� ��������� � "����������" reader�

typedef struct {
    unsigned int cxClient, cyClient;//������ � ������ ���������� �������
    unsigned int xOffset, yOffset;//�������� �� ������, ������������ ��� �������
    unsigned int mode;//�����
    unsigned int VscrollMax, HscrollMax;//������������ ������� �������
    int wheelDelta;//����������, ������������ ��� ��������� ��������� ������� ����
    double kf, kfh;//������������, ������������ ��� ���������� ��������� ������
    unsigned int maxStrLeng, numlinesOnScr;//������������ ����� ������ � ���������� �����
    unsigned int oldWidth, oldHeigth;//������ ������ � ������
    unsigned int isSwitchMode;//����, ������������ ��������� ������
    unsigned int lastIndx;//������ ������������ ������
    unsigned int lastSubStr, lastCntSub;//������ ��������� ��������� � ���������� ��������
    mFont* font;
}mView;

/*
void viewInit(mView** view) - ������������� ���������
mView** view - ��������� �� ��������� ���������
�� ������: ������(�� �������� ������ ��� ���������, ���� ���������)
*/
void viewInit(mView** view);

/*
void viewResize(mView* view, int buffNumLines, int outBufNumlines, int maxStrLen)- �������� �������� ����� ���������
mView* view - ��������� �� ���������
unsigned int buffNumLines - ���������� ����� � ��������� ������
unsigned int outBufNumlines - ���������� ����� � ������ � ������ ��������������
unsigned int maxStrLen - ������������ ����� ������
�� ������: ������(��������� � ����������� ������)
*/
void viewResize(mView* view, unsigned int buffNumLines,unsigned int outBufNumlines);


/*
void setStyle(HDC hdc, mFont* font)- ��������� �����
HDC hdc - ��������� ��������� ����������
mFont* font - ��������� �� ���������, ��������� �� �������
�� ������: ������(��������� � ���������� ������)
*/
void setStyle(HDC hdc, mFont* font);

/*
void viewDestroy(mView* view) - ����������� ���������
mView* view - ��������� �� ���������
�� ������: ������(�� ������� ������ (���� ��������� � ���� ���������))
*/
void viewDestroy(mView* view);


int maxx(int x, int y);//�������� �� ���� ����������(���������� ������������� ��������)
int minn(int x, int y);//������� �� ���� ����������(���������� ������������� �������)

