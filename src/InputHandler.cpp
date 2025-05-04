#include "InputHandler.h"
#include <cmath>

InputHandler::InputHandler(Camera* camera, Scene* scene) : camera(camera), scene(scene) {}

InputHandler::~InputHandler() {}

void InputHandler::handleKeyboardPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
    case 'R':
        scene->operateCurrentModel(RESET);
        camera->reset();
        break;
    case 'q':
	case 'Q':
		scene->operateCurrentModel(MOVE_X);
		break;
	case 'a':
	case 'A':
		scene->operateCurrentModel(MOVE_NEGATIVE_X);
		break;
	case 'w':
	case 'W':
		scene->operateCurrentModel(MOVE_Y);
		break;
	case 's':
	case 'S':
		scene->operateCurrentModel(MOVE_NEGATIVE_Y);
		break;
	case 'e':
	case 'E':
		scene->operateCurrentModel(MOVE_Z);
		break;
	case 'd':
	case 'D':
		scene->operateCurrentModel(MOVE_NEGATIVE_Z);
		break;
    case '1':
		scene->operateCurrentModel(ROTATE_X);
        break;
	case '2':
		scene->operateCurrentModel(ROTATE_Y);
		break;
	case '3':
		scene->operateCurrentModel(ROTATE_Z);
		break;
	case '4':
		scene->operateCurrentModel(ROTATE_NEGATIVE_X);
		break;
	case '5':
		scene->operateCurrentModel(ROTATE_NEGATIVE_Y);
		break;
	case '6':
		scene->operateCurrentModel(ROTATE_NEGATIVE_Z);
		break;
	case 'k':
	case 'K':
		scene->operateCurrentModel(INCREASE_SCALE);
		break;
	case 'l':
	case 'L':
		scene->operateCurrentModel(DECREASE_SCALE);
		break;
	case 'm':
	case 'M':
		camera->moveUp();
        break;
	case 'n':
	case 'N':
		camera->moveDown();
		break;
    case 27: // ESC 鍵
        glutLeaveMainLoop();
        break;
    }

    glutPostRedisplay();
}

void InputHandler::handSpecialKeyPress(int key, int x, int y) {
	switch (key) {
    case GLUT_KEY_UP:
        camera->moveForward();
        break;
    case GLUT_KEY_DOWN:
        camera->moveBackward();
        break;
	case GLUT_KEY_LEFT:
		camera->moveLeft();
		break;
	case GLUT_KEY_RIGHT:
		camera->moveRight();
        break;
    case GLUT_KEY_F1:
		camera->revolveLeft();
		break;
	case GLUT_KEY_F2:
		camera->revolveRight();
		break;
	case GLUT_KEY_F3:
        camera->revolveUp();
		break;
	case GLUT_KEY_F4:
		camera->revolveDown();
		break;
	case 114: // Left Ctrl
	case 115: // Right Ctrl
		scene->setCameraFocusModel();
		break;
	}

	glutPostRedisplay();
}

void InputHandler::handleMouseClick(int button, int state, int x, int y) {
	if (button == 3 && state == GLUT_DOWN) {  // 滾輪向上
        scene->operateCurrentModel(INCREASE_SCALE);
	}
	else if (button == 4 && state == GLUT_DOWN) {  // 滾輪向下
        scene->operateCurrentModel(DECREASE_SCALE);
    }

    glutPostRedisplay();
}
