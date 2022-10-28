#include"model.h"

/*fCreate - обработка сообщений WM_CREATE
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
На выходе: ничего(при этом инициализруем поля структуры)
*/
void fCreate(HWND hwnd , modelData* mData);

/*fDestroy - обработка сообщений WM_DESTROY
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
На выходе: ничего(при этом очищаем поля структуры)
*/
void fDestroy(modelData* mData);

/*fSize - обработка сообщений WM_SIZE
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
LPARAM lParam - переменная, которую получили из wndproc
На выходе: ничего(при этом получаем изменененные поля структуры)
*/
void fSize(HWND hwnd, modelData* mData, LPARAM lParam);

/*fPaint - обработка сообщений WM_PAINT
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
На выходе: ничего(при этом выводим текст)
*/
void fPaint(HWND hwnd, modelData* mData);

/*fVscroll - обработка сообщений WM_VSCROLL
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
WPARAM wParam - переменная, которую получили из wndproc
На выходе: ничего(пересчитанное значие смещения по тексту)
*/
void fVscroll(HWND hwnd, WPARAM wParam, modelData* mData);

/*fHscroll - обработка сообщений WM_HSCROLL
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
WPARAM wParam - переменная, которую получили из wndproc
На выходе: ничего(пересчитанное смещение по тексту)
*/
void fHscroll(HWND hwnd, WPARAM wParam, modelData* mData);

/*fKeydown - обработка сообщений WM_KEYDOWN
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
WPARAM wParam - переменная, которую получили из wndproc
На выходе: ничего(обработка нажатий клавиш)
*/
void fKeydown(HWND hwnd, WPARAM wParam, modelData* mData);

/*fMouseWheel - обработка сообщений WM_MOUSEWHEEL
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
WPARAM wParam - переменная, которую получили из wndproc
На выходе: ничего(обработка прокрутки мыши)
*/
void fMouseWheel(HWND hwnd, WPARAM wParam, modelData* mData);

/*fCommand - обработка сообщений WM_COMMNAD
На входе:
HWND hwnd - описатель окна(получили из wndproc)
modelData* mData - указатель на общую структуру(модель данных)
WPARAM wParam - переменная, которую получили из wndproc
На выходе: ничего(в зависимости от команды будут пересчитанные поля структуры)
*/
void fCommand(HWND hwnd, WPARAM wParam, modelData* mData);


