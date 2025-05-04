#ifndef UNEXPECTED_EVENT_EXCEPTION_H
#define UNEXPECTED_EVENT_EXCEPTION_H

#include <stdexcept>
#include <string>

struct UnexpectedEventException : public std::runtime_error {
    UnexpectedEventException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // UNEXPECTED_EVENT_EXCEPTION_H