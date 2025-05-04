#ifndef CAMERA_H
#define CAMERA_H

#include "struct/Vector3D.h"

class Camera {
public:
    Camera();
    ~Camera();

	void setDefaultPosition(float x, float y, float z) { defaultPosition = { x, y, z }; }
	void setDefaultTarget(float x, float y, float z) { defaultTarget = { x, y, z }; }
	void setDefaultUp(float x, float y, float z) { defaultUp = { x, y, z }; }
	void setMoveFactor(float factor) { moveFactor = factor; }
	void setRevolveFactor(float factor) { revolveFactor = factor; }
    void changeTarget(float x, float y, float z);
	void reset();

    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
	void revolveRight();
	void revolveLeft();
	void revolveUp();
    void revolveDown();
	void applyCamera() const;

private:
    Vector3D defaultPosition; // ��v����l��m
    Vector3D defaultTarget; // ��v����l�ؼ�
    Vector3D defaultUp; // ��v����l�W�V�q

    Vector3D position; // ��v����m
    Vector3D target; // �[�ݥؼ�
    Vector3D up; // �W�V�q

	Vector3D forward; // �V�e���ʪ���V
	float moveFactor;  // ���ʳt��
	float revolveFactor; // ����t��
};

#endif // CAMERA_H