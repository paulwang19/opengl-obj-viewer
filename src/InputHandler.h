#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <map>
#include <GL/freeglut.h>
#include "Camera.h"
#include "Scene.h"
#include "Logger.h"

class InputHandler {
public:
    InputHandler(Camera* camera, Scene* scene);
    ~InputHandler();

    // 處理輸入
    void handleKeyboardPress(unsigned char key, int x, int y);
    void handSpecialKeyPress(int key, int x, int y);
    void handleMouseClick(int button, int state, int x, int y);

    // 每幀更新攝影機
    // void update(float deltaTime);

private:
    Camera* camera; // 攝影機指針
    Scene* scene; // 場景指針
    //std::map<unsigned char, bool> keyStates; // 鍵盤狀態
    //bool mousePressed; // 滑鼠左鍵是否按下
    //float lastX, lastY; // 上次滑鼠位置
    //float yaw, pitch; // 攝影機旋轉角度
    //float moveSpeed; // 移動速度
    //float mouseSensitivity; // 滑鼠靈敏度
};

#endif // INPUT_HANDLER_H