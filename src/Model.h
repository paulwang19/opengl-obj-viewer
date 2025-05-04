#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "ObjLoader.h"
#include "Logger.h"
#include "struct/Vector3D.h"
#include "struct/Face.h"
#include "struct/BoundingBox.h"

enum class RenderMode { POINT, LINE, FACE };
enum class ColorMode { SINGLE, RANDOM };

class Model {
public:
    Model(std::string filename, std::string modelName);
    ~Model();

    
	std::string getName() const { return name; } // ����ҫ��W��
	BoundingBox getBoundingBox() const { return boundingBox; } // �����ɮ�

	void reset(); // ���m�ҫ���m�B����M�Y��
	void moveX(); // �u X �b����
	void moveY(); // �u Y �b����
	void moveZ(); // �u Z �b����
	void moveNegativeX(); // �u -X �b����
	void moveNegativeY(); // �u -Y �b����
	void moveNegativeZ(); // �u -Z �b����
	void rotateX();
	void rotateY();
	void rotateZ();
	void rotateNegativeX();
	void rotateNegativeY();
	void rotateNegativeZ();
	void increaseScale();
	void decreaseScale();

	void setMoveDelta(float delta) { moveDelta = delta; } // �]�m�����ܤƶq
	void setRotDelta(float delta) { rotDelta = delta; } // �]�m�����ܤƶq
	void setScaleDelta(float delta) { scaleDelta = delta; } // �]�m�Y���ܤƶq

    void render(RenderMode renderMode, ColorMode colorMode) const;  // ��V�ҫ�

private:
	std::string name; // �ҫ��W��
    std::vector<Vector3D> vertices; // �x�s���I�y��
    std::vector<Face> faces; // �x�s�������I����
    Vector3D position; // �ҫ���m
    float rotX, rotY, rotZ;  // �ҫ����ਤ��
    float scale; // �ҫ��Y����
	float baseColor[3]; // �� RGB ���� (�Ω���Ҧ�)
	BoundingBox boundingBox; // ��ɮ�

	float moveDelta;  // �C���վ㲾�ʪ��ܤƶq
	float rotDelta;  // �C���վ���઺�ܤƶq
	float scaleDelta;  // �C���վ��Y���ܤƶq

	void initializeFace(); // ��l�ƭ�
	void initializeBoundingBox(); // ��l����ɮ�

    void setupLighting() const; // �]�m����
	void renderPoint(ColorMode colorMode) const; // ��V�I
	void renderLine(ColorMode colorMode) const; // ��V�u
	void renderFace(ColorMode colorMode) const; // ��V��
};

#endif // MODEL_H