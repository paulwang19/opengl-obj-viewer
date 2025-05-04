#include "Camera.h"
#include <GL/freeglut.h>
#include <cmath>

Camera::Camera() : moveFactor(0.1f), revolveFactor(0.1f) {
	position = { 0.0f, 0.0f, 5.0f };
	target = { 0.0f, 0.0f, 0.0f };
	up = { 0.0f, 1.0f, 0.0f };
	forward = (target - position).normalize(); // 計算向前向量
}

Camera::~Camera() {}

void Camera::changeTarget(float x, float y, float z) {
	target.x = x;
	target.y = y;
	target.z = z;
	forward = (target - position).normalize(); // 更新向前向量
}

void Camera::reset() {  // 重設攝影機位置
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	forward = (target - position).normalize(); // 更新向前向量
}

void Camera::moveForward() {
	position += (target - position).normalize() * moveFactor;
}

void Camera::moveBackward() {
	position -= (target - position).normalize() * moveFactor;
}

void Camera::moveRight() {
	Vector3D dir = forward.cross(up).normalize();
	position += dir * moveFactor;
	target += dir * moveFactor;
}

void Camera::moveLeft() {
	Vector3D dir = forward.cross(up).normalize();
	position -= dir * moveFactor;
	target -= dir * moveFactor;
}

void Camera::moveUp() {
	Vector3D dir = forward.cross(up.cross(forward)).normalize();
	position += dir * moveFactor;
	target += dir * moveFactor;
}

void Camera::moveDown() {
	Vector3D dir = forward.cross(up.cross(forward)).normalize();
	position -= dir * moveFactor;
	target -= dir * moveFactor;
}

void Camera::revolveRight() {
	position += (target - position).cross(up).normalize() * revolveFactor;
	forward = (target - position).normalize();  // 公轉後更新向前向量
}

void Camera::revolveLeft() {
	position -= (target - position).cross(up).normalize() * revolveFactor;
	forward = (target - position).normalize();  // 公轉後更新向前向量
}

void Camera::revolveUp() {
	position += forward.cross(up.cross(target - position)).normalize() * revolveFactor;
	forward = (target - position).normalize();  // 公轉後更新向前向量
}

void Camera::revolveDown() {
	position -= forward.cross(up.cross(target - position)).normalize() * revolveFactor;
	forward = (target - position).normalize();  // 公轉後更新向前向量
}

void Camera::applyCamera() const {
	gluLookAt(
		position.x, position.y, position.z, // 攝影機位置
		target.x, target.y, target.z, // 目標點
		up.x, up.y, up.z  // 上向量
	);
}
