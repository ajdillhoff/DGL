/*
	File:					ajd_gbase.h
	Created:			07/30/2014
	Modified:			07/30/2014
	Description:	Header file containing base functionality used by higher level graphics implementations.
*/

#include <windows.h>
#include "Matrix.h"
#include "Vector.h"
#include <math.h>

#define PI 3.14159265358979323846
#define DEG2RAD PI/(180.0)

#ifndef GBASE
#define GBASE

typedef struct {
	int x, y;
} wcpt2;

typedef struct {
	int width, height;
	COLORREF *pixels;
} bufferPt;

void setPixel(int, int, COLORREF, HWND);

void setPixelBuffer(int, int, COLORREF, bufferPt*);

bufferPt* createPixelBuffer(int, int);

void clearBuffer(bufferPt*);

void drawBuffer(bufferPt*, HWND);

#endif