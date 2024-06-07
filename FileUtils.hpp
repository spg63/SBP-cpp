//
//  FileUtils.hpp
//  cpplibs
//
//  Created by Sean Grimes on 08/7/15.
//  Edited: 10/16/15.
//  Copyright © 2015 Sean Grimes. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdexcept>
#include "StrUtils.hpp"
#include <cstring>
#include <unistd.h>

class FileUtils{
public:
    static std::string readFullFile(const std::string &fileName);
    static std::vector<std::string> readLineByLine(const std::string &fileName);
    static size_t lineCount(const char *fname);
    static std::vector<std::string> getFilesInDir(const std::string &dirPath, std::string ext = "");
    static std::vector<std::string> getDirsInDir(const std::string &path);
    static bool isFile(const std::string &path);
    static bool isDir(const std::string &path);

};



#endif /* FileUtils_hpp */

