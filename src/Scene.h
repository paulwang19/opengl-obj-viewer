#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <GL/freeglut.h>
#include "Model.h"
#include "Logger.h"
#include "Camera.h"

enum Operation {
	RESET,               // 重置
    MOVE_X,              // 沿 X 軸正向移動
    MOVE_Y,              // 沿 Y 軸正向移動
    MOVE_Z,              // 沿 Z 軸正向移動
    MOVE_NEGATIVE_X,     // 沿 X 軸負向移動
    MOVE_NEGATIVE_Y,     // 沿 Y 軸負向移動
    MOVE_NEGATIVE_Z,     // 沿 Z 軸負向移動
    ROTATE_X,            // 繞 X 軸正向旋轉
    ROTATE_Y,            // 繞 Y 軸正向旋轉
    ROTATE_Z,            // 繞 Z 軸正向旋轉
    ROTATE_NEGATIVE_X,   // 繞 X 軸負向旋轉
    ROTATE_NEGATIVE_Y,   // 繞 Y 軸負向旋轉
    ROTATE_NEGATIVE_Z,   // 繞 Z 軸負向旋轉
    INCREASE_SCALE,      // 放大
    DECREASE_SCALE       // 縮小
};

class Scene {
public:
    Scene(Camera* camera);
    ~Scene();

    void initialize(int width, int height); // 初始化場景
    int addModel(const Model& model);  // 添加模型到場景
	void chooseCurrentShowModel(std::string modelName); // 選擇當前顯示的模型
    void operateCurrentModel(Operation operation);
	void setRenderMode(RenderMode mode) { renderMode = mode; } // 設置渲染模式
	void setColorMode(ColorMode mode) { colorMode = mode; } // 設置顏色模式
	void setCameraFocusModel(); // 設置攝影機對準於當前模型

    void render() const; // 渲染場景

private:
    Camera* camera;
    RenderMode renderMode;
    ColorMode colorMode;
    std::vector<Model> models; // 場景中的模型
	int currentShowModelIndex; // 當前渲染的模型索引

	void adjustCameraToCurrentModel(); // 調整攝影機位置以適應當前模型
};

#endif // SCENE_H