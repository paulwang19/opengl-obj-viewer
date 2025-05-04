#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <vector>
#include <string>
#include "struct/Vector3D.h"
#include "struct/Face.h"

class ObjLoader {
public:
    ObjLoader();
    ~ObjLoader();

    // ���J .obj �ɮ�
    void loadObj(const std::string& filename);

    // ������I�M�����
    const std::vector<Vector3D>& getVertices() const;
    const std::vector<Face>& getFaces() const;

private:
    std::vector<Vector3D> vertices; // �x�s���I�y��
    std::vector<Face> faces; // �x�s�������I����
};

#endif // OBJ_LOADER_H