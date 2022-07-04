//
// Created by boole on 7/4/22.
//

#ifndef ENIGMA_REFLECTOR_H
#define ENIGMA_REFLECTOR_H

#include <string>

class reflector {

    std::string out;

public:
    reflector(std::string out) {
        this->out = out;
    }

    std::string getOutput() const;
    char output(char in);

};


#endif //ENIGMA_REFLECTOR_H
