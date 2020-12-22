#pragma once

#include <math.h>
#include <windows.h>
#define Pi 3.141592653589

typedef struct Vector
{
	SHORT x, y;
} Vector;

void RotateVector(Vector* v, double phi);

typedef struct Triangle
{
	POINTS Origin; // coords of left bottom corner
	Triangle* Parent;
	int level;
	Triangle* Child[3];
} Triangle;

void ClearWindow(HDC hdc);
void Line(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2); //Draw line (x1,y1)-(x2,y2)
void LineA(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy); //Draw line (x1,y1)-(x1+dx,y1+dy), change origin of vector to (x1+dx,y1+dy)
void LineDv(HDC hdc, POINTS* ptsBegin, SHORT dx, SHORT dy); //Draw line (x1,y1)-(x1+dx,y1+dy)
void DrawTriangle(HDC hdc, Triangle* ptr); 
void DivideTriangle(Triangle* ptr); //give triangle children
void DrawDivided(HDC hdc, Triangle* ptr, int IsDel); //draw or clear one level of triangles
Triangle* InitTriangle(HWND hWnd, POINTS* ptsBegin, POINTS* ptsEnd);
void CreateLevel(HDC, Triangle*);
void FreeLevel(HDC, Triangle*);