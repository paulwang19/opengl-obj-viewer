#ifndef FILE_READ_FAILED_EXCEPTION_H
#define FILE_READ_FAILED_EXCEPTION_H

#include <stdexcept>
#include <string>

struct FileReadFailedException : public std::runtime_error {
    FileReadFailedException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // FILE_READ_FAILED_EXCEPTION_H