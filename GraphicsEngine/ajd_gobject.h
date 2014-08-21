#include "ajd_gbase.h"
#include <vector>

typedef struct ajd_vertex {
	POINT3D vertex;
	Vector4D normal;
} Vertex;

typedef std::vector<Vertex> VERTICES;

typedef struct ajd_polygon {
	int vertexIndices[3];
	VERTICES* pointlist;
	COLORREF color;

	float GetAverageZ() const {
		return (float)(pointlist->at(vertexIndices[0]).vertex.z + pointlist->at(vertexIndices[1]).vertex.z + pointlist->at(vertexIndices[2]).vertex.z) / 3;
	}
} POLYGON;

typedef std::vector<POLYGON> POLYGONLIST;

// Using this sorting class, don't know if I like it
class CSortByAverage {
public:
	bool operator () (const POLYGON& lhs, const POLYGON& rhs) const {
		float av1 = lhs.GetAverageZ();
		float  av2 = rhs.GetAverageZ();
		return av1 > av2;//we need to sort them in descending order
	}
};

class GObject
{
public:
	POLYGONLIST polygonList;
	VERTICES verticesList;
	POINT3D worldPosition;
};