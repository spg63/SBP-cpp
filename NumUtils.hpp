//
//  NumUtils.hpp
//  cpplibs
//
//  Created by Sean Grimes on 11/26/14.
//  Edited: 04/09/15.
//  Edited: 01/13/16 --> Bunch of non-pertinent (to AI Assignment) stuff removed.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#ifndef NumUtils_hpp
#define NumUtils_hpp
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <float.h>
#include <random>
#include <limits.h>
#include <cstdint>

class NumUtils{
public:
    
    /*
     NOTE: Both of these strToInt/Double functions are closely related to code written on a stack overflow answer:
     http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
     by Dan Moulding
     Which in turn is based on the cstdlib strtol family of functions
     */
    /**
     * Returns an int from a string, using stringstream
     *
     * @param: s - The string to be converted to an int
     * @return: int - The converted string
     */
    static int strToInt(const std::string &s);
   
    /**
     * Returns a double from a string, using stringstream
     *
     * @param: s - The string to be converted to a double
     * @return: double - The converted string
     */
    static double strToDouble(const std::string &s);
    
    /**
     * Gets a random integer between the range given
     * Modeled from: http://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library
     * Answer #1: Bill Lynch
     */
    static int getRandomInt(int start, int end);

    
private:
    static void printerr_and_quit(const std::string &s);
    
};


#endif /* NumUtils_hpp */




















