#include <iostream>
#include <GL/freeglut.h>
#include <string>
#include <exception>
#include "Logger.h"
#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "InputHandler.h"
#include "MenuHandler.h"
#include "CallBackUtil.h"
#include "exception/FileReadFailedException.h"

struct Config {
	std::vector<std::string> objFilenames;
};

int windowWidth = 800;
int windowHeight = 600;

static Camera *camera = nullptr;
static Scene *scene = nullptr;
static MenuHandler *menuHandler = nullptr;
static InputHandler *inputHandler = nullptr;

std::string ExtractModelNameFromFilePath(const std::string& path);
void Init(Config& config);

int main(int argc, char** argv) {
	try {
		Config config;
		for (int i = 1; i < argc; ++i) {  // 處理命令行參數，使用者輸入的檔案名稱
			config.objFilenames.emplace_back(argv[i]);
		}

		srand(static_cast<unsigned int>(time(0))); // 隨機數初始化

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow("3D Model Renderer");

		Init(config);

		glutDisplayFunc(HandleRenderScene);
		glutReshapeFunc(HandleResizeWindow);
		glutKeyboardFunc(HandleKeyboardPress);
		glutSpecialFunc(HandSpecialKeyPress);
		glutMouseFunc(HandleMouseClick);

		glutMainLoop();

		delete scene;
		delete camera;
		delete inputHandler;
		return 0;
	}
	catch (const std::exception& e) {
		Logger::getInstance().logError("Exception: " + std::string(e.what()));
		return 1;
	}
}

std::string ExtractModelNameFromFilePath(const std::string& path) {
	// 提取最後一段
	size_t pos = path.find_last_of("/\\");
	std::string last_segment = (pos == std::string::npos) ? path : path.substr(pos + 1);

	// 移除副檔名
	size_t dot_pos = last_segment.find_last_of('.');
	return (dot_pos != std::string::npos) ? last_segment.substr(0, dot_pos) : last_segment;
}

void Init(Config &config) {
	camera = new Camera;
	scene = new Scene(camera);
	menuHandler = new MenuHandler(scene);
	inputHandler = new InputHandler(camera, scene);

	SetSceneInstance(scene);
	SetInputHandlerInstance(inputHandler);
	SetMenuHandlerInstance(menuHandler);

	Model gourdModel("model_file/gourd.obj", "Gourd");
	Model octahedronModel("model_file/octahedron.obj", "Octahedron");
	Model teapotModel("model_file/teapot.obj", "Teapot");
	Model teddyModel("model_file/teddy.obj", "Teddy");

	scene->addModel(gourdModel);
	scene->addModel(octahedronModel);
	scene->addModel(teapotModel);
	scene->addModel(teddyModel);
	scene->chooseCurrentShowModel("Gourd"); // 設定當前顯示的模型索引

	menuHandler->initialize(); // 初始化菜單
	menuHandler->addModelOption(gourdModel.getName());
	menuHandler->addModelOption(octahedronModel.getName());
	menuHandler->addModelOption(teapotModel.getName());
	menuHandler->addModelOption(teddyModel.getName());

	// 載入使用者輸入的模型檔案
	for (const auto& objFilename : config.objFilenames) {
		try {
			std::string modelName = ExtractModelNameFromFilePath(objFilename);
			Model model(objFilename, modelName);
			scene->addModel(model);
			menuHandler->addModelOption(model.getName());
		}
		catch (FileReadFailedException e) {
			Logger::getInstance().logWarning("Failed to load model: " + objFilename);
		}
	}
}