//
//  StrUtils.hpp
//  cpplibs
//
//  Created by Sean Grimes on 10/26/15.
//  Edited: 01/13/15 --> Removed non-pertinent functions
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#ifndef StrUtils_hpp
#define StrUtils_hpp

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

const bool DEBUG_P{true};

class StrUtils{
public:
    template<typename T>
    static std::string numToString(const T &a){
        std::stringstream vert;
        std::string b;
        vert << a;
        vert >> b;
        return b;
    }
    
    static std::vector<std::string> splitStr(const std::string &line, const char delim);
    
    static bool ends_with_string(const std::string &str, const std::string &what);
    
    template<typename T>
    static void debugp(const T &msg){
        if(DEBUG_P)
            std::cout << msg << std::endl;
    }
};

#endif /* StrUtils_hpp */















