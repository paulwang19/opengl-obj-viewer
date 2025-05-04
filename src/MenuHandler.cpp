#include "MenuHandler.h"
#include "CallBackUtil.h"
#include <stdexcept>

MenuHandler::MenuHandler(Scene* scene)
	: scene(scene), mainMenu(0), modelSubMenu(0), renderSubMenu(0), colorSubMenu(0) {
}

MenuHandler::~MenuHandler() {}

void MenuHandler::initialize() {
	// 創建 Model 子菜單
	modelSubMenu = glutCreateMenu(HandleMenuSelect);

    // 創建 Render Mode 子菜單
    renderSubMenu = glutCreateMenu(HandleMenuSelect);
    glutAddMenuEntry("Point", RENDER_POINT);
    glutAddMenuEntry("Line", RENDER_LINE);
    glutAddMenuEntry("Face", RENDER_FACE);

    // 創建 Color Mode 子菜單
    colorSubMenu = glutCreateMenu(HandleMenuSelect);
    glutAddMenuEntry("Single color", COLOR_SINGLE);
    glutAddMenuEntry("Random colors", COLOR_RANDOM);

    // 創建主菜單
    mainMenu = glutCreateMenu(HandleMenuSelect);
    glutAddSubMenu("Model", modelSubMenu);
    glutAddSubMenu("Render Mode", renderSubMenu);
    glutAddSubMenu("Color Mode", colorSubMenu);

    // 綁定右鍵
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuHandler::addModelOption(const std::string& modelName) {
	int nextOptionID = MODEL_OPTION_START + modelOptions.size();
    modelOptions[nextOptionID] = modelName;

	glutDestroyMenu(modelSubMenu); // 銷毀舊的菜單
    modelSubMenu = glutCreateMenu(HandleMenuSelect);
    for (const auto& pair : modelOptions) {
        glutAddMenuEntry(pair.second.c_str(), pair.first);
    }

    glutSetMenu(mainMenu);
	glutChangeToSubMenu(1, "Model", modelSubMenu); // 更新菜單（重新綁定）
}

void MenuHandler::handleMenuSelect(int option) {
	if (option >= MODEL_OPTION_START && option < MODEL_OPTION_START + modelOptions.size()) {  // 選擇模型
		std::string modelName = modelOptions.find(option)->second;
        scene->chooseCurrentShowModel(modelName);
    }
    else {  // 選擇渲染模式或顏色模式
        switch (option) {
        case RENDER_POINT:
            scene->setRenderMode(RenderMode::POINT);
            break;
        case RENDER_LINE:
            scene->setRenderMode(RenderMode::LINE);
            break;
        case RENDER_FACE:
            scene->setRenderMode(RenderMode::FACE);
            break;
        case COLOR_SINGLE:
            scene->setColorMode(ColorMode::SINGLE);
            break;
        case COLOR_RANDOM:
            scene->setColorMode(ColorMode::RANDOM);
            break;
        default:
			throw std::invalid_argument("Invalid menu option selected: " + std::to_string(option));
			break;
        }
    }

    glutPostRedisplay();
}
