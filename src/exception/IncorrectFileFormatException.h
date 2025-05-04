#ifndef INCORRECT_FILE_FORMAT_EXCEPTION_H
#define INCORRECT_FILE_FORMAT_EXCEPTION_H

#include <stdexcept>
#include <string>

struct IncorrectFileFormatException : public std::runtime_error {
    IncorrectFileFormatException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // INCORRECT_FILE_FORMAT_EXCEPTION_H