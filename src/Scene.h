#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <GL/freeglut.h>
#include "Model.h"
#include "Logger.h"
#include "Camera.h"

enum Operation {
	RESET,               // ���m
    MOVE_X,              // �u X �b���V����
    MOVE_Y,              // �u Y �b���V����
    MOVE_Z,              // �u Z �b���V����
    MOVE_NEGATIVE_X,     // �u X �b�t�V����
    MOVE_NEGATIVE_Y,     // �u Y �b�t�V����
    MOVE_NEGATIVE_Z,     // �u Z �b�t�V����
    ROTATE_X,            // ¶ X �b���V����
    ROTATE_Y,            // ¶ Y �b���V����
    ROTATE_Z,            // ¶ Z �b���V����
    ROTATE_NEGATIVE_X,   // ¶ X �b�t�V����
    ROTATE_NEGATIVE_Y,   // ¶ Y �b�t�V����
    ROTATE_NEGATIVE_Z,   // ¶ Z �b�t�V����
    INCREASE_SCALE,      // ��j
    DECREASE_SCALE       // �Y�p
};

class Scene {
public:
    Scene(Camera* camera);
    ~Scene();

    void initialize(int width, int height); // ��l�Ƴ���
    int addModel(const Model& model);  // �K�[�ҫ������
	void chooseCurrentShowModel(std::string modelName); // ��ܷ�e��ܪ��ҫ�
    void operateCurrentModel(Operation operation);
	void setRenderMode(RenderMode mode) { renderMode = mode; } // �]�m��V�Ҧ�
	void setColorMode(ColorMode mode) { colorMode = mode; } // �]�m�C��Ҧ�
	void setCameraFocusModel(); // �]�m��v����ǩ��e�ҫ�

    void render() const; // ��V����

private:
    Camera* camera;
    RenderMode renderMode;
    ColorMode colorMode;
    std::vector<Model> models; // ���������ҫ�
	int currentShowModelIndex; // ��e��V���ҫ�����

	void adjustCameraToCurrentModel(); // �վ���v����m�H�A����e�ҫ�
};

#endif // SCENE_H