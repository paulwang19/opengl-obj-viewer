#include "Model.h"
#include <GL/freeglut.h>
#include <cmath>
#include "exception/UnexpectedEventException.h"

Model::Model(std::string filename, std::string modelName)
    : name(modelName), position{0.0, 0.0, 0.0}, rotX(0.0), rotY(0.0), rotZ(0.0), scale(1.0),
    baseColor{0.0, 0.0, 0.0}, moveDelta(1.0), rotDelta(5.0), scaleDelta(0.05) {
    ObjLoader loader;
    loader.loadObj(filename);
    vertices = loader.getVertices();
    faces = loader.getFaces();

    if (vertices.empty()) {
        Logger::getInstance().logError("Model initialization failed: No vertices provided");
        throw UnexpectedEventException("No vertices available");
    }

    // 隨機化基本顏色
    baseColor[0] = static_cast<float>(std::rand()) / RAND_MAX; // R
    baseColor[1] = static_cast<float>(std::rand()) / RAND_MAX; // G
    baseColor[2] = static_cast<float>(std::rand()) / RAND_MAX; // B

    initializeFace();
    initializeBoundingBox();
    Logger::getInstance().logInfo("Model initialized with " + std::to_string(vertices.size()) + " vertices and " + std::to_string(faces.size()) + " faces");
}

Model::~Model() {}

void Model::initializeFace() {
    // 為每個面計算法向量
    for (auto& face : faces) {
        // 為每個面隨機顏色
        face.color[0] = static_cast<float>(std::rand()) / RAND_MAX; // R
        face.color[1] = static_cast<float>(std::rand()) / RAND_MAX; // G
        face.color[2] = static_cast<float>(std::rand()) / RAND_MAX; // B

        if (face.vertex1Index < vertices.size() && face.vertex2Index < vertices.size() && face.vertex3Index < vertices.size()) {
            Vector3D v1 = vertices[face.vertex1Index];
            Vector3D v2 = vertices[face.vertex2Index];
            Vector3D v3 = vertices[face.vertex3Index];

            // 計算邊向量
            Vector3D edge1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
            Vector3D edge2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };

            // 叉積計算法向量
            face.normal.x = edge1.y * edge2.z - edge1.z * edge2.y;
            face.normal.y = edge1.z * edge2.x - edge1.x * edge2.z;
            face.normal.z = edge1.x * edge2.y - edge1.y * edge2.x;

            // 標準化法向量
            float length = std::sqrt(face.normal.x * face.normal.x + face.normal.y * face.normal.y + face.normal.z * face.normal.z);
            if (length > 0) {
                face.normal.x /= length;
                face.normal.y /= length;
                face.normal.z /= length;
            }
            else {
                face.normal = { 0.0f, 0.0f, 1.0f }; // 預設法向量
            }
        }
        else {
            Logger::getInstance().logWarning("Invalid vertex indices in face, using default normal");
            face.normal = { 0.0f, 0.0f, 1.0f };
        }
    }
}

void Model::initializeBoundingBox() {
    boundingBox = {
        {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()},
        {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()},
        {0.0f, 0.0f, 0.0f},
        0.0f, 0.0f, 0.0f
    };

    if (vertices.empty()) {
        throw UnexpectedEventException("No vertices available to calculate bounding box");
    }

    for (const auto& vertex : vertices) {
        boundingBox.min.x = std::min(boundingBox.min.x, vertex.x);
        boundingBox.min.y = std::min(boundingBox.min.y, vertex.y);
        boundingBox.min.z = std::min(boundingBox.min.z, vertex.z);
        boundingBox.max.x = std::max(boundingBox.max.x, vertex.x);
        boundingBox.max.y = std::max(boundingBox.max.y, vertex.y);
        boundingBox.max.z = std::max(boundingBox.max.z, vertex.z);
    }

    // 計算中心
    boundingBox.center.x = (boundingBox.min.x + boundingBox.max.x) / 2.0f;
    boundingBox.center.y = (boundingBox.min.y + boundingBox.max.y) / 2.0f;
    boundingBox.center.z = (boundingBox.min.z + boundingBox.max.z) / 2.0f;

    // 計算尺寸
    boundingBox.width = boundingBox.max.x - boundingBox.min.x;
    boundingBox.height = boundingBox.max.y - boundingBox.min.y;
    boundingBox.depth = boundingBox.max.z - boundingBox.min.z;
}

void Model::reset() {
	position = { 0.0f, 0.0f, 0.0f };
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scale = 1.0f;
}

void Model::moveX() {
	position.x += moveDelta;
}

void Model::moveY() {
	position.y += moveDelta;
}

void Model::moveZ() {
	position.z += moveDelta;
}

void Model::moveNegativeX() {
	position.x -= moveDelta;
}

void Model::moveNegativeY() {
	position.y -= moveDelta;
}

void Model::moveNegativeZ() {
	position.z -= moveDelta;
}

void Model::rotateX() {
	rotX += rotDelta;
	if (rotX > 360.0f) {
		rotX -= 360.0f;
	}
}

void Model::rotateY() {
    rotY += rotDelta;
    if (rotY > 360.0f) {
        rotY -= 360.0f;
    }
}

void Model::rotateZ() {
    rotZ += rotDelta;
    if (rotZ > 360.0f) {
        rotZ -= 360.0f;
    }
}

void Model::rotateNegativeX() {
    rotX -= rotDelta;
    if (rotX < 0.0f) {
        rotX += 360.0f;
    }
}

void Model::rotateNegativeY() {
    rotY -= rotDelta;
    if (rotY < 0.0f) {
        rotY += 360.0f;
    }
}

void Model::rotateNegativeZ() {
    rotZ -= rotDelta;
    if (rotZ < 0.0f) {
        rotZ += 360.0f;
    }
}

void Model::increaseScale() {
    scale += scaleDelta;
    if (scale > 10.0) {
        scale = 10.0;
    }
}

void Model::decreaseScale() {
    scale -= scaleDelta;
    if (scale < 0.05) {
        scale = 0.05;
    }
}

void Model::render(RenderMode renderMode, ColorMode colorMode) const {
    glPushMatrix(); // 保存當前矩陣狀態

    // 移動立方體到指定位置
	glTranslatef(position.x, position.y, position.z);

    // 按照指定角度旋轉立方體
    glRotatef(rotX, 1.0f, 0.0f, 0.0f); // 繞 X 軸旋轉
    glRotatef(rotY, 0.0f, 1.0f, 0.0f); // 繞 Y 軸旋轉
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f); // 繞 Z 軸旋轉

    // 應用縮放比例
    glScalef(scale, scale, scale); // 在 X, Y, Z 三個方向上均勻縮放
    
	// 根據渲染模式設置 OpenGL 渲染模式
    if (renderMode == RenderMode::POINT) {
		renderPoint(colorMode);
    }
	else if (renderMode == RenderMode::LINE) {
        renderLine(colorMode);
	}
	else { // renderMode == RenderMode::FACE
		renderFace(colorMode);
	}
    glPopMatrix();  // 恢復矩陣狀態
}

void Model::setupLighting() const {
    // 啟用光照
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 設置光源屬性（方向光）
    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // 方向光 (x,y,z,0)
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // 環境光
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // 漫反射光
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    // 設置材質屬性（與面顏色結合）
    GLfloat materialSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 無高光
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f); // 無高光
}

void Model::renderPoint(ColorMode colorMode) const {
    glPointSize(2.0f); // 設置點大小
    glBegin(GL_POINTS);
    for (const auto& face : faces) {
        // 依據渲染模式設置材質顏色（與光照結合）
        float color[3];
        if (colorMode == ColorMode::SINGLE) {
            std::copy(std::begin(baseColor), std::end(baseColor), std::begin(color));
        }
        else {  // colorMode == ColorMode::RANDOM
            std::copy(std::begin(face.color), std::end(face.color), std::begin(color));
        }

        // 繪製點
        glColor3f(color[0], color[1], color[2]);
        glVertex3f(vertices.at(face.vertex1Index).x, vertices.at(face.vertex1Index).y, vertices.at(face.vertex1Index).z);
        glVertex3f(vertices.at(face.vertex2Index).x, vertices.at(face.vertex2Index).y, vertices.at(face.vertex2Index).z);
        glVertex3f(vertices.at(face.vertex3Index).x, vertices.at(face.vertex3Index).y, vertices.at(face.vertex3Index).z);
    }
    glEnd();
}

void Model::renderLine(ColorMode colorMode) const {
    glLineWidth(2.0f); // 設置線寬
    glBegin(GL_LINES);
    for (const auto& face : faces) {
        // 依據渲染模式設置材質顏色（與光照結合）
        float color[3];
        if (colorMode == ColorMode::SINGLE) {
            std::copy(std::begin(baseColor), std::end(baseColor), std::begin(color));
        }
        else {  // colorMode == ColorMode::RANDOM
            std::copy(std::begin(face.color), std::end(face.color), std::begin(color));
        }

        // 繪製三角形的三條邊
        glColor3f(color[0], color[1], color[2]);

        // 邊 1: v1 -> v2
        glVertex3f(vertices.at(face.vertex1Index).x, vertices.at(face.vertex1Index).y, vertices.at(face.vertex1Index).z);
        glVertex3f(vertices.at(face.vertex2Index).x, vertices.at(face.vertex2Index).y, vertices.at(face.vertex2Index).z);
        // 邊 2: v2 -> v3
        glVertex3f(vertices.at(face.vertex2Index).x, vertices.at(face.vertex2Index).y, vertices.at(face.vertex2Index).z);
        glVertex3f(vertices.at(face.vertex3Index).x, vertices.at(face.vertex3Index).y, vertices.at(face.vertex3Index).z);
        // 邊 3: v3 -> v1
        glVertex3f(vertices.at(face.vertex3Index).x, vertices.at(face.vertex3Index).y, vertices.at(face.vertex3Index).z);
        glVertex3f(vertices.at(face.vertex1Index).x, vertices.at(face.vertex1Index).y, vertices.at(face.vertex1Index).z);
    }
    glEnd();
}

void Model::renderFace(ColorMode colorMode) const {
    setupLighting();
    glBegin(GL_TRIANGLES);
    for (const auto& face : faces) {
        // 依據渲染模式設置材質顏色（與光照結合）
        float color[3];
        if (colorMode == ColorMode::SINGLE) {
            std::copy(std::begin(baseColor), std::end(baseColor), std::begin(color));
        }
        else {  // colorMode == ColorMode::RANDOM
            std::copy(std::begin(face.color), std::end(face.color), std::begin(color));
        }

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

        // 設置法向量
        glNormal3f(face.normal.x, face.normal.y, face.normal.z);

        glVertex3f(
            vertices.at(face.vertex1Index).x,
            vertices.at(face.vertex1Index).y,
            vertices.at(face.vertex1Index).z
        );
        glVertex3f(
            vertices.at(face.vertex2Index).x,
            vertices.at(face.vertex2Index).y,
            vertices.at(face.vertex2Index).z
        );
        glVertex3f(
            vertices.at(face.vertex3Index).x,
            vertices.at(face.vertex3Index).y,
            vertices.at(face.vertex3Index).z
        );
    }
    glEnd();

    // 禁用光照和法向量標準化
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
}