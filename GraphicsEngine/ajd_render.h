
#include "ajd_gbase.h"
#include "ajd_camera.h"

class ARender {
public:
	HWND hwnd;
	Camera camera;
	void Init(float, float, HWND);
	void Render();
};