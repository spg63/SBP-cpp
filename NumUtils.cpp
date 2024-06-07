//
//  NumUtils.cpp
//  cpplibs
//
//  Created by Sean Grimes on 11/26/14.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#include "NumUtils.hpp"

// NOTE: These exist to avoid bringing in the full cstdlib, they are more or less
//       identical to atodlib
int NumUtils::strToInt(const std::string &s){
    char *end;
    long l;
    char *c_str = new char[s.length() + 1];
    strcpy(c_str, s.c_str());
    std::string err = "strToInt Error: ";
    errno = 0;
    l = strtol(c_str, &end, 10);
    if((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
        printerr_and_quit(err + "Integer overflow on conversion.");
    if((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
        printerr_and_quit(err + "Integer underflow on conversion");
    if(*c_str == '\0' || *end != '\0')
        printerr_and_quit(err + "Cannot convert " + s + " to an integer");
    
    delete c_str;
    c_str = nullptr;
   
    return (int) l;
}

double NumUtils::strToDouble(const std::string &s){
    char *end;
    double d;
    char *c_str = new char[s.length() + 1];
    strcpy(c_str, s.c_str());
    std::string err = "strToDouble Error: ";
    errno = 0;
    d = strtod(c_str, &end);
    if((errno == ERANGE && d == DBL_MAX) || d > DBL_MAX)
        printerr_and_quit(err + "Double overflow on conversion.");
    if((errno == ERANGE && d == DBL_MIN) || d < DBL_MIN)
        printerr_and_quit(err + "Double underflow on conversion.");
    if(*c_str == '\0' || *end != '\0')
        printerr_and_quit(err + "Cannot convert " + s + " to a double");
    
    delete c_str;
    c_str = nullptr;
    
    return (double) d;
}

int NumUtils::getRandomInt(int start, int end){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(start, end);
    return dist(mt);
}

void NumUtils::printerr_and_quit(const std::string &s){
    fprintf(stderr, "\n*** %s ***\n\n", s.c_str());
    exit(-1);
}