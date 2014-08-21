/*
	File:					ajd_gbase.cpp
	Created:			07/30/2014
	Modified:			07/30/2014
	Description:	Implementation file containing base functionality used by higher level graphics implementations.
*/

#include "ajd_gbase.h"

void setPixel(int x, int y, COLORREF color, HWND sHwnd) {
	HDC hdc = GetDC(sHwnd);
	SetPixel(hdc, x, y, color);
	ReleaseDC(sHwnd, hdc);
	return;
}

void setPixelBuffer(int x, int y, COLORREF color, bufferPt *buffer) {
	int width = buffer->width;
	buffer->pixels[y * width + x] = color;
}

bufferPt* createPixelBuffer(int width, int height) {
	bufferPt *newBuffer = (bufferPt*)malloc(sizeof(bufferPt));
	newBuffer->width = width;
	newBuffer->height = height;
	newBuffer->pixels = (COLORREF*)malloc((width * height) * sizeof(COLORREF));

	return newBuffer;
}

void clearBuffer(bufferPt *buffer) {
	free(buffer->pixels);
	free(buffer);
}

void drawBuffer(bufferPt *buffer, HWND sHwnd) {
	int width = buffer->width;
	int height = buffer->height;
	int x, y;
	COLORREF color;
	for (int i = 0; i < width * height; i++) {
		y = (i / height);
		x = (i % width);
		color = buffer->pixels[(y * width) + x];
		if (color) {
			setPixel(x, y, color, sHwnd);
		}
	}
}