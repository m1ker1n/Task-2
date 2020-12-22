// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, 800, 800, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //
#include "Foo.h"
extern int levelCounts;
extern int koef;
extern Triangle* root;

/*
struct Vector
{
	SHORT x, y;
	void Rotate(Vector* v, double phi) //add phi
	{
		double x, y;
		x = v->x;
		y = v->y;
		v->x = (SHORT)(v->x * cos(phi) - v->y * sin(phi));
		v->y = (SHORT)(v->x * sin(phi) + v->y * cos(phi));
	}
} v[3];

struct Triangle
{
	POINTS Origin; // coords of left bottom corner
	Triangle* Parent;
	int level;
	Triangle* Child[3];
};

int levelCounts = 0; //level
int koef = 1;
Triangle* root;

void ClearWindow(HDC hdc);
void ClearWindow(HDC hdc)
{
	HBRUSH hBrush; //declare brush
	hBrush = CreateSolidBrush(RGB(0, 0, 0)); //solid black brush
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, 800, 800); //paint all the canvas in black
	DeleteObject(hBrush); //delete brush
}

void Line(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2);
void Line(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2)
{
	MoveToEx(hdc, x1, y1, (LPPOINT)NULL);
	LineTo(hdc, x2, y2);
}

void LineA(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy);
void LineA(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy)
{
	Line(hdc, ptsBegin->x, ptsBegin->y, ptsBegin->x + dx, ptsBegin->y - dy);
	ptsBegin->x += dx;
	ptsBegin->y -= dy;
}

void LineDv(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy);
void LineDv(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy)
{
	Line(hdc, ptsBegin->x, ptsBegin->y, ptsBegin->x + dx, ptsBegin->y - dy);
}

void DrawTriangle(HDC hdc, Triangle* ptr);
void DrawTriangle(HDC hdc, Triangle* ptr)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	for (int i = 0; i < 3; i++)
	{
		LineA(hdc, &(ptr->Origin), v[i].x / koef, v[i].y / koef);
	}
	DeleteObject(hPen);
}

void DivideTriangle(Triangle* ptr);
void DivideTriangle(Triangle* ptr)
{
	Triangle* ChildPtr[3];

	for (int i = 0; i < 3; i++)
	{
		ChildPtr[i] = (Triangle*)malloc(sizeof(Triangle));
		if (ChildPtr == NULL) PostQuitMessage(0);
		ptr->Child[i] = ChildPtr[i];
		ChildPtr[i]->Parent = ptr;
		ChildPtr[i]->level = levelCounts;
		for (int k = 0; k < 3; k++) ChildPtr[i]->Child[k] = NULL;
	}

	ChildPtr[0]->Origin.x = ptr->Origin.x;
	ChildPtr[0]->Origin.y = ptr->Origin.y;

	ChildPtr[1]->Origin.x = ptr->Origin.x + v[0].x / koef;
	ChildPtr[1]->Origin.y = ptr->Origin.y - v[0].y / koef;

	ChildPtr[2]->Origin.x = ptr->Origin.x - v[2].x / koef;
	ChildPtr[2]->Origin.y = ptr->Origin.y + v[2].y / koef;
}

void DrawDivided(HDC hdc, Triangle* ptr, int IsDel);
void DrawDivided(HDC hdc, Triangle* ptr, int IsDel)
{
	HPEN hPen;
	if (IsDel) hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	else hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	LineDv(hdc, &(ptr->Child[1])->Origin, v[1].x / koef, v[1].y / koef);
	LineDv(hdc, &(ptr->Child[1])->Origin, -v[2].x / koef, -v[2].y / koef);
	LineDv(hdc, &(ptr->Child[2])->Origin, v[0].x / koef, v[0].y / koef);
	DeleteObject(hPen);
}

Triangle* InitTriangle(HWND hWnd, POINTS* ptsBegin, POINTS* ptsEnd);
Triangle* InitTriangle(HWND hWnd, POINTS* ptsBegin, POINTS* ptsEnd)
{
	SHORT dx, dy;
	dx = ptsEnd->x - ptsBegin->x;
	dy = -(ptsEnd->y - ptsBegin->y); //Because origin is in left top corner

	Triangle* ptr = (Triangle*)malloc(sizeof(Triangle));
	if (ptr == NULL) PostQuitMessage(0);
	ptr->Origin.x = ptsBegin->x;
	ptr->Origin.y = ptsBegin->y;
	ptr->Parent = NULL;
	ptr->level = 0;
	levelCounts = 0;
	koef = 1;


	v[0].x = dx;
	v[0].y = dy;
	ptr->Child[0] = NULL;
	for (int i = 1; i < 3; i++)
	{
		ptr->Child[i] = NULL;
		v[i].x = v[i - 1].x;
		v[i].y = v[i - 1].y;
		v[i].Rotate(v + i, 2 * Pi / 3);
	}
	return ptr;
}

void CreateLevel(HDC, Triangle*);
void CreateLevel(HDC hdc, Triangle* ptr)
{
	if (ptr->level >= levelCounts) return;
	else if (ptr->Child[0] != NULL) 
	{
		for (int i = 0; i < 3; i++) CreateLevel(hdc, ptr->Child[i]);
	}
	else
	{
		DivideTriangle(ptr);
		DrawDivided(hdc, ptr, 0);
		CreateLevel(hdc, ptr);
	}
}

void FreeLevel(HDC, Triangle*);
void FreeLevel(HDC hdc, Triangle* ptr)
{
	if (ptr->level < levelCounts)
	{
		for (int i = 0; i < 3; i++)
		{
			FreeLevel(hdc, ptr->Child[i]);

		}
	}
	else
	{
		Triangle* ptr1 = ptr->Parent;
		if (ptr1->Child[0] != NULL) DrawDivided(hdc, ptr1, 1);
		if (ptr == ptr1->Child[0]) ptr1->Child[0] = NULL;
		else if (ptr == ptr1->Child[1]) ptr1->Child[1] = NULL;
		else if (ptr == ptr1->Child[2]) ptr1->Child[2] = NULL;
		free(ptr);
	}
}
*/
// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //// MOE //

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;                       // handle to device context 
	RECT rcClient;                 // client area rectangle 
	POINT ptClientUL;              // client upper left corner 
	POINT ptClientLR;              // client lower right corner 
	static POINTS ptsBegin;        // beginning point 
	static POINTS ptsEnd;          // new endpoint 
	static POINTS ptsPrevEnd;      // previous endpoint 
	static BOOL fPrevLine = FALSE; // previous line flag 

	switch (message)
	{
	case WM_LBUTTONDOWN:

		// Capture mouse input. 

		SetCapture(hWnd);

		// Retrieve the screen coordinates of the client area, 
		// and convert them into client coordinates. 

		GetClientRect(hWnd, &rcClient);
		ptClientUL.x = rcClient.left;
		ptClientUL.y = rcClient.top;

		// Add one to the right and bottom sides, because the 
		// coordinates retrieved by GetClientRect do not 
		// include the far left and lowermost pixels. 

		ptClientLR.x = rcClient.right + 1;
		ptClientLR.y = rcClient.bottom + 1;
		ClientToScreen(hWnd, &ptClientUL);
		ClientToScreen(hWnd, &ptClientLR);

		// Copy the client coordinates of the client area 
		// to the rcClient structure. Confine the mouse cursor 
		// to the client area by passing the rcClient structure 
		// to the ClipCursor function. 

		SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
			ptClientLR.x, ptClientLR.y);
		ClipCursor(&rcClient);

		// Convert the cursor coordinates into a POINTS 
		// structure, which defines the beginning point of the 
		// line drawn during a WM_MOUSEMOVE message. 

		ptsBegin = MAKEPOINTS(lParam);
		return 0;

	case WM_MOUSEMOVE:

		// When moving the mouse, the user must hold down 
		// the left mouse button to draw lines. 

		if (wParam & MK_LBUTTON)
		{

			// Retrieve a device context (DC) for the client area. 

			hdc = GetDC(hWnd);

			// The following function ensures that pixels of 
			// the previously drawn line are set to white and 
			// those of the new line are set to black. 

			SetROP2(hdc, R2_NOTXORPEN); //выбирает цвет, инверсивный фону

			// If a line was drawn during an earlier WM_MOUSEMOVE 
			// message, draw over it. This erases the line by 
			// setting the color of its pixels to white. 

			if (fPrevLine)
			{
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
					(LPPOINT)NULL);
				LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
			}

			// Convert the current cursor coordinates to a 
			// POINTS structure, and then draw a new line. 

			ptsEnd = MAKEPOINTS(lParam);
			MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
			LineTo(hdc, ptsEnd.x, ptsEnd.y);

			// Set the previous line flag, save the ending 
			// point of the new line, and then release the DC. 

			fPrevLine = TRUE;
			ptsPrevEnd = ptsEnd;
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_LBUTTONUP:
	{
		// The user has finished drawing the line. Reset the 
		// previous line flag, release the mouse cursor, and 
		// release the mouse capture. 

		fPrevLine = FALSE;
		ClipCursor(NULL); //To make cursor always in the borders
		ReleaseCapture();

		root = InitTriangle(hWnd, &ptsBegin, &ptsEnd);

		HDC hdc = GetDC(hWnd);
		DrawTriangle(hdc, root);
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	break;
	case WM_KEYDOWN:
	{
		hdc = GetDC(hWnd);
		switch (wParam)
		{
		case VK_ESCAPE:
			// Retrieve a device context (DC) for the client area. 
			ClearWindow(hdc);
			//освободить все структуры, обнулить n
			break;

		case VK_RIGHT:

			levelCounts++;
			koef *= 2;
			CreateLevel(hdc, root);

			break;

		case VK_LEFT:
			if (levelCounts > 0)
			{
				FreeLevel(hdc, root);
				levelCounts--;
				koef /= 2;
			}
			break;
		}
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		ClearWindow(hdc);
		//освободить все структуры, обнулить n
		EndPaint(hWnd, &ps);
	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
