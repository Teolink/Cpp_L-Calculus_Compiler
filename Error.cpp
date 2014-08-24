#include "Error.h"
#include <iostream>

Error::Error(const char* const msg) : _msg(msg) {}

const char *Error::what() const noexcept {
    std::cerr << "Error";
    if(_msg) std::cerr << ": " << _msg << std::endl;
}