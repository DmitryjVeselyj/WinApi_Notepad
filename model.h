#pragma once

#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <tchar.h>

#include"inputF.h"
#include"style.h"
#include"outScr.h"
#include"menu.h"
#include"errors.h"


typedef struct{
    inBuff* buffer;//������� ������(�������� ������������ �����)
    mView* view;//���(������� ������, �������� �� ������, ������, ������ ���������� �������)
    outBuf* outBuffer;//������, � ������� �������� ��������� �� ������ ����� ���������������� ������
}modelData;
