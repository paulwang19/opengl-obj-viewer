#include "Logger.h"
#include <iostream>

Logger* Logger::instance = nullptr;

Logger& Logger::getInstance() {
    if (instance == nullptr) {
        instance = new Logger();
    }

    return *instance;
}

void Logger::logDebug(const std::string& message) {
	if (!debugMode) {
		return; // �p�G�����Ҧ����ҥΡA�h���O�������T��
	}

    std::cout << "[DEBUG] " << message << std::endl;
}

void Logger::logInfo(const std::string& message) {
    std::cout << "[INFO] " << message << std::endl;
}

void Logger::logWarning(const std::string& message) {
    std::cout << "[WARNING] " << message << std::endl;
}

void Logger::logError(const std::string& message) {
    std::cout << "[ERROR] " << message << std::endl;
}

void Logger::setDebugMode(bool enable) {
	debugMode = enable;
}