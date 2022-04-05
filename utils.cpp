#include "lib.h"

int count_lines(char const *filename);
bool existFile(char const *path);


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

bool existFile(char const *path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        return false;
    }
    return true;
}