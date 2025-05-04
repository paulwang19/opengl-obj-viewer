#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3D.h"

struct BoundingBox {
    Vector3D min; // �̤p�y��
    Vector3D max; // �̤j�y��
    Vector3D center; // �����I
    float width; // X �b�d��
    float height; // Y �b�d��
    float depth; // Z �b�d��
};

#endif // BOUNDING_BOX_H