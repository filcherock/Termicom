#include <iostream>
#include <dirent.h>
#include <sys/types.h>

#include "tcolor.h"

void listFilesAndDirectories(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        const std::string fileOrDirName = entry->d_name;

    if (fileOrDirName != "." && fileOrDirName != "..") {
        std::cout << (entry->d_type == DT_DIR ? "\e[1;36m[DIR]\e[0;37m " : "\e[1;33m[FILE]\e[0;37m ") 
                << fileOrDirName << std::endl;
        }
    }

    closedir(dir);
}