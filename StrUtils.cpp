//
//  StrUtils.cpp
//  cpplibs
//
//  Created by Sean Grimes on 11/26/15.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#include "StrUtils.hpp"
std::vector<std::string> StrUtils::splitStr(const std::string &line, const char delim){
    std::vector<std::string> vec;
    std::stringstream ss{line};
    std::string tmp;
    while(std::getline(ss, tmp, delim)){
        vec.push_back(tmp);
    }
    return vec;
}

bool StrUtils::ends_with_string(const std::string &str, const std::string &what) {
    return what.size() <= str.size() && str.find(what, str.size() - what.size()) != str.npos;
}