#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>


void read_file(char const *filename)
{
    std::string linea;
    FILE *file=NULL;
    file=fopen(filename,"rt");
    while(getline(file, linea)){
        std::cout<<linea<<std::endl;
    }
}


int main(int argc, char const *argv[])
{
    char const *filename=argv[1];
    read_file(filename);

}