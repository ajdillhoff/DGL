#include "ajd_camera.h"
#include <math.h>

Matrix& Camera::GetWorldToCameraMatrix() {
	return WorldToCameraMatrix;
}

Matrix& Camera::GetCameraToProjectionMatrix() {
	return CameraToProjectionMatrix;
}

Matrix& Camera::GetProjectionToViewMatrix() {
	return ViewProjectionMatrix;
}

void Camera::Init(const POINT3D& pos, const Vector4D& dir, float fov, float width, float height) {
	ViewportWidth = width;
	ViewportHeight = height;
	ViewDistance = 1 / tan(DEG2RAD * (fov/2));

	position = pos;
	direction = dir;

	// Default to the identity matrix
	WorldToCameraMatrix.Identity();
	CameraToProjectionMatrix.Identity();
	ViewProjectionMatrix.Identity();

	SetWorldToCameraMatrix();
	SetCameraToProjectionMatrix();
	SetProjectionToViewMatrix();
}

void Camera::SetWorldToCameraMatrix() {
	Matrix& mat = GetWorldToCameraMatrix();
	Matrix translatemat;
	Matrix rotmat;
	translatemat.Identity();
	rotmat.Identity();
	BuildTranslateMatrix(translatemat, -position.x, -position.y, -position.z);
	Build_XYZ_RotationMatrix(rotmat, -direction.x, 0.0, 0.0);//x
	Build_XYZ_RotationMatrix(rotmat, 0.0, -direction.y, 0.0);//y
	Build_XYZ_RotationMatrix(rotmat, 0.0, 0.0, -direction.z);//z

	mat = translatemat * rotmat;
}

/*
* SetCameraToProjectionMatrix
* ---------------------------
* Precondition: CameraToProjectionMatrix exists
* Postcondition: CameraToProjectionMatrix is set to the basic projection matrix
*
* | 1 0  0  0 |
* | 0 1  0  0 |
* | 0 0  1  0 |
* | 0 0 1/d 0 |
*/
void Camera::SetCameraToProjectionMatrix() {
	CameraToProjectionMatrix._11 = 1;
	CameraToProjectionMatrix._43 = 1 / ViewDistance;
	CameraToProjectionMatrix._44 = 0;
}

// TODO: Figure this out on paper
void Camera::SetProjectionToViewMatrix() {
	float w = (float)(ViewportWidth - 1) / 2;
	float h = (float)(ViewportHeight - 1) / 2;

	Matrix &mat = GetProjectionToViewMatrix();
	mat._11 = w;
	mat._22 = -h;
	mat._41 = w;
	mat._42 = h;
}

void Camera::BuildTranslateMatrix(Matrix& retMatrix, float x, float y, float z) {
	//retMatrix.Identity();
	retMatrix._41 = x;
	retMatrix._42 = y;
	retMatrix._43 = z;
}

void Camera::Build_XYZ_RotationMatrix(Matrix& retMatrix, float x, float y, float z) {
	float _x = DEG2RAD * x;
	float _y = DEG2RAD * y;
	float _z = DEG2RAD * z;

	//retMatrix.Identity();
	//rotate around x axis
	//| 1  0    0  0 |
	//| 0 cosa sina 0|
	//| 0 -sina cosa 0|
	//| 0 0      0    1|
	if (fabs(_x) > EPSILON) {
		retMatrix._22 = cos(_x);
		retMatrix._23 = sin(_x);
		retMatrix._32 = -retMatrix._23;
		retMatrix._33 = retMatrix._22;
	}
	//rotate around y axis
	//| cosa 0 -sina 0|
	//| 0    1   0   0|
	//| sina 0 cosa 0 |
	//| 0    0  0   1|
	else if (fabs(_y) > EPSILON) {
		retMatrix._11 = cos(_y);
		retMatrix._13 = -sin(_y);
		retMatrix._31 = -retMatrix._13;
		retMatrix._33 = retMatrix._11;
	}
	//rotate around z axis
	//| cosa sina 0 0 |
	//| -sina cosa 0 0|
	//| 0   0   1  0|
	//|0    0  0  1|
	else if (fabs(_z) > EPSILON) {
		retMatrix._11 = cos(_z);
		retMatrix._12 = sin(_z);
		retMatrix._21 = -retMatrix._12;
		retMatrix._22 = retMatrix._11;
	}
}
