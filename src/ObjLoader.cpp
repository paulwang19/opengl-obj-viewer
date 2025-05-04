#include "ObjLoader.h"
#include "exception/FileReadFailedException.h"
#include "exception/IncorrectFileFormatException.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <string>

ObjLoader::ObjLoader() : vertices(), faces() {}

ObjLoader::~ObjLoader() {}

void ObjLoader::loadObj(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::string errorMsg = "Failed to open file: " + filename;
        throw FileReadFailedException(errorMsg);
    }

    vertices.clear();
    faces.clear();

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        // 忽略空行或註解
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            float x, y, z;
            if (!(iss >> x >> y >> z)) {
                std::string errorMsg = "Invalid vertex format at line " + std::to_string(lineNumber);
                Logger::getInstance().logError(errorMsg);
                throw IncorrectFileFormatException(errorMsg);
            }
            vertices.emplace_back(x, y, z);
        }
        else if (type == "f") {
            std::vector<int> indices;
            std::string indexStr;
            while (iss >> indexStr) {
                try {
                    if (indexStr[0] == '#') {
                        break;
                    }

                    int index = std::stoi(indexStr);
                    // .obj 索引從 1 開始，轉為 0 開始
                    if (index <= 0 || index > static_cast<int>(vertices.size())) {
                        std::string errorMsg = "Invalid vertex index at line " + std::to_string(lineNumber);
                        Logger::getInstance().logError(errorMsg);
                        throw IncorrectFileFormatException(errorMsg);
                    }

                    indices.push_back(index - 1);
                } catch (const std::invalid_argument& e) {
                    std::string errorMsg = "Invalid vertex index format at line " + std::to_string(lineNumber);
                    Logger::getInstance().logError(errorMsg);
                    throw IncorrectFileFormatException(errorMsg);
                }
            }

            if (indices.size() != 3) {
                std::string errorMsg = "Face must have exactly 3 vertices at line " + std::to_string(lineNumber);
                Logger::getInstance().logError(errorMsg);
                throw IncorrectFileFormatException(errorMsg);
            }

			faces.push_back(Face(indices.at(0), indices.at(1), indices.at(2)));
        }
        // 忽略其他類型（如 g）
    }

    file.close();
    std::string successMsg = "Successfully loaded " + filename + ": " +
        std::to_string(vertices.size()) + " vertices, " +
        std::to_string(faces.size()) + " faces";
    Logger::getInstance().logInfo(successMsg);
}

const std::vector<Vector3D>& ObjLoader::getVertices() const {
    return vertices;
}

const std::vector<Face>& ObjLoader::getFaces() const {
    return faces;
}