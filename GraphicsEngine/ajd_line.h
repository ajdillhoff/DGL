/*
	File:					ajd_line.h
	Created:			07/29/2014
	Modified:			07/30/2014
	Description:	Header file for prototyping line algorithms used in graphics programming.
*/

#include <windows.h>
#include "ajd_gbase.h"

/* Bresenham's line drawing algorithm for slopes in the range 0 < m < 1 */
void lineBres(HWND, int, int, int, int, COLORREF);

/* Buffer test */
void lineBresBuf(bufferPt *, int, int, int, int, COLORREF);