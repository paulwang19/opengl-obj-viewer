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

    // �B�z��J
    void handleKeyboardPress(unsigned char key, int x, int y);
    void handSpecialKeyPress(int key, int x, int y);
    void handleMouseClick(int button, int state, int x, int y);

    // �C�V��s��v��
    // void update(float deltaTime);

private:
    Camera* camera; // ��v�����w
    Scene* scene; // �������w
    //std::map<unsigned char, bool> keyStates; // ��L���A
    //bool mousePressed; // �ƹ�����O�_���U
    //float lastX, lastY; // �W���ƹ���m
    //float yaw, pitch; // ��v�����ਤ��
    //float moveSpeed; // ���ʳt��
    //float mouseSensitivity; // �ƹ��F�ӫ�
};

#endif // INPUT_HANDLER_H