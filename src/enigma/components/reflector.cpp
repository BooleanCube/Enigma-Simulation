//
// Created by boole on 7/4/22.
//

#include "reflector.h"

std::string reflector::getOutput() const {
    return out;
}

char reflector::output(char in) {
    return out.at((uint8_t)in - 65);
}