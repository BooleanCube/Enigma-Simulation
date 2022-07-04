//
// Created by boole on 7/4/22.
//

#ifndef ENIGMA_ROTOR_H
#define ENIGMA_ROTOR_H

#include <string>
#include <vector>
#include <algorithm>

class rotor {
public:
    std::string out;
    std::string reverseOut;
    std::string notches;

    char top;
    int ring;

    rotor(std::string output, std::string notches) {
        this->out = output;
        this->notches = notches;

        std::vector<char> revList(26);
        for(int i=0; i<out.length(); i++) revList[(int)output.at(i)-65] = (char)(i+65);
        this->reverseOut = std::string(revList.begin(), revList.end());
    }

    void setRing(int ring);
    void setTop(char top);
    std::string getNotches();
    std::string getOutput();
    bool isNotch(char chr);
    static char offset(char start, int shift);
    char output(char in, int setting);
    char reverseOutput(char in, int setting);
};

#endif //ENIGMA_ROTOR_H
