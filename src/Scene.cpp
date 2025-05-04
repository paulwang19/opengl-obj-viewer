#include "Scene.h"
#include <GL/freeglut.h>
#include "exception/NotImplementedException.h"

Scene::Scene(Camera* camera)
    : camera(camera), currentShowModelIndex(-1),
    renderMode(RenderMode::FACE), colorMode(ColorMode::RANDOM) {}

Scene::~Scene() {}

void Scene::initialize(int width, int height) {
    glEnable(GL_DEPTH_TEST); // �ҥβ`�״���
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
		45.0, // �������ס]�ס^
        (float)width / (float)height,  // �e����
		0.1, // ����ŭ�
		1000.0 // �����ŭ�
    );
}

void Scene::render() const {  
   glClearColor(0.75f, 0.75f, 0.75f, 1.0f); // �Ǧ�I��  
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

   glMatrixMode(GL_MODELVIEW);  
   glLoadIdentity();

   camera->applyCamera(); // ������v���Ѽ�

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
 * ��v����m�p�G�g�L���ʡA���Ǥ�V�i�ण�A�O�ҫ� 
 * ���������v�����s��Ǽҫ�����
 */
void Scene::setCameraFocusModel() {
    BoundingBox box = models.at(currentShowModelIndex).getBoundingBox();
	camera->changeTarget(box.center.x, box.center.y, box.center.z); // �]�m��v���ؼ�
}

void Scene::adjustCameraToCurrentModel() {
    BoundingBox box = models.at(currentShowModelIndex).getBoundingBox();
    camera->setDefaultPosition(box.center.x + box.width * 2.0, box.center.y, box.center.z + box.depth * 2.0); // �]�m��v����m
    camera->setDefaultTarget(box.center.x, box.center.y, box.center.z); // �]�m��v���ؼ�
    camera->setDefaultUp(0.0f, 1.0f, 0.0f); // �]�m��v���W�V�q
    camera->setMoveFactor((box.width + box.height + box.depth) * 0.05);
    camera->setRevolveFactor((box.width + box.height + box.depth) * 0.05);
	camera->reset(); // ���]��v��
}