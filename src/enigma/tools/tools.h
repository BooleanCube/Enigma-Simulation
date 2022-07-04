//
// Created by boole on 7/4/22.
//

#ifndef ENIGMA_TOOLS_H
#define ENIGMA_TOOLS_H

#endif //ENIGMA_TOOLS_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class tools {
public:
    static int random_int(int start, int bound);
    static std::vector<std::string> &split(const std::string &s, char delim);
    static std::string join(std::vector<std::string>& list, const std::string& separator);
};
