//
// Created by boole on 7/4/22.
//

#ifndef ENIGMA_PLUGBOARD_H
#define ENIGMA_PLUGBOARD_H

#include <string>
#include <vector>

class plugboard {

    std::vector<char>* out;

public:
    plugboard() {
        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        out = new std::vector<char>(alphabet.begin(), alphabet.end());
    }
    void connect(char f, char s);
    char output(char in);

};


#endif //ENIGMA_PLUGBOARD_H
