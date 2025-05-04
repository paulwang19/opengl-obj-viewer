#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    // 獲取單例實例的靜態方法
    static Logger& getInstance();

    // 記錄不同層級的訊息
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);

	void setDebugMode(bool enable = true); // 切換除錯模式
    void logDebug(const std::string& message);

    // 禁止複製和賦值
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    bool debugMode; // 是否啟用除錯模式

    // 私有建構函數，確保單例
    Logger() : debugMode(false) {}

    // 靜態實例
    static Logger* instance;
};

#endif // LOGGER_H