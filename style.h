#pragma once
#include"errors.h"
#include"inputF.h"
#define SCROLL 0
#define FORMAT 1
#define MAX_SCROLL_POS 65535
typedef struct{
    HFONT hfont;
    unsigned int cxChar, cyChar;//ширина и высота символа
    COLORREF bkColor;//цвет фона текста
    COLORREF textColor;//цвет текста
}mFont;//структура связанная с "косметикой" readerа

typedef struct {
    unsigned int cxClient, cyClient;//ширина и высота клиентской области
    unsigned int xOffset, yOffset;//смещение по тексту, используемое для скролла
    unsigned int mode;//режим
    unsigned int VscrollMax, HscrollMax;//максимальные позиции скролла
    int wheelDelta;//переменная, используемая для обработки прокрутки колёсика мыши
    double kf, kfh;//коэффициенты, используемые для правильной прокрутки текста
    unsigned int maxStrLeng, numlinesOnScr;//максимальная длина строки и количество строк
    unsigned int oldWidth, oldHeigth;//старая ширина и высота
    unsigned int isSwitchMode;//флаг, показывающий изменение режима
    unsigned int lastIndx;//индекс инвариантной строки
    unsigned int lastSubStr, lastCntSub;//индекс последней подстроки и количество подстрок
    mFont* font;
}mView;

/*
void viewInit(mView** view) - инициализация структуры
mView** view - указатель на указатель структуры
На выходе: ничего(но выделяем память под структуры, поля структуры)
*/
void viewInit(mView** view);

/*
void viewResize(mView* view, int buffNumLines, int outBufNumlines, int maxStrLen)- пересчёт значений полей структуры
mView* view - указатель на структуру
unsigned int buffNumLines - количество строк в оригинале текста
unsigned int outBufNumlines - количество строк в тексте в режиме форматирования
unsigned int maxStrLen - максимальная длина строки
На выходе: ничего(структура с измененными полями)
*/
void viewResize(mView* view, unsigned int buffNumLines,unsigned int outBufNumlines);


/*
void setStyle(HDC hdc, mFont* font)- установка стиля
HDC hdc - описатель контекста устройства
mFont* font - указатель на структуру, связанную со шрифтом
На выходе: ничего(структура с изменёнными полями)
*/
void setStyle(HDC hdc, mFont* font);

/*
void viewDestroy(mView* view) - уничтожение структуры
mView* view - указатель на структуру
На выходе: ничего(но очищаем память (поля структуры и сама структура))
*/
void viewDestroy(mView* view);


int maxx(int x, int y);//максимум из двух переменных(возвращаем соотвественно максимум)
int minn(int x, int y);//минимум из двух переменных(вовзращаем соотвественно минимум)

