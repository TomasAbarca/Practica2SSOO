#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>

int count_lines(char const *filename)
{
    int counter;
    std::string line;
    std::ifstream file(filename);
    if (existFile(filename)){
        while(getline(file,line)){
        counter++;
    }
    }
    return counter;
}


//Método para comprobar si existe el archivo

bool existFile(std::string path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        return false;
    }
    return true;
}