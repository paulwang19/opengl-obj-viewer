#ifndef INSTANCE_NOT_SET_EXCEPTION_H
#define INSTANCE_NOT_SET_EXCEPTION_H

#include <stdexcept>
#include <string>

struct InstanceNotSetException : public std::runtime_error {
    InstanceNotSetException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // INSTANCE_NOT_SET_EXCEPTION_H