#include "CallBackUtil.h"
#include "exception/InstanceNotSetException.h"

extern int windowWidth;
extern int windowHeight;

static Scene* sceneInstance = nullptr;
static InputHandler* inputHandlerInstance = nullptr;
static MenuHandler* menuHandlerInstance = nullptr;

void SetSceneInstance(Scene* scene) {
	sceneInstance = scene;
}

void SetInputHandlerInstance(InputHandler* inputHandler) {
	inputHandlerInstance = inputHandler;
}

void SetMenuHandlerInstance(MenuHandler* menuHandler) {
	menuHandlerInstance = menuHandler;
}

void HandleRenderScene() {
	if (!sceneInstance) {
		throw InstanceNotSetException("Scene instance is not set.");
	}

	sceneInstance->render();
}

void HandleResizeWindow(int width, int height) {
	if (!sceneInstance) {
		throw InstanceNotSetException("Scene instance is not set.");
	}

	sceneInstance->initialize(width, height);
	windowWidth = width;
	windowHeight = height;
	Logger::getInstance().logInfo("Window resized to " + std::to_string(windowWidth) + " x " + std::to_string(windowHeight));
}

void HandleKeyboardPress(unsigned char key, int x, int y) {
	if (!inputHandlerInstance) {
		throw InstanceNotSetException("InputHandler instance is not set.");
	}

	inputHandlerInstance->handleKeyboardPress(key, x, y);
}

void HandSpecialKeyPress(int key, int x, int y) {
	if (!inputHandlerInstance) {
		throw InstanceNotSetException("InputHandler instance is not set.");
	}

	inputHandlerInstance->handSpecialKeyPress(key, x, y);
}

void HandleMouseClick(int button, int state, int x, int y) {
	if (!inputHandlerInstance) {
		throw InstanceNotSetException("InputHandler instance is not set.");
	}

	inputHandlerInstance->handleMouseClick(button, state, x, y);
}

void HandleMenuSelect(int option) {
	if (!menuHandlerInstance) {
		throw InstanceNotSetException("MenuHandler instance is not set.");
	}

	menuHandlerInstance->handleMenuSelect(option);
}