#include"model.h"

/*fCreate - ��������� ��������� WM_CREATE
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������������� ���� ���������)
*/
void fCreate(HWND hwnd , modelData* mData);

/*fDestroy - ��������� ��������� WM_DESTROY
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������� ���� ���������)
*/
void fDestroy(modelData* mData);

/*fSize - ��������� ��������� WM_SIZE
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
LPARAM lParam - ����������, ������� �������� �� wndproc
�� ������: ������(��� ���� �������� ������������ ���� ���������)
*/
void fSize(HWND hwnd, modelData* mData, LPARAM lParam);

/*fPaint - ��������� ��������� WM_PAINT
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
�� ������: ������(��� ���� ������� �����)
*/
void fPaint(HWND hwnd, modelData* mData);

/*fVscroll - ��������� ��������� WM_VSCROLL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(������������� ������ �������� �� ������)
*/
void fVscroll(HWND hwnd, WPARAM wParam, modelData* mData);

/*fHscroll - ��������� ��������� WM_HSCROLL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(������������� �������� �� ������)
*/
void fHscroll(HWND hwnd, WPARAM wParam, modelData* mData);

/*fKeydown - ��������� ��������� WM_KEYDOWN
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(��������� ������� ������)
*/
void fKeydown(HWND hwnd, WPARAM wParam, modelData* mData);

/*fMouseWheel - ��������� ��������� WM_MOUSEWHEEL
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(��������� ��������� ����)
*/
void fMouseWheel(HWND hwnd, WPARAM wParam, modelData* mData);

/*fCommand - ��������� ��������� WM_COMMNAD
�� �����:
HWND hwnd - ��������� ����(�������� �� wndproc)
modelData* mData - ��������� �� ����� ���������(������ ������)
WPARAM wParam - ����������, ������� �������� �� wndproc
�� ������: ������(� ����������� �� ������� ����� ������������� ���� ���������)
*/
void fCommand(HWND hwnd, WPARAM wParam, modelData* mData);


