/*
	File:					ajd_line.cpp
	Created:			07/29/2014
	Modified:			07/29/2014
	Description:	Implementation file for prototyping line algorithms used in graphics programming.
*/

#include "ajd_line.h"

/* Bresenham's line drawing algorithm for slopes in the range 0 < m < 1 */
void lineBres(HWND sHwnd, int xa, int ya, int xb, int yb, COLORREF COLOR) {
	int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
	int x, y, xEnd, yEnd;
	int steep = dy > dx ? 1 : 0;
	int temp = 0;

	if (steep) {
		p = 2 * dx - dy;
		twoDyDx = 2 * (dx - dy);
		twoDy = 2 * dx;

		temp = xa;
		xa = ya;
		ya = temp;

		temp = xb;
		xb = yb;
		yb = temp;
	}

	/* Determine which point to use as start, which as end */
	if (xa > xb) {
		x = xb;
		y = yb;
		xEnd = xa;
		yEnd = ya;
	} else {
		x = xa;
		y = ya;
		xEnd = xb;
		yEnd = yb;
	}
	if (steep > 0)
		setPixel(y, x, COLOR, sHwnd);
	else
		setPixel(x, y, COLOR, sHwnd);
	

	while (x < xEnd) {
		x++;
		if (p < 0)
			p += twoDy;
		else {
			if (y > yEnd) {
				y--;
			} else {
				y++;
			}
			p += twoDyDx;
		}
		if (steep > 0)
			setPixel(y, x, COLOR, sHwnd);
		else
			setPixel(x, y, COLOR, sHwnd);
	}
}

void lineBresBuf(bufferPt *buffer, int xa, int ya, int xb, int yb, COLORREF COLOR) {
	int dx = abs(xa - xb), dy = abs(ya - yb);
	int p = dx - dy, p2;
	int sx = xa < xb ? 1 : -1;
	int sy = ya < yb ? 1 : -1;

	while (xa != xb || ya != yb) {
		setPixelBuffer(xa, ya, COLOR, buffer);
		p2 = 2 * p;
		if (p2 > -1 * dy) {
			p -= dy;
			xa += sx;
		}

		if (p2 < dx) {
			p += dx;
			ya += sy;
		}
	}
}