/*
Termicom 2.0.0
Copyright (C), 2025
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "tcolor.h"
#include "info.h"
#include "unistd.h"
#include "interpreter.h"

void shell() {
    while (true)
    {
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::cout << tbGreen << "termicom:" << tbBlue << cwd << tWhite << " $ ";
            std::getline(std::cin, command); 
            interpreter(command);
        } else {
            perror("Error!");
        }
    }
}

void init() {
    system("clear");
    std::cout << tbWhite << "Welcome to Termicom!" << std::endl;
    shell();
}

int main() {
    init();
    return 0;
}