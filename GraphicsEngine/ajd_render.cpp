#include "ajd_render.h"
#include "ajd_gobject.h"
#include "ajd_graphics.h"
#include <algorithm>
#include <vector>

void ARender::Init(float width, float height, HWND sHwnd) {
	hwnd = sHwnd;

	camera = Camera();

	// Set up the camera
	POINT3D cameraPosition = POINT3D(-0.5, 1.25, 0.0);
	Vector4D cameraDirection = Vector4D(15.0, 15.0, 0.0);
	float fov = 90.0;
	camera.Init(cameraPosition, cameraDirection, fov, width, height);
}

void ARender::Render() {

	// Form the projection matrix
	Matrix &mat = camera.GetWorldToCameraMatrix();
	mat *= camera.GetCameraToProjectionMatrix();
	mat *= camera.GetProjectionToViewMatrix();

	// Temp - Make an object
	VERTICES verticesList;
	Vertex v1, v2, v3, v4, v5;
	POINT3D p1, p2, p3, p4, p5;
	POLYGON poly;
	POLYGONLIST pList;

	COLORREF COLOR1 = RGB(255, 0, 255);
	COLORREF COLOR2 = RGB(255, 0, 0);
	COLORREF COLOR3 = RGB(0, 255, 0);
	COLORREF COLOR4 = RGB(0, 0, 255);

	p1 = POINT3D(0.0, 0.0, 0.0);
	p2 = POINT3D(0.5, 1.0, 0.5);
	p3 = POINT3D(1.0, 0.0, 0.0);
	v1.vertex = p1;
	v2.vertex = p2;
	v3.vertex = p3;
	verticesList.push_back(v1);
	verticesList.push_back(v2);
	verticesList.push_back(v3);

	poly.vertexIndices[0] = 0;
	poly.vertexIndices[1] = 1;
	poly.vertexIndices[2] = 2;
	poly.pointlist = &verticesList;
	poly.color = COLOR1;
	pList.push_back(poly);

	p4 = POINT3D(1.0, 0.0, 1.0);
	v4.vertex = p4;
	verticesList.push_back(v4);

	poly.vertexIndices[0] = 2;
	poly.vertexIndices[1] = 1;
	poly.vertexIndices[2] = 3;
	poly.pointlist = &verticesList;
	poly.color = COLOR2;
	pList.push_back(poly);

	p5 = POINT3D(0.0, 0.0, 1.0);
	v5.vertex = p5;
	verticesList.push_back(v5);

	poly.vertexIndices[0] = 3;
	poly.vertexIndices[1] = 1;
	poly.vertexIndices[2] = 4;
	poly.pointlist = &verticesList;
	poly.color = COLOR3;
	pList.push_back(poly);

	poly.vertexIndices[0] = 4;
	poly.vertexIndices[1] = 1;
	poly.vertexIndices[2] = 0;
	poly.pointlist = &verticesList;
	poly.color = COLOR4;
	pList.push_back(poly);

	std::sort(pList.begin(), pList.end(), CSortByAverage());

	// For each object, multiply their vertices
	for (int i = 0; i < verticesList.size(); i++) {
		//float z = verticesList[i].vertex.z;
		verticesList[i].vertex *= mat;
		//verticesList[i].vertex *= 1/verticesList[i].vertex.w;
		//verticesList[i].vertex.z = z;
	}

	// For each object, draw the polygons
	for (int i = 0; i < pList.size(); i++) {
		drawFilledTriangle(verticesList[pList[i].vertexIndices[0]].vertex, verticesList[pList[i].vertexIndices[1]].vertex, verticesList[pList[i].vertexIndices[2]].vertex, hwnd, pList[i].color);
	}
}