#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

class Vector3D {
public:
    float x, y, z;

    Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

	// �V�q�[�k
	Vector3D operator+(const Vector3D& other) const {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

    // �V�q��k
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // �V�q���t
    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    // �Y�ƭ��k
	Vector3D operator*(float scalar) const {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

    // �V�q +=
    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // �V�q -=
    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // �V�q�e�n
    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // ����
    Vector3D normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length < 1e-6f) return *this; // �קK���H�s
        return Vector3D(x / length, y / length, z / length);
    }
};

#endif // VECTOR3D_H