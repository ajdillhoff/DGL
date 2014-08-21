
#include "ajd_gbase.h"

#define EPSILON 0.0001f

class Camera {
public:
	POINT3D position;
	Vector4D direction;
	float ViewportWidth;
	float ViewportHeight;
	float ViewDistance;

	Camera() : position(0.0, 0.0, 0.0), direction(0.0, 0.0, 0.0) {}
	void Init(const POINT3D&, const Vector4D&, float, float, float);
	Matrix& GetWorldToCameraMatrix();
	Matrix& GetCameraToProjectionMatrix();
	Matrix& GetProjectionToViewMatrix();
protected:
	void SetWorldToCameraMatrix();
	void SetCameraToProjectionMatrix();
	void SetProjectionToViewMatrix();
	void BuildTranslateMatrix(Matrix&, float, float, float);
	void Build_XYZ_RotationMatrix(Matrix&, float, float, float);
private:
	Matrix WorldToCameraMatrix;
	Matrix CameraToProjectionMatrix;
	Matrix ViewProjectionMatrix;
};