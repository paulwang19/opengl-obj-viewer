#ifndef NOT_IMPLEMENTED_EXCEPTION_H
#define NOT_IMPLEMENTED_EXCEPTION_H

#include <stdexcept>
#include <string>

struct NotImplementedException : public std::runtime_error {
    NotImplementedException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // NOT_IMPLEMENTED_EXCEPTION_H