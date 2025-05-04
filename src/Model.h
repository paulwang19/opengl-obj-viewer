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

    
	std::string getName() const { return name; } // 獲取模型名稱
	BoundingBox getBoundingBox() const { return boundingBox; } // 獲取邊界框

	void reset(); // 重置模型位置、旋轉和縮放
	void moveX(); // 沿 X 軸移動
	void moveY(); // 沿 Y 軸移動
	void moveZ(); // 沿 Z 軸移動
	void moveNegativeX(); // 沿 -X 軸移動
	void moveNegativeY(); // 沿 -Y 軸移動
	void moveNegativeZ(); // 沿 -Z 軸移動
	void rotateX();
	void rotateY();
	void rotateZ();
	void rotateNegativeX();
	void rotateNegativeY();
	void rotateNegativeZ();
	void increaseScale();
	void decreaseScale();

	void setMoveDelta(float delta) { moveDelta = delta; } // 設置移動變化量
	void setRotDelta(float delta) { rotDelta = delta; } // 設置旋轉變化量
	void setScaleDelta(float delta) { scaleDelta = delta; } // 設置縮放變化量

    void render(RenderMode renderMode, ColorMode colorMode) const;  // 渲染模型

private:
	std::string name; // 模型名稱
    std::vector<Vector3D> vertices; // 儲存頂點座標
    std::vector<Face> faces; // 儲存面的頂點索引
    Vector3D position; // 模型位置
    float rotX, rotY, rotZ;  // 模型旋轉角度
    float scale; // 模型縮放比例
	float baseColor[3]; // 基本 RGB 底色 (用於單色模式)
	BoundingBox boundingBox; // 邊界框

	float moveDelta;  // 每次調整移動的變化量
	float rotDelta;  // 每次調整旋轉的變化量
	float scaleDelta;  // 每次調整縮放的變化量

	void initializeFace(); // 初始化面
	void initializeBoundingBox(); // 初始化邊界框

    void setupLighting() const; // 設置光照
	void renderPoint(ColorMode colorMode) const; // 渲染點
	void renderLine(ColorMode colorMode) const; // 渲染線
	void renderFace(ColorMode colorMode) const; // 渲染面
};

#endif // MODEL_H