//
// Created by boole on 7/4/22.
//

#include "rotor.h"


std::string rotor::getNotches() {
    return notches;
}

std::string rotor::getOutput() {
    return out;
}

void rotor::setRing(int ring) {
    this->ring = ring;
}

void rotor::setTop(char top) {
    this->top = top;
}

bool rotor::isNotch(char chr) {
    return std::any_of(std::begin(notches), std::end(notches), [chr](char c){ return chr == c; });
}

char rotor::offset(char start, int shift) {
    if(shift > 0) {
        if((start+shift) > 90) return (char)(65 + shift - (90-start) - 1);
        else return (char)(start + shift);
    } else {
        if((start+shift < 65)) return (char)(90 + (shift + (start-65)) + 1);
        else return (char)(start + shift);
    }
}

char rotor::output(char in, int setting) {
    char alpha = offset(in, -setting+1);
    int off = out.at((int)(alpha)-65) - alpha;
    return offset(in, off);
}

char rotor::reverseOutput(char in, int setting) {
    char alpha = offset(in, -setting+1);
    int off = reverseOut.at((int)(alpha)-65) - alpha;
    return offset(in, off);
}

