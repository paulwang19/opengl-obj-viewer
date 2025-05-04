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
    Vector3D defaultPosition; // 攝影機初始位置
    Vector3D defaultTarget; // 攝影機初始目標
    Vector3D defaultUp; // 攝影機初始上向量

    Vector3D position; // 攝影機位置
    Vector3D target; // 觀看目標
    Vector3D up; // 上向量

	Vector3D forward; // 向前移動的方向
	float moveFactor;  // 移動速度
	float revolveFactor; // 公轉速度
};

#endif // CAMERA_H