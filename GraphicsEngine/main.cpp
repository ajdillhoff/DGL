#include <windows.h>
#include <iostream>
#include <cmath>
#include "ajd_graphics.h"
#include "ajd_render.h"
#include <gl/GL.h>

using namespace std;

#define PI 3.14

const char g_szClassName[] = "myWindowClass";

void ajd_main(HWND);

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Graphics Engine AJD",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

		ajd_main(hwnd);
	}
	return Msg.wParam;
}

void ajd_main(HWND hwnd) {
	ARender a;
	a.Init(800, 600, hwnd);
	a.Render();

	return;
}

//int main() {
//	////Get a console handle
//	HWND myconsole = GetConsoleWindow();
//
//	//int pixel = 0;
//
//	////Choose any color
//	//COLORREF COLOR = RGB(255, 255, 255);
//
//	//wcpt2 p;
//	//p.x = 0;
//	//p.y = 0;
//
//	//wcpt2 q;
//	//q.x = 50;
//	//q.y = 100;
//
//	//wcpt2 r;
//	//r.x = 100;
//	//r.y = 0;
//
//	//wcpt2 t;
//	//t.x = 75;
//	//t.y = 75;
//
//	//wcpt2 *pts = (wcpt2*)malloc(4 * sizeof(wcpt2));
//	//pts[0] = p;
//	//pts[1] = q;
//	//pts[2] = t;
//	//pts[3] = r;
//
//	//pBufPolyLine(4, pts, myconsole, COLOR);
//	//cin.ignore();
//	//free(pts);
//	ARender a;
//	a.Init(800, 600, myconsole);
//	a.Render();
//
//	//ReleaseDC(myconsole, mydc);
//	return 0;
//}