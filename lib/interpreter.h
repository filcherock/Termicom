#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "tcolor.h"
#include "info.h"
#include "fs.h"

#define HELP_STR "help"
#define INFO_STR "info"
#define DIR_STR "ls"

#define HELP_PARAM "--h"

std::string command;

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

void OutHelpString(std::string file) {
    std::string line;
    std::ifstream in("help-list/" + file + ".txt");
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::cout << tCyan << line << tWhite << std::endl;
        }
    }
    in.close();
}

int interpreter(std::string line) {
    bool mainCmd = true;
    bool isParam = false;
    std::string command;
    if (line.empty()) {
        return 0; 
    }
    std::vector<std::string> words = split(line);
    for (const auto& word : words) {
        if (mainCmd == true) {
            command = word;
            mainCmd = false;
        } else {
            if (word == "--h")
            {
                OutHelpString(command);
                isParam = true;
            }
            
        }
    }
    if (isParam == false) {
        if (command == HELP_STR) {
            std::cout << "╔════════════════════════════════════╗" << std::endl;
            std::cout << "║  help - output help-list           ║" << std::endl;
            std::cout << "║  info - output information         ║" << std::endl;
            std::cout << "║  ls - lists files and directories  ║" << std::endl;
            std::cout << "╚════════════════════════════════════╝" << std::endl;
        } else if (command == INFO_STR) {
            std::cout << "╔═════════════════════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║ " << PROGRAM_NAME << "                                                ║" << std::endl;
            std::cout << "║  └ Version: " << PROGRAM_VERSION << "                                              ║" << std::endl;
            std::cout << "║  └ Author: " << PROGRAM_AUTHOR << "                                              ║" << std::endl;
            std::cout << "║  └ GitHub Repos: " << PROGRAM_GITHUB_REPOS << "         ║" << std::endl;
            std::cout << "║  └ License: " << PROGRAM_LICENSE << "                     ║" << std::endl;
            std::cout << "╚═════════════════════════════════════════════════════════════════╝" << std::endl;
        } else if (command == DIR_STR) {
            char cwd[256];
            if (getcwd(cwd, sizeof(cwd)) != nullptr) {
                listFilesAndDirectories(cwd);
            } else {
                perror("Error!");
            }
        } else {
            return 0;
        }
    }
    
    
    return 0;
}

/*int interpreter(std::string line) {
    if (line.empty()) {
        return 0; 
    }
    std::vector<std::string> words = split(line);
    if (words[0] == HELP_STR) {
        std::cout << "╔════════════════════════════════════╗" << std::endl;
        std::cout << "║                                    ║" << std::endl;
        std::cout << "╚════════════════════════════════════╝" << std::endl;
    } else if (words[0] == INFO_STR)
    {
        if (words[1] == HELP_PARAM) {
            std::cout << "The" << tbGreen << " info " << tWhite << "command is designed to display information about a program. It displays the program version, author, GitHub repository, and the license under which the program is distributed." << std::endl;
        } else {
            std::cout << "╔═════════════════════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║ " << PROGRAM_NAME << "                                                ║" << std::endl;
            std::cout << "║  └ Version: " << PROGRAM_VERSION << "                                              ║" << std::endl;
            std::cout << "║  └ Author: " << PROGRAM_AUTHOR << "                                              ║" << std::endl;
            std::cout << "║  └ GitHub Repos: " << PROGRAM_GITHUB_REPOS << "         ║" << std::endl;
            std::cout << "║  └ License: " << PROGRAM_LICENSE << "                     ║" << std::endl;
            std::cout << "╚═════════════════════════════════════════════════════════════════╝" << std::endl;
        }
    }
    else {
        std::cout << tbRed << words[0] << ": Not found!" << std::endl;
    }
    return 0;
}*/