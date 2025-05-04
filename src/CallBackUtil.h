#ifndef CALL_BACK_UTIL_H
#define CALL_BACK_UTIL_H

#include "Scene.h"
#include "InputHandler.h"
#include "MenuHandler.h"

void SetSceneInstance(Scene* scene);
void SetInputHandlerInstance(InputHandler* inputHandler);
void SetMenuHandlerInstance(MenuHandler* menuHandler);

void HandleRenderScene();
void HandleResizeWindow(int width, int height);
void HandleKeyboardPress(unsigned char key, int x, int y);
void HandSpecialKeyPress(int key, int x, int y);
void HandleMouseClick(int button, int state, int x, int y);
void HandleMenuSelect(int option);

#endif // CALL_BACK_UTIL_H

