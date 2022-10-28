#include"style.h"
#include <stdio.h>
#include <stdlib.h>

/*
void viewInit(mView** view) - инициализация структуры
mView** view - указатель на указатель структуры
На выходе: ничего(но выделяем память под структуры, поля структуры)
*/
void viewInit(mView** view) {
    (*view) = malloc(sizeof(mView));
    if(!(*view)) {
        errMessage("can't malloc for view\n");
        return;
    }
    (*view)->font = malloc(sizeof(mFont));
    if(!(*view)->font) {
        free(view);
        errMessage("can't malloc for font\n");
        return;
    }
    (*view)->cxClient = 0;
    (*view)->cyClient = 0;
    (*view)->xOffset = 0;
    (*view)->yOffset = 0;
    (*view)->HscrollMax =0;
    (*view)->kf = 1;
    (*view)->kfh = 1;
    (*view)->VscrollMax=0;
    (*view)->wheelDelta = 0;
    (*view)->mode = FORMAT;

    (*view)->font->cxChar =0;
    (*view)->font->cyChar =0;

    (*view)->maxStrLeng = 0;
    (*view)->numlinesOnScr =0;
    (*view)->isSwitchMode = 1;
    (*view)->lastIndx = 0;
    (*view)->lastSubStr=0;
    (*view)->lastCntSub = 0;
    (*view)->oldHeigth = 0;
    (*view)->oldWidth = 0;
}

/*
void viewDestroy(mView* view) - уничтожение структуры
mView* view - указатель на структуру
На выходе: ничего(но очищаем память (поля структуры и сама структура))
*/
void viewDestroy(mView* view) {
    DeleteObject(view->font->hfont);
    free(view->font);
    free(view);
}

/*
void setStyle(HDC hdc, mFont* font)- установка стиля
HDC hdc - описатель контекста устройства
mFont* font - указатель на структуру, связанную со шрифтом
На выходе: ничего(структура с изменёнными полями)
*/
void setStyle(HDC hdc, mFont* font) {
    TEXTMETRIC tm;
    font->bkColor =RGB(255,255,255);
    font->textColor = RGB(0, 0, 0);
    font->hfont = CreateFont(16,0,0,0,0,FALSE,FALSE,FALSE,DEFAULT_CHARSET,0,0,0, FIXED_PITCH,"Consolas");
    SetBkColor(hdc,font->bkColor);
    SetTextColor(hdc,font->textColor);
    SelectObject(hdc, font->hfont);

    GetTextMetrics(hdc, &tm);
    font->cxChar = tm.tmAveCharWidth;
    font->cyChar = tm.tmHeight;
}

/*
void viewResize(mView* view, int buffNumLines, int outBufNumlines, int maxStrLen)- пересчёт значений полей структуры
mView* view - указатель на структуру
unsigned int buffNumLines - количество строк в оригинале текста
unsigned int outBufNumlines - количество строк в тексте в режиме форматирования
unsigned int maxStrLen - максимальная длина строки
На выходе: ничего(структура с измененными полями)
*/
void viewResize(mView* view, unsigned int buffNumLines,unsigned int outBufNumlines) {
    unsigned int heightScr= view->cyClient/ view->font->cyChar;
    unsigned int widthScr = view->cxClient/ view->font->cxChar;
    view->numlinesOnScr = outBufNumlines;
    if(view->mode == FORMAT) {
        if((int)(outBufNumlines - heightScr ) >= MAX_SCROLL_POS) {
            view->VscrollMax = MAX_SCROLL_POS ;
            view->kf = (double)(outBufNumlines - heightScr) / view->VscrollMax ;//определяем коэффициент, который используется для случая , когда строк >65536
        } else {
            view->VscrollMax = maxx(outBufNumlines - heightScr, 0);
            view->kf = 1;
        }
    } else {
        if((int)(buffNumLines - heightScr) >= MAX_SCROLL_POS) {
            view->VscrollMax = MAX_SCROLL_POS ;
            view->kf = (double)(buffNumLines - heightScr) / view->VscrollMax ;
        } else {
            view->VscrollMax = maxx(buffNumLines - heightScr, 0);
            view->kf= 1;
        }

        if((int)(view->maxStrLeng - widthScr ) >=MAX_SCROLL_POS) {
            view->HscrollMax = MAX_SCROLL_POS;
            view->kfh = (double)(view->maxStrLeng  - widthScr ) / view->HscrollMax ;
        } else {
            view->HscrollMax = maxx(0, view->maxStrLeng  - widthScr );
            view->kfh = 1;
        }
    }

    view->xOffset = minn(view->xOffset, view->HscrollMax * view->kfh);
    view->yOffset= minn(view->yOffset, view->VscrollMax * view->kf);
}

int maxx(int x, int y) { //максимум из двух переменных
    return x > y ? x : y;
}

int minn(int x, int y) { //минимум из двух переменных
    return x < y ? x : y;
}

