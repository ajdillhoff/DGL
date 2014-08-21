/*
	File:					ajd_poly.h
	Created:			07/29/2014
	Modified:			07/30/2014
	Description:	Header file for prototyping polygon draw and fill algorithms used in graphics programming.
*/

#include <windows.h>
#include "ajd_gbase.h"

typedef struct tEdge {
	int yUpper;
	float xIntersect, dxPerScan;
	struct tEdge *next;
} Edge;

/* Inserts edge into list in order of increasing xIntersect field. */
void insertEdge(Edge *, Edge *);

/* For an index, return y-coordinate of next non horizontal line. */
int yNext(int, int, POINT3D []);

/* Store lower-y coordinate and inverse slope for each edge. Adjust
	 and store upper-y coordinate for edges that are the lower member
	 of a monotonically increasing or decreasing pair of edges. */
void makeEdgeRec(POINT3D, POINT3D, int, Edge *, Edge *[]);

/* Builds a list of edges given the initial POINTs. */
void buildEdgeList(int, POINT3D [], Edge *[]);

void buildActiveList(int, Edge *, Edge *[]);

/* Draws the fill between the edges */
void fillScan(int, Edge *, HWND, COLORREF);

void deleteAfter(Edge *);

/* Delete completed edges. Update 'xIntersect' field for others. */
void updateActiveList(int, Edge *);

void resortActiveList(Edge *);
void scanFill(int, POINT3D [], HWND, COLORREF);