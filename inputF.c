#include"inputF.h"
#include<stdio.h>
#include<stdlib.h>

/*
void initBuff(inBuff** buffer) - инициализация структуры
inBuff** buffer - указатель на указатель структуры
На выходе: ничего(но меняем (*buffer))
*/
void initBuff(inBuff** buffer) {
    (*buffer) = malloc(sizeof(inBuff));
    if(!(*buffer)) {
        errMessage("can't allocate memory for buff\n");
        return;
    }
    (*buffer)->textSize = 0;
    (*buffer)->text = NULL;
    (*buffer)->posSize = 0;
    (*buffer)->pos = NULL;
}

/*
void destroyBuff(inBuff* buffer) - уничтожение структуры
inBuff** buffer - указатель на указатель структуры
На выходе: ничего(но освобождаем память, выделенную под поля и структуру)
*/
void destroyBuff(inBuff* buffer) {
    if(!buffer)
        errMessage("null ptr\n");
    free(buffer->pos);
    free(buffer->text);
    free(buffer);
}

/*
void readFile(char* name, inBuff* buffer) - чтение файла
char* name - имя файла
inBuff* buffer - указатель на структуру
На выходе: ничего(записываем(соотвественно и выделяем паямть) в поля структуры текст, размер, индексы начала строк)
*/
void readFile(char* name, inBuff* buffer) {
    FILE* fl = fopen(name, "r");
    if(!fl) {
        errMessage("can't open file\n");
        return;
    }
    fseek(fl, 0, SEEK_END);
    buffer->textSize = ftell(fl);
    fseek(fl, 0, SEEK_SET);
    if(buffer->text != NULL) {
        free(buffer->text);
    }

    buffer->text = calloc(sizeof(char), (int)(buffer->textSize + 1));

    if(!buffer->text) {
        errMessage("can't allocate memory\n");
        return;
    }
    buffer->textSize = fread(buffer->text, sizeof(char), buffer->textSize, fl);
    buffer->text[buffer->textSize] = 0;
    buffer->posSize = 2;
    int i = 0;
    for(i = 0 ; i < buffer->textSize; i++) {
        if(buffer->text[i] == '\n') {
            buffer->posSize++;
        }
    }
    if(buffer->pos != NULL) {
        free(buffer->pos);
    }
    buffer->pos = malloc(sizeof(unsigned int) * buffer->posSize);
    if(!buffer->pos) {
        free(buffer->text);
        errMessage("can't malloc memory\n");
        return;
    }

    buffer->pos[0] = 0;
    int k = 1;
    for(i = 0, k = 1 ; i < buffer->textSize; i++) {
        if(buffer->text[i] == '\n') {
            buffer->pos[k++] = i  + 1;
        }
    }
    buffer->pos[buffer->posSize - 1] = buffer->textSize + 1;
    fclose(fl);
}

/*
unsigned int maxStrLength(inBuff* buffer) - определение максимальной длины строки
inBuff* buffer - указатель на структуру
На выходе: максимальная длина строки
*/
unsigned int maxStrLength(inBuff* buffer) {
    unsigned int maxL= 0;
    unsigned int i = 0;
    for(i = 0 ; i < (int)(buffer->posSize - 1); i++) {
        if(maxL < buffer->pos[i + 1] - buffer->pos[i]) {
            maxL = buffer->pos[i + 1] - buffer->pos[i];
        }

    }
    return maxL;
}
