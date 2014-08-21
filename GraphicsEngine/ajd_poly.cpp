/*
	File:					ajd_poly.cpp
	Created:			07/29/2014
	Modified:			07/30/2014
	Description:	Implementation file for prototyping polygon draw and fill algorithms used in graphics programming.
*/

#include "ajd_poly.h"

void insertEdge(Edge *list, Edge *edge) {
	Edge *p, *q = list;

	p = q->next;
	while (p != NULL) {
		if (edge->xIntersect < p->xIntersect) {
			p = NULL;
		} else {
			q = p;
			p = p->next;
		}
	}
	edge->next = q->next;
	q->next = edge;
}

int yNext(int k, int cnt, POINT3D pts[]) {
	int j;

	if ((k + 1) > (cnt - 1)) {
		j = 0;
	} else {
		j = k + 1;
	}

	while (pts[k].y == pts[j].y) {
		if ((j + 1) > (cnt - 1)) {
			j = 0;
		} else {
			j++;
		}
	}

	return pts[j].y;
}

void makeEdgeRec(POINT3D lower, POINT3D upper, int yComp, Edge *edge, Edge *edges[]) {
	edge->dxPerScan = (float)(upper.x - lower.x) / (upper.y - lower.y);
	edge->xIntersect = lower.x;
	if (upper.y < yComp) {
		edge->yUpper = upper.y - 1;
	} else {
		edge->yUpper = upper.y;
	}
	insertEdge(edges[(int)lower.y], edge);
}

void buildEdgeList(int cnt, POINT3D pts[], Edge *edges[]) {
	Edge *edge;
	POINT3D v1, v2;
	int i, yPrev = pts[cnt - 2].y;

	v1.x = pts[cnt - 1].x;
	v1.y = pts[cnt - 1].y;
	for (i = 0; i < cnt; i++) {
		v2 = pts[i];
		if (v1.y != v2.y) {
			edge = (Edge *)malloc(sizeof(Edge));
			if (v1.y < v2.y) {
				makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
			} else {
				makeEdgeRec(v2, v1, yPrev, edge, edges);
			}
		}
		yPrev = v1.y;
		v1 = v2;
	}
}

void buildActiveList(int scan, Edge *active, Edge *edges[]) {
	Edge *p, *q;

	p = edges[scan]->next;
	while (p) {
		q = p->next;
		insertEdge(active, p);
		p = q;
	}
}

void fillScan(int scan, Edge *active, HWND sHwnd, COLORREF COLOR) {
	Edge *p1, *p2;
	int i;

	p1 = active->next;
	while (p1) {
		p2 = p1->next;
		for (i = p1->xIntersect; i < p2->xIntersect; i++) {
			setPixel(i, scan, COLOR, sHwnd);
		}
		p1 = p2->next;
	}
}

void deleteAfter(Edge *q) {
	Edge *p = q->next;

	q->next = p->next;
	free(p);
}

void updateActiveList(int scan, Edge *active) {
	Edge *q = active, *p = active->next;

	while (p) {
		if (scan >= p->yUpper) {
			p = p->next;
			deleteAfter(q);
		} else {
			p->xIntersect = p->xIntersect + p->dxPerScan;
			q = p;
			p = p->next;
		}
	}
}

void resortActiveList(Edge *active) {
	Edge *q, *p = active->next;

	active->next = NULL;
	while (p) {
		q = p->next;
		insertEdge(active, p);
		p = q;
	}
}

// TODO: Update edge count to something less static
void scanFill(int cnt, POINT3D pts[], HWND sHwnd, COLORREF color) {
	Edge *edges[600], *active;
	int i, scan;

	for (i = 0; i < 600; i++) {
		edges[i] = (Edge *)malloc(sizeof(Edge));
		edges[i]->next = NULL;
	}
	buildEdgeList(cnt, pts, edges);
	active = (Edge *)malloc(sizeof(Edge));
	active->next = NULL;

	for (scan = 0; scan < 600; scan++) {
		buildActiveList(scan, active, edges);
		if (active->next) {
			fillScan(scan, active, sHwnd, color);
			updateActiveList(scan, active);
			resortActiveList(active);
		}
	}
	/* Free edge records that have been malloc'ed */
	for (i = 0; i < 600; i++) {
		free(edges[i]);
	}
}