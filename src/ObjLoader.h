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

    // 載入 .obj 檔案
    void loadObj(const std::string& filename);

    // 獲取頂點和面資料
    const std::vector<Vector3D>& getVertices() const;
    const std::vector<Face>& getFaces() const;

private:
    std::vector<Vector3D> vertices; // 儲存頂點座標
    std::vector<Face> faces; // 儲存面的頂點索引
};

#endif // OBJ_LOADER_H