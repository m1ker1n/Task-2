#include "Foo.h"

Vector v[3];
int levelCounts = 0; //level
int koef = 1;
Triangle* root;

void RotateVector(Vector* v, double phi)
{
	double x, y;
	x = v->x;
	y = v->y;
	v->x = (SHORT)(x * cos(phi) - y * sin(phi));
	v->y = (SHORT)(x * sin(phi) + y * cos(phi));
}


void ClearWindow(HDC hdc)
{
	HBRUSH hBrush; //declare brush
	hBrush = CreateSolidBrush(RGB(0, 0, 0)); //solid black brush
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, 800, 800); //paint all the canvas in black
	DeleteObject(hBrush); //delete brush
}


void Line(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2)
{
	MoveToEx(hdc, x1, y1, (LPPOINT)NULL);
	LineTo(hdc, x2, y2);
}


void LineDv(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy)
{
	Line(hdc, ptsBegin->x, ptsBegin->y, ptsBegin->x + dx, ptsBegin->y - dy);
}


void DrawTriangle(HDC hdc, Triangle* ptr)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	SelectObject(hdc, hPen);
	for (int i = 0; i < 3; i++)
	{
		LineDv(hdc, &(ptr->Origin), v[i].x / koef, v[i].y / koef);

		(&(ptr->Origin))->x += v[i].x / koef;
		(&(ptr->Origin))->y -= v[i].y / koef;
	}
	DeleteObject(hPen);
}


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
		RotateVector(v + i, 2 * Pi / 3);
	}
	return ptr;
}


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