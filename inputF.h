#pragma once
#include"errors.h"
typedef struct{
    char* text;//оригинал текста
    unsigned int textSize;//размер текста
    unsigned int* pos;//массив индексов, с которых начинаются строки
    unsigned int posSize;//размер массива индексов
}inBuff;


/*
void initBuff(inBuff** buffer) - инициализация структуры
inBuff** buffer - указатель на указатель структуры
На выходе: ничего(но меняем (*buffer))
*/
void initBuff(inBuff** buffer);

/*
void destroyBuff(inBuff* buffer) - уничтожение структуры
inBuff** buffer - указатель на указатель структуры
На выходе: ничего(но освобождаем память, выделенную под поля и структуру)
*/
void destroyBuff(inBuff* buffer);

/*
void readFile(char* name, inBuff* buffer) - чтение файла
char* name - имя файла
inBuff* buffer - указатель на структуру
На выходе: ничего(записываем(соотвественно и выделяем паямть) в поля структуры текст, размер, индексы начала строк)
*/
void readFile(char* name, inBuff* buffer);

/*
unsigned int maxStrLength(inBuff* buffer) - определение максимальной длины строки
inBuff* buffer - указатель на структуру
На выходе: максимальная длина строки
*/
unsigned int maxStrLength(inBuff* buffer);

