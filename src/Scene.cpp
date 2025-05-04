#include "Scene.h"
#include <GL/freeglut.h>
#include "exception/NotImplementedException.h"

Scene::Scene(Camera* camera)
    : camera(camera), currentShowModelIndex(-1),
    renderMode(RenderMode::FACE), colorMode(ColorMode::RANDOM) {}

Scene::~Scene() {}

void Scene::initialize(int width, int height) {
    glEnable(GL_DEPTH_TEST); // 啟用深度測試
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
		45.0, // 視場角度（度）
        (float)width / (float)height,  // 寬高比
		0.1, // 近裁剪面
		1000.0 // 遠裁剪面
    );
}

void Scene::render() const {  
   glClearColor(0.75f, 0.75f, 0.75f, 1.0f); // 灰色背景  
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

   glMatrixMode(GL_MODELVIEW);  
   glLoadIdentity();

   camera->applyCamera(); // 應用攝影機參數

   models.at(currentShowModelIndex).render(renderMode, colorMode);  
   glutSwapBuffers();  
}

int Scene::addModel(const Model& model) {
    models.push_back(model);
    return models.size();
}

void Scene::chooseCurrentShowModel(std::string modelName) {
	for (int i = 0; i < models.size(); ++i) {
		if (models[i].getName() == modelName) {
			currentShowModelIndex = i;
            adjustCameraToCurrentModel();
			return;
		}
    }
    
	throw std::invalid_argument("Model not found: " + modelName);
}

void Scene::operateCurrentModel(Operation operation) {
    switch (operation) {
	case RESET:
		models.at(currentShowModelIndex).reset();
		break;
    case MOVE_X:
        models.at(currentShowModelIndex).moveX();
        break;
    case MOVE_Y:
        models.at(currentShowModelIndex).moveY();
        break;
    case MOVE_Z:
        models.at(currentShowModelIndex).moveZ();
        break;
    case MOVE_NEGATIVE_X:
        models.at(currentShowModelIndex).moveNegativeX();
        break;
    case MOVE_NEGATIVE_Y:
        models.at(currentShowModelIndex).moveNegativeY();
        break;
    case MOVE_NEGATIVE_Z:
        models.at(currentShowModelIndex).moveNegativeZ();
        break;
    case ROTATE_X:
        models.at(currentShowModelIndex).rotateX();
        break;
    case ROTATE_Y:
        models.at(currentShowModelIndex).rotateY();
        break;
    case ROTATE_Z:
        models.at(currentShowModelIndex).rotateZ();
        break;
    case ROTATE_NEGATIVE_X:
        models.at(currentShowModelIndex).rotateNegativeX();
        break;
    case ROTATE_NEGATIVE_Y:
        models.at(currentShowModelIndex).rotateNegativeY();
        break;
    case ROTATE_NEGATIVE_Z:
        models.at(currentShowModelIndex).rotateNegativeZ();
        break;
    case INCREASE_SCALE:
        models.at(currentShowModelIndex).increaseScale();
        break;
    case DECREASE_SCALE:
        models.at(currentShowModelIndex).decreaseScale();
        break;
    default:
		throw NotImplementedException("Operation not implemented");
        break;
    }
}

/*
 * 攝影機位置如果經過移動，其對準方向可能不再是模型 
 * 此函數讓攝影機重新對準模型中央
 */
void Scene::setCameraFocusModel() {
    BoundingBox box = models.at(currentShowModelIndex).getBoundingBox();
	camera->changeTarget(box.center.x, box.center.y, box.center.z); // 設置攝影機目標
}

void Scene::adjustCameraToCurrentModel() {
    BoundingBox box = models.at(currentShowModelIndex).getBoundingBox();
    camera->setDefaultPosition(box.center.x + box.width * 2.0, box.center.y, box.center.z + box.depth * 2.0); // 設置攝影機位置
    camera->setDefaultTarget(box.center.x, box.center.y, box.center.z); // 設置攝影機目標
    camera->setDefaultUp(0.0f, 1.0f, 0.0f); // 設置攝影機上向量
    camera->setMoveFactor((box.width + box.height + box.depth) * 0.05);
    camera->setRevolveFactor((box.width + box.height + box.depth) * 0.05);
	camera->reset(); // 重設攝影機
}