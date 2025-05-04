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
    int mainMenu; // 主菜單
	int modelSubMenu; // 模型子菜單
	int renderSubMenu; // 渲染模式子菜單
	int colorSubMenu; // 顏色模式子菜單
    
    std::map<int, std::string> modelOptions; // 模型名稱到編號的映射
};

#endif // MENU_HANDLER_H