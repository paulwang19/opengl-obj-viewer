#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3D.h"

struct BoundingBox {
    Vector3D min; // 最小座標
    Vector3D max; // 最大座標
    Vector3D center; // 中心點
    float width; // X 軸範圍
    float height; // Y 軸範圍
    float depth; // Z 軸範圍
};

#endif // BOUNDING_BOX_H