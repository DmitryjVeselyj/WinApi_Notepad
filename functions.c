#include"functions.h"

/*fCreate - ��������� ��������� WM_CREATE
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������������� ���� ���������)
*/
void fCreate(HWND hwnd, modelData* mData) {
    HDC hdc;
    hdc = GetDC(hwnd);
    initBuff(&(mData->buffer));         //�������������
    viewInit(&(mData->view));
    if(mData->view)
        setStyle(hdc, mData->view->font);
    outBufInit(&(mData->outBuffer));
    ReleaseDC(hwnd, hdc);
}

/*fDestroy - ��������� ��������� WM_DESTROY
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������� ���� ���������)
*/
void fDestroy(modelData* mData) {
    destroyBuff(mData->buffer);         //�����������
    outBufDestroy(mData->outBuffer);
    viewDestroy(mData->view);
}

/*fSize - ��������� ��������� WM_SIZE
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
LPARAM lParam - ����������, ������� �������� �� wndproc
�� ������: ������(��� ���� �������� ������������ ���� ���������)
*/
void fSize(HWND hwnd, modelData* mData, LPARAM lParam) {
    if(!IsIconic(hwnd) && mData->buffer->text != NULL) {
        mData->view->oldWidth = mData->view->cxClient/ mData->view->font->cxChar - 1;
        mData->view->oldHeigth = mData->view->cyClient/ mData->view->font->cyChar - 1;
        mData->view->cxClient = LOWORD(lParam);                         //�������� ��������
        mData->view->cyClient = HIWORD(lParam);
        int newWidth = mData->view->cxClient/ mData->view->font->cxChar -1;
        int newHeigth = mData->view->cyClient/ mData->view->font->cyChar - 1;
        if(mData->view->oldWidth != newWidth || mData->view->oldHeigth != newHeigth) {
            viewResize(mData->view, mData->buffer->posSize - 1, numlinesScr(mData->buffer, mData->view));

            if(mData->view->mode == FORMAT && mData->view->oldWidth != newWidth) {
                mData->view->yOffset = getNewOffset(mData->outBuffer, mData->buffer, mData->view);
                outBufResize(&(mData->outBuffer), mData->buffer, mData->view);
            }
        }
        SetScrollRange(hwnd, SB_VERT, 0, mData->view->VscrollMax, FALSE);//������������� �������� ��� �������
        SetScrollRange(hwnd, SB_HORZ, 0, mData->view->HscrollMax, FALSE);
        SetScrollPos(hwnd, SB_VERT, (int)((double)mData->view->yOffset / mData->view->kf), TRUE);//������������� ������� �������
        SetScrollPos(hwnd, SB_HORZ, (int)((double)mData->view->xOffset / mData->view->kfh), TRUE);
        mData->view->isSwitchMode = 0;
    }
}

/*fPaint - ��������� ��������� WM_PAINT
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������� �����)
*/
void fPaint(HWND hwnd, modelData* mData) {
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    unsigned int pBeg = 0, pEnd = 0, pLeft = 0, pRight = 0;
    pBeg = maxx(0, mData->view->yOffset+ ps.rcPaint.top / mData->view->font->cyChar- 1);//����������, � ����� ����� ��������
    pLeft = maxx(0, mData->view->xOffset+ ps.rcPaint.left / mData->view->font->cxChar -1);//������� � ������, � ������� ������� �����
    if(mData->view->mode == FORMAT) {
        pEnd = minn(mData->outBuffer->numPtr -1, mData->view->yOffset + ps.rcPaint.bottom / mData->view->font->cyChar + 1);//����������, �� ����� ������ ��������
        pRight = minn(mData->view->maxStrLeng,   mData->view->xOffset + ps.rcPaint.right / mData->view->font->cxChar );
    } else {
        pEnd = minn(mData->buffer->posSize - 1,    mData->view->yOffset + ps.rcPaint.bottom / mData->view->font->cyChar  + 1);
        pRight = minn(mData->view->maxStrLeng,   mData->view->xOffset + ps.rcPaint.right / mData->view->font->cxChar );//������� � ������, �� ������� ������� �����
    }
    printText(hdc, mData->outBuffer,mData->buffer,  mData->view, pBeg, pEnd,  pLeft, pRight);
    EndPaint(hwnd, &ps);
}

/*fVscroll - ��������� ��������� WM_VSCROLL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(������������� ������ �������� �� ������)
*/
void fVscroll(HWND hwnd, WPARAM wParam, modelData* mData) {
    int VscrollInc = 0;
    switch(LOWORD(wParam)) {
    case SB_TOP :
        VscrollInc = -mData->view->yOffset;
        break;
    case SB_BOTTOM :
        VscrollInc = mData->view->kf * mData->view->VscrollMax - mData->view->yOffset;
        break;
    case SB_LINEUP :
        VscrollInc = -1;
        break;
    case SB_LINEDOWN :
        VscrollInc = 1;
        break;
    case SB_PAGEUP :
        VscrollInc = minn(-1, -mData->view->cyClient / mData->view->font->cyChar);
        break;
    case SB_PAGEDOWN :
        VscrollInc = minn(1, mData->view->cyClient / mData->view->font->cyChar);
        break;
    case SB_THUMBTRACK :
        VscrollInc = mData->view->kf * HIWORD(wParam)- mData->view->yOffset;
        break;
    default :
        VscrollInc = 0;
    }
    VscrollInc =  maxx(-mData->view->yOffset, minn(VscrollInc, mData->view->kf * mData->view->VscrollMax - mData->view->yOffset));//���������� ����������� � ��������
    if (VscrollInc != 0) {
        mData->view->yOffset +=  VscrollInc;
        ScrollWindow(hwnd, 0, -mData->view->font->cyChar * VscrollInc,NULL, NULL);
        SetScrollPos(hwnd, SB_VERT, mData->view->yOffset / mData->view->kf, TRUE);
    }

}

/*fHscroll - ��������� ��������� WM_HSCROLL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(������������� �������� �� ������)
*/
void fHscroll(HWND hwnd, WPARAM wParam, modelData* mData) {
    int HscrollInc = 0;
    switch(LOWORD(wParam)) {
    case SB_LINEUP :
        HscrollInc = -1;
        break;
    case SB_LINEDOWN :
        HscrollInc = 1;
        break;
    case SB_PAGEUP :
        HscrollInc =minn(-1, -mData->view->cxClient / mData->view->font->cxChar);
        break;
    case SB_PAGEDOWN :
        HscrollInc = minn(1, mData->view->cxClient / mData->view->font->cxChar);
        break;
    case SB_THUMBTRACK :
        HscrollInc = mData->view->kfh * HIWORD(wParam) - mData->view->xOffset;
        break;
    default :
        HscrollInc = 0;
    }
    HscrollInc = maxx(-mData->view->xOffset,minn(HscrollInc, mData->view->kfh * mData->view->HscrollMax - mData->view->xOffset));//���������� ����������� � ��������
    if (HscrollInc != 0) {
        mData->view->xOffset += HscrollInc;
        ScrollWindow(hwnd, -mData->view->font->cxChar * HscrollInc, 0, NULL, NULL);
        SetScrollPos(hwnd, SB_HORZ, (int)((double)mData->view->xOffset / mData->view->kfh), TRUE);

    }

}

/*fKeydown - ��������� ��������� WM_KEYDOWN
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(��������� ������� ������)
*/
void fKeydown(HWND hwnd, WPARAM wParam, modelData* mData) {
    switch(wParam) {
    case VK_HOME :
        SendMessage(hwnd, WM_VSCROLL, SB_TOP, 0L);
        break;
    case VK_END :
        SendMessage(hwnd, WM_VSCROLL, SB_BOTTOM, 0L);
        break;
    case VK_PRIOR :
        SendMessage(hwnd, WM_VSCROLL, SB_PAGEUP, 0L);
        break;
    case VK_NEXT :
        SendMessage(hwnd, WM_VSCROLL, SB_PAGEDOWN, 0L);
        break;
    case VK_UP :
        SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0L);
        break;
    case VK_DOWN :
        SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0L);
        break;
    case VK_LEFT :
        if(mData->view->mode == SCROLL)
            SendMessage(hwnd, WM_HSCROLL, SB_PAGEUP, 0L);
        break;
    case VK_RIGHT :
        if(mData->view->mode == SCROLL)
            SendMessage(hwnd, WM_HSCROLL, SB_PAGEDOWN, 0L);
        break;
    }
}

/*fMouseWheel - ��������� ��������� WM_MOUSEWHEEL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(��������� ��������� ����)
*/
void fMouseWheel(HWND hwnd, WPARAM wParam, modelData* mData) {

    mData->view->wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
    for(; mData->view->wheelDelta > WHEEL_DELTA; mData->view->wheelDelta -= WHEEL_DELTA)
        SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0L);
    for(; mData->view->wheelDelta < 0; mData->view->wheelDelta += WHEEL_DELTA)
        SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0L);
}

/*fCommand - ��������� ��������� WM_COMMNAD
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(� ����������� �� ������� ����� ������������� ���� ���������)
*/
void fCommand(HWND hwnd, WPARAM wParam, modelData* mData) {
    HMENU hMenu = GetMenu(hwnd);
    switch(LOWORD(wParam)) {
    case IDM_OPEN: {

        char szFile[200];
        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(ofn));

        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "*.TXT\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if(GetOpenFileName(&ofn) == TRUE) {
            readFile(ofn.lpstrFile, mData->buffer);
            if(mData->buffer->text) {
                mData->view->maxStrLeng = maxStrLength(mData->buffer);
                mData->view->xOffset = 0;
                mData->view->yOffset = 0;
                mData->view->isSwitchMode = 1;
            }
            else{
                mData->view->isSwitchMode = 0;
            }
        }
        break;

    }
    case IDM_EXIT :
        SendMessage(hwnd, WM_CLOSE, 0, 0L);
        break;
    case IDM_FORMAT:
        CheckMenuItem(hMenu, IDM_SCROLL, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_FORMAT, MF_CHECKED);

        if(mData->view->mode == SCROLL) {
            mData->view->xOffset = 0;
            mData->view->isSwitchMode = 1;
            mData->view->yOffset = getLastLine(mData->outBuffer, mData->buffer, mData->view);
        }
        mData->view->mode = FORMAT;
        break;
    case IDM_SCROLL:
        CheckMenuItem(hMenu, IDM_FORMAT, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_SCROLL, MF_CHECKED);
        if(mData->view->mode == FORMAT) {
            mData->view->xOffset = 0;
            mData->view->isSwitchMode = 1;
            mData->view->yOffset = getLastLine(mData->outBuffer, mData->buffer, mData->view);
        }
        mData->view->mode = SCROLL;
        break;
    }
    if(mData->view->isSwitchMode == 1) {
        viewResize(mData->view, mData->buffer->posSize - 1, numlinesScr(mData->buffer, mData->view));
        if(mData->view->mode == FORMAT) {
            outBufResize(&(mData->outBuffer), mData->buffer, mData->view);
            ShowScrollBar(hwnd, SB_HORZ, FALSE);
        } else {
            if(!mData->view->HscrollMax && !mData->view->xOffset){
              ShowScrollBar(hwnd, SB_HORZ, FALSE);
            }
            else{
            ShowScrollBar(hwnd, SB_HORZ, TRUE);
            }
        }
        if(!mData->view->VscrollMax && !mData->view->yOffset){
          ShowScrollBar(hwnd, SB_VERT, FALSE);
        }
        else{
          ShowScrollBar(hwnd, SB_VERT, TRUE);
        }


        SetScrollRange(hwnd, SB_VERT, 0, mData->view->VscrollMax, FALSE);
        SetScrollRange(hwnd, SB_HORZ, 0, mData->view->HscrollMax, FALSE);
        SetScrollPos(hwnd, SB_VERT, (int)((double)mData->view->yOffset / mData->view->kf), TRUE);
        SetScrollPos(hwnd, SB_HORZ, (int)((double)mData->view->xOffset / mData->view->kfh), TRUE);
        InvalidateRect(hwnd,NULL, TRUE);
        UpdateWindow(hwnd);
        mData->view->isSwitchMode = 0;
    }
}


