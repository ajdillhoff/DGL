/*
	File:					ajd_graphics.h
	Created:			07/30/2014
	Modified:			07/30/2014
	Description:	Header file for importing the graphics package created from "Computer Graphics C Version (2nd ed.)" by Donald Hearn and M. Pauline Baker
*/

#include "ajd_line.h"
#include "ajd_poly.h"

/* Draw a connected sequence of n-1 line segments, specified in pts. */
void pPolyLine(int n, wcpt2 *pts, HWND, COLORREF);

/* Draw a filled polygon with n vertices, specified in pts. */
void pFillArea(int, wcpt2 *, HWND, COLORREF);

/* Buffer test */
void pBufPolyLine(int, wcpt2 *, HWND, COLORREF);

void drawTriangle(POINT3D&, POINT3D&, POINT3D&, HWND, COLORREF);
void drawFilledTriangle(POINT3D&, POINT3D&, POINT3D&, HWND, COLORREF);