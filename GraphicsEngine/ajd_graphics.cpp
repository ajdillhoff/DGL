/*
	File:					ajd_graphics.cpp
	Created:			07/30/2014
	Modified:			07/30/2014
	Description:	Implementation file for importing the graphics package created from "Computer Graphics C Version (2nd ed.)" by Donald Hearn and M. Pauline Baker
*/

#include "ajd_graphics.h"

/* Draw a connected sequence of n-1 line segments, specified in pts. */
void pPolyLine(int n, wcpt2 *pts, HWND sHwnd, COLORREF color) {
	for (int i = 0; i < n-1; i++) {
		lineBres(sHwnd, (int)pts[i].x, (int)pts[i].y, (int)pts[i + 1].x, (int)pts[i + 1].y, color);
	}
	// Draw the last two points
	lineBres(sHwnd, (int)pts[0].x, (int)pts[0].y, (int)pts[n - 1].x, (int)pts[n - 1].y, color);
}

/* Draw a filled polygon with n vertices, specified in pts. */
void pFillArea(int n, wcpt2 *pts, HWND sHwnd, COLORREF color) {
	//scanFill(n, pts, sHwnd, color);
}

/* Buffer test */
void pBufPolyLine(int n, wcpt2 *pts, HWND sHwnd, COLORREF color) {
	bufferPt *buffer = createPixelBuffer(200, 200);
	for (int i = 0; i < n - 1; i++) {
		lineBresBuf(buffer, (int)pts[i].x, (int)pts[i].y, (int)pts[i + 1].x, (int)pts[i + 1].y, color);
	}
	lineBresBuf(buffer, (int)pts[0].x, (int)pts[0].y, (int)pts[n - 1].x, (int)pts[n - 1].y, color);
	drawBuffer(buffer, sHwnd);
	clearBuffer(buffer);
}

void drawTriangle(POINT3D& p1, POINT3D& p2, POINT3D& p3, HWND sHwnd, COLORREF color) {
	lineBres(sHwnd, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, color);
	lineBres(sHwnd, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, color);
	lineBres(sHwnd, (int)p3.x, (int)p3.y, (int)p1.x, (int)p1.y, color);
}

void drawFilledTriangle(POINT3D& p1, POINT3D& p2, POINT3D& p3, HWND sHwnd, COLORREF color) {
	POINT3D pts[3];
	pts[0] = p1;
	pts[1] = p2;
	pts[2] = p3;
	scanFill(3, pts, sHwnd, color);
}