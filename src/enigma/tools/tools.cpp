//
// Created by boole on 7/4/22.
//

#include "tools.h"

int tools::random_int(int start, int bound) {
    bound -= start - 1;
    return (int)((float)rand()/RAND_MAX * bound) + start;
}

std::vector<std::string> &tools::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    auto* elems = new std::vector<std::string>;
    while(getline(ss, item, delim)) elems->push_back(item);
    return *elems;
}

std::string tools::join(std::vector<std::string>& list, const std::string& separator){
    std::string s;
    for(const auto& i : list){
        if(s.empty()) s = i;
        else s += separator + i;
    }
    return s;
}