#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    // �����ҹ�Ҫ��R�A��k
    static Logger& getInstance();

    // �O�����P�h�Ū��T��
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);

	void setDebugMode(bool enable = true); // ���������Ҧ�
    void logDebug(const std::string& message);

    // �T��ƻs�M���
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    bool debugMode; // �O�_�ҥΰ����Ҧ�

    // �p���غc��ơA�T�O���
    Logger() : debugMode(false) {}

    // �R�A���
    static Logger* instance;
};

#endif // LOGGER_H