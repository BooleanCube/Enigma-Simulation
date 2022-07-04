//
// Created by boole on 7/4/22.
//

#include "plugboard.h"

void plugboard::connect(char f, char s) {
    out->at((uint8_t)f - 65) = s;
    out->at((uint8_t)s - 65) = f;
}

char plugboard::output(char in) {
    return out->at((uint8_t)in - 65);
}