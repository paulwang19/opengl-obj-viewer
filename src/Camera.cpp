#include "Camera.h"
#include <GL/freeglut.h>
#include <cmath>

Camera::Camera() : moveFactor(0.1f), revolveFactor(0.1f) {
	position = { 0.0f, 0.0f, 5.0f };
	target = { 0.0f, 0.0f, 0.0f };
	up = { 0.0f, 1.0f, 0.0f };
	forward = (target - position).normalize(); // �p��V�e�V�q
}

Camera::~Camera() {}

void Camera::changeTarget(float x, float y, float z) {
	target.x = x;
	target.y = y;
	target.z = z;
	forward = (target - position).normalize(); // ��s�V�e�V�q
}

void Camera::reset() {  // ���]��v����m
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	forward = (target - position).normalize(); // ��s�V�e�V�q
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
	forward = (target - position).normalize();  // ������s�V�e�V�q
}

void Camera::revolveLeft() {
	position -= (target - position).cross(up).normalize() * revolveFactor;
	forward = (target - position).normalize();  // ������s�V�e�V�q
}

void Camera::revolveUp() {
	position += forward.cross(up.cross(target - position)).normalize() * revolveFactor;
	forward = (target - position).normalize();  // ������s�V�e�V�q
}

void Camera::revolveDown() {
	position -= forward.cross(up.cross(target - position)).normalize() * revolveFactor;
	forward = (target - position).normalize();  // ������s�V�e�V�q
}

void Camera::applyCamera() const {
	gluLookAt(
		position.x, position.y, position.z, // ��v����m
		target.x, target.y, target.z, // �ؼ��I
		up.x, up.y, up.z  // �W�V�q
	);
}
