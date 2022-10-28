#include<stdio.h>
#include"outScr.h"
#include"style.h"
#include<stdlib.h>
#include<math.h>


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
void printText(HDC hdc, outBuf* outBuffer,inBuff* buffer,  mView* view, unsigned int iPaintBeg, unsigned int iPaintEnd, unsigned int iPaintLeft,unsigned int iPaintRight) {
    int width =0, iwidth = iPaintRight - iPaintLeft;
    int i = 0;
    if(buffer->text!= NULL) {
        for(i = iPaintBeg; i < iPaintEnd; i++) {
            if(view->mode == FORMAT) {
                width = (outBuffer)->strPos[i + 1]- (outBuffer)->strPos[i];
                if(buffer->text[(outBuffer)->strPos[i] + width - 1] == '\n' || buffer->text[(outBuffer)->strPos[i] + width - 1] == 0)
                    width--;
                TextOut(hdc, view->font->cxChar *(1 - view->xOffset), view->font->cyChar *( -view->yOffset + i ), buffer->text + (outBuffer)->strPos[i],width );
            } else {
                width = minn(iwidth, (int)buffer->pos[i+1]- buffer->pos[i]-iPaintLeft - 1);
                TextOut(hdc, view->font->cxChar *(1 - view->xOffset  + iPaintLeft), view->font->cyChar *(-view->yOffset  + i), buffer->text + buffer->pos[i] + iPaintLeft, width);
            }
        }
        view->lastIndx = view->yOffset;
    }
}

/*
unsigned int numlinesScr(inBuff* buffer, mView* view) - ������� ���������� ����� � ������ ��������������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������: ����� �����
*/
unsigned int numlinesScr(inBuff* buffer, mView* view) {
    unsigned width = view->cxClient/ view->font->cxChar -1, cStrings = 0;
    int tmpSize = 0;
    int i = 0;
    if(view->mode == FORMAT) {
        for(i = 0; i < (int)(buffer->posSize-1); i++) {
            tmpSize = buffer->pos[i + 1] - buffer->pos[i]  - 1;
            if(width < tmpSize) {
                cStrings+= tmpSize / width + (tmpSize % width == 0?0:1);
            } else {
                cStrings++;
            }
        }
    }
    return cStrings;
}

/*
void outBufInit(outBuf** outBuffer) - ������������� ���������, ������������� �� �������� �������� ��������� �� ������
�� �����:
outBuf** outBuffer - ��������� �� ��������� ���������
�� ������: ������(�� �������� ������ ��� ���������)
*/
void outBufInit(outBuf** outBuffer) {
    (*outBuffer) = malloc(sizeof(outBuf));
    if(!(*outBuffer)) {
        errMessage("cant alloc outbuf\n");
        return;
    }
    (*outBuffer)->strPos = NULL;
}

/*
void outBufDestoy(outBuf** outBuffer) - ����������� ���������
�� �����:
outBuf* outBuffer - ��������� �� ���������
�� ������: ������(������� ������, ���������� ��� ��������� � � ����)
*/
void outBufDestroy(outBuf* outBuffer) {
    if(!outBuffer) {
        errMessage("null ptr outbuffer\n");
        return;
    }
    free(outBuffer->strPos);
    free(outBuffer);
}
/*
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view) - �������� �������� ����� ���������
�� �����:
outBuf** outBuffer - ��������� �� ��������� ���������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������: ������(�� ������� ������ ��� ���� ���������, ������� ���������� ��� �������)
*/
void outBufResize(outBuf** outBuffer, inBuff* buffer, mView* view) {
    unsigned int width = view->cxClient/ view->font->cxChar - 1;
    int tmpSize = 0, j = 0, k= 0, i =0;
    (*outBuffer)->numPtr = view->numlinesOnScr + 1;
    if((*outBuffer)->strPos) {
        free((*outBuffer)->strPos);
    }
    (*outBuffer)->strPos = malloc(sizeof(unsigned int) * ((*outBuffer)->numPtr));
    if(!(*outBuffer)->strPos) {
        errMessage("cant alloc outbuf\n");
        return;
    }
    for(i = 0; i < (int)(buffer->posSize - 1); i++) {
        tmpSize = buffer->pos[i + 1] - buffer->pos[i] - 1;

        if(width >= tmpSize) {
            (*outBuffer)->strPos[k++] =  buffer->pos[i];
        } else {
            for(j = 0 ; width < tmpSize; j++) {
                (*outBuffer)->strPos[k++] = buffer->pos[i] + j * width;
                tmpSize-=width;
            }
            (*outBuffer)->strPos[k++] = buffer->pos[i] + j * width;
        }
    }
    (*outBuffer)->strPos[(*outBuffer)->numPtr  -1] = buffer->textSize;
}

/*
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth) - ���������� ���������� �������� � ������
inBuff* buffer - ���������, ���������� ������������ �����
unsigned int lineInd - ����� ������
unsigned int wth - ������ ���������� �������
�� ������: ���������� �������� � ������
*/
unsigned int getCntSubStr(inBuff* buffer, unsigned int lineInd, unsigned int wth) {
    unsigned width = wth,cStrings = 0;
    int tmpSize = 0;
    tmpSize = buffer->pos[lineInd + 1] - buffer->pos[lineInd]  - 1;
    if(width < tmpSize) {
        cStrings= tmpSize / width + (tmpSize % width == 0?0:1) - 1;
    }
    return cStrings;
}

/*
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view) - ���������� ������������ ������(������������ ��� ��������� �������)
outBuf* outBuffer - ��������� , �������� ��������� �� ������ ����� � ��������������� ������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������:
����� ������
*/
unsigned int getLastLine(outBuf* outBuffer, inBuff* buffer, mView* view) {
    unsigned int width = view->cxClient / view->font->cxChar - 1;
    int tmpSize= 0, cStrings = 0;
    if(view->mode == SCROLL) { //���� ������������� �� ������� � ��������������(������)
        int i = 0 ;
        for(i = 0; i < (int)(buffer->posSize-1) && i < view->lastIndx; i++) {
            tmpSize = buffer->pos[i + 1] - buffer->pos[i] -1;
            if(width < tmpSize) {
                cStrings+= tmpSize / width + (tmpSize % width == 0?0:1);
            } else {
                cStrings++;
            }

        }
        return cStrings;
    } else { //���� ������������� �� ������� � ��������������
        int j = 0;
        int i = 0;
        for(i = 0; i <  (int)(buffer->posSize-1) && j < view->lastIndx; cStrings++) {
            tmpSize = buffer->pos[i + 1] - buffer->pos[i] - 1;
            view->lastSubStr = 0;
            view->lastCntSub = getCntSubStr(buffer, i, width);
            if(width < tmpSize) {
                int k = 0;
                for(k = 0; tmpSize >0; k++, j++) {
                    tmpSize-=minn(width, tmpSize);
                    if(j == view->lastIndx) {
                        view->lastSubStr = k;
                        return cStrings;
                    }
                }
                i++;
            } else {
                j++;
                i++;
            }
        }
        return cStrings;
    }
}

/*
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view) - ���������� �������� ��� ��������� ������� ������
outBuf* outBuffer - ��������� , �������� ��������� �� ������ ����� � ��������������� ������
inBuff* buffer - ���������, ���������� ������������ �����
mView* view - ������ �������������
�� ������:
��������
*/
unsigned int getNewOffset(outBuf* outBuffer, inBuff* buffer, mView* view) {
    /*�������-�������. � ��������� ��������� ������ ����� � ������� �������� � ������� ������� ��������*/
    unsigned int width = view->cxClient / view->font->cxChar - 1;
    int tmpSize= 0, cStrings = 0;
    int j = 0, k = 0;
    int i = 0;
    view->lastSubStr = 0;
    for(i = 0; i < (int)(buffer->posSize-1) && j < view->lastIndx; cStrings++) { //���������� ����� ������ � ��������� ��� ������ ������
        tmpSize = buffer->pos[i + 1] - buffer->pos[i] - 1;
        view->lastSubStr = 0;
        view->lastCntSub = getCntSubStr(buffer, i, view->oldWidth);
        if(view->oldWidth < tmpSize) {
            for(k = 0; tmpSize >0; k++, j++) {
                tmpSize-=minn(view->oldWidth, tmpSize);
                if(j == view->lastIndx) {
                    view->lastSubStr = k;
                    break;
                }
            }
            if(j == view->lastIndx) {
                if(k - 1 == view->lastCntSub && k - 1!=0) {
                    cStrings++;
                }
                break;
            }
            i++;
        } else {
            j++;
            i++;
        }
    }
    int cntSubStr = getCntSubStr(buffer, cStrings, width);
    int cntPos = 0;
    for(i = 0; i < (int)(buffer->posSize-1) && i < cStrings; i++) {
        tmpSize = buffer->pos[i + 1] - buffer->pos[i] -1;
        if(width < tmpSize) {
            cntPos+= tmpSize / width + (tmpSize % width == 0?0:1);
        } else {
            cntPos++;
        }
    }//���������� ����� ������ � ��������� ��� ����� ������
    int newoffSet = 0;
    if(view->lastSubStr == 0) { //��������� ��������
        newoffSet = cntPos ;
    } else {
        if(view->lastSubStr* cntSubStr / view->lastCntSub == 0 && cntSubStr != 0) {
            newoffSet = cntPos + 1;
        } else if(view->lastSubStr == view->lastCntSub && cntSubStr > view->lastCntSub) {
            newoffSet = cntPos + cntSubStr - 1;//����� ���������
        } else if(cntSubStr < view->lastCntSub && view->lastSubStr != view->lastCntSub) { //���������, �� �� ���� �������
            newoffSet = cntPos + (double)view->lastSubStr* cntSubStr / view->lastCntSub  + (view->lastSubStr* cntSubStr / view->lastCntSub == 0?0:1);
        } else {
            newoffSet = cntPos + (double)view->lastSubStr* cntSubStr / view->lastCntSub ;
        }
    }
    view->lastCntSub = cntSubStr;
    view->lastSubStr = newoffSet - cntPos;
    return minn(newoffSet, view->VscrollMax * view->kf);
}
