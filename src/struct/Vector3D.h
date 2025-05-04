#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

class Vector3D {
public:
    float x, y, z;

    Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

	// 向量加法
	Vector3D operator+(const Vector3D& other) const {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

    // 向量減法
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // 向量取負
    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    // 係數乘法
	Vector3D operator*(float scalar) const {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

    // 向量 +=
    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // 向量 -=
    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // 向量叉積
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // 單位化
    Vector3D normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length < 1e-6f) return *this; // 避免除以零
        return Vector3D(x / length, y / length, z / length);
    }
};

#endif // VECTOR3D_H