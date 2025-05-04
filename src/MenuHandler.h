#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <GL/freeglut.h>
#include <map>
#include <string>
#include "Scene.h"
#include "Logger.h"

class MenuHandler {
public:
    MenuHandler(Scene* scene);
    ~MenuHandler();

    void initialize();
    void addModelOption(const std::string& modelName);
    void handleMenuSelect(int option);

private:
    enum MenuOption {
        RENDER_POINT = 1,
        RENDER_LINE,
        RENDER_FACE,
        COLOR_SINGLE,
        COLOR_RANDOM,
		MODEL_OPTION_START
    };

    Scene* scene;
    int mainMenu; // �D���
	int modelSubMenu; // �ҫ��l���
	int renderSubMenu; // ��V�Ҧ��l���
	int colorSubMenu; // �C��Ҧ��l���
    
    std::map<int, std::string> modelOptions; // �ҫ��W�٨�s�����M�g
};

#endif // MENU_HANDLER_H