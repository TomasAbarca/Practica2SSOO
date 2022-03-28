#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>

int lines_count(char const *filename)
{
    int counter;
    std::string line;
    std::ifstream file(filename);
    while(getline(file,line)){
        counter++;
    }
    return counter;
}