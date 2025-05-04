#ifndef FACE_H
#define FACE_H

#include <vector>

class Face {
public:
	int vertex1Index, vertex2Index, vertex3Index;
	float color[3]; // RGB 顏色
	Vector3D normal; // 法向量

	Face () : vertex1Index(-1), vertex2Index(-1), vertex3Index(-1) {
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
	}

	Face(int vertex1Index, int vertex2Index, int vertex3Index) :
		vertex1Index(vertex1Index), vertex2Index(vertex2Index), vertex3Index(vertex3Index) {
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
	}

	void setColor(float r, float g, float b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
};

#endif // FACE_H