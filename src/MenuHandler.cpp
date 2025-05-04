#include "MenuHandler.h"
#include "CallBackUtil.h"
#include <stdexcept>

MenuHandler::MenuHandler(Scene* scene)
	: scene(scene), mainMenu(0), modelSubMenu(0), renderSubMenu(0), colorSubMenu(0) {
}

MenuHandler::~MenuHandler() {}

void MenuHandler::initialize() {
	// �Ы� Model �l���
	modelSubMenu = glutCreateMenu(HandleMenuSelect);

    // �Ы� Render Mode �l���
    renderSubMenu = glutCreateMenu(HandleMenuSelect);
    glutAddMenuEntry("Point", RENDER_POINT);
    glutAddMenuEntry("Line", RENDER_LINE);
    glutAddMenuEntry("Face", RENDER_FACE);

    // �Ы� Color Mode �l���
    colorSubMenu = glutCreateMenu(HandleMenuSelect);
    glutAddMenuEntry("Single color", COLOR_SINGLE);
    glutAddMenuEntry("Random colors", COLOR_RANDOM);

    // �ЫإD���
    mainMenu = glutCreateMenu(HandleMenuSelect);
    glutAddSubMenu("Model", modelSubMenu);
    glutAddSubMenu("Render Mode", renderSubMenu);
    glutAddSubMenu("Color Mode", colorSubMenu);

    // �j�w�k��
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuHandler::addModelOption(const std::string& modelName) {
	int nextOptionID = MODEL_OPTION_START + modelOptions.size();
    modelOptions[nextOptionID] = modelName;

	glutDestroyMenu(modelSubMenu); // �P���ª����
    modelSubMenu = glutCreateMenu(HandleMenuSelect);
    for (const auto& pair : modelOptions) {
        glutAddMenuEntry(pair.second.c_str(), pair.first);
    }

    glutSetMenu(mainMenu);
	glutChangeToSubMenu(1, "Model", modelSubMenu); // ��s���]���s�j�w�^
}

void MenuHandler::handleMenuSelect(int option) {
	if (option >= MODEL_OPTION_START && option < MODEL_OPTION_START + modelOptions.size()) {  // ��ܼҫ�
		std::string modelName = modelOptions.find(option)->second;
        scene->chooseCurrentShowModel(modelName);
    }
    else {  // ��ܴ�V�Ҧ����C��Ҧ�
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
