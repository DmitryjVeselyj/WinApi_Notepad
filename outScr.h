#pragma once
#include"errors.h"
#include"inputF.h"
#include"style.h"

typedef struct{
    unsigned int numPtr;//размер массива индексов
    unsigned int* strPos;//массив индексов начала строк(которые получаются в режиме форматирования)
}outBuf;

/*
void outBufInit(outBuf** outBuffer) - инициализация структуры, ответственной за хранение массивов указателй на строки
На входе:
outBuf** outBuffer - указатель на указатель структуры
На выходе: ничего(но выделяем память под структуру)
*/
void outBufInit(outBuf** outBuffer);

/*
void outBufDestoy(outBuf** outBuffer) - уничтожение структуры
На входе:
outBuf* outBuffer - указатель на структуру
На выходе: ничего(очищаем память, выделенную под структуру и её поля)
*/
void outBufDestroy(outBuf* outBuffer);

/*
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view) - пересчёт значений полей структуры
На входе:
outBuf** outBuffer - указатель на указатель структуры
inBuff* buffer - структура, содержащая оригинальный текст
mView* view - модель представления
На выходе: ничего(но выделям память под поля структуры, которые изменяются при ресайзе)
*/
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view);

/*
void printText(HDC hdc, outBuf* outBuffer,inBuff* buffer, mView* view, unsigned int iPaintBeg,unsigned int iPaintEnd, unsigned int iPaintLeft, unsigned int iPaintRight);
В этой функции как раз выводится текст
HDC hdc - описатель контекста устройства
outBuf* outBuffer - структура , хранящая указатели на начала строк в форматированном режиме
inBuff* buffer - структура, содержащая оригинальный текст
mView* view - модель представления
unsigned int iPaintBeg- индекс строки, с которой начинаем принтить
unsigned int iPaintEnd- индекс строки, до которой принтим
unsigned int iPaintLeft- индекс символа, с которого начинаем принтить(те при горизонтальном скролле)
unsigned int iPaintRight- индекс символа, до которого принтими(те при горизонтальном скролле)
На выходе: ничего(при этом выводим текст)
*/
void printText(HDC hdc, outBuf* outBuffer,inBuff* buffer, mView* view, unsigned int iPaintBeg,unsigned int iPaintEnd, unsigned int iPaintLeft, unsigned int iPaintRight);

/*
int numlinesScr(inBuff* buffer, mView* view) - подсчёт количества строк в режиме форматирования
inBuff* buffer - структура, содержащая оригинальный текст
mView* view - модель представления
На выходе: число строк
*/
unsigned int numlinesScr(inBuff* buffer, mView* view);

/*
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view) - определяем инвариантную строку(используется при изменении режимов)
outBuf* outBuffer - структура , хранящая указатели на начала строк в форматированном режиме
inBuff* buffer - структура, содержащая оригинальный текст
mView* view - модель представления
На выходе:
номер строки
*/
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view);

/*
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view) - определяем смещение при изменении размера экрана
outBuf* outBuffer - структура , хранящая указатели на начала строк в форматированном режиме
inBuff* buffer - структура, содержащая оригинальный текст
mView* view - модель представления
На выходе:
Смещение
*/
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view);

/*
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth) - определяем количество подстрок у строки
inBuff* buffer - структура, содержащая оригинальный текст
unsigned int lineInd - номер строки
unsigned int wth - ширина клиентской области
На выходе:  количество подстрок у строки
*/
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth);
