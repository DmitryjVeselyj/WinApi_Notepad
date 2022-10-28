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
    inBuff* buffer;//входной буффер(содержит оригинальный текст)
    mView* view;//вид(метрика шрифта, смещение по тексту, ширина, высота клиентской области)
    outBuf* outBuffer;//буффер, в котором хранятся указатели на начала строк форматированного текста
}modelData;
