#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

#include "utils.cpp"

int total_lines;

void read_file(char const *filename, int line_min, int line_max)
{
    int id_line=0;
    std::string linea;
    std::ifstream file(filename);
    if(existFile(filename)){
        while(getline(file, linea)){
            if(id_line>=line_min && id_line<=line_max){
                std::cout<<linea<<std::endl;
            }else;
            id_line++;
        }
    }
    
}


int main(int argc, char const *argv[])
{
    std::vector <std::thread> v_threads;
    char const *filename=argv[1];
    int threads, *n_threads;
    n_threads=&threads;
    *n_threads=std::atoi(argv[2]);
    total_lines=count_lines(filename);
    int block_size = total_lines/threads;

    std::cout<<total_lines<<std::endl;
    std::cout<<"Numero de threads:"<<threads<<std::endl;

    for (unsigned i=0;i<threads;i++){
        int line_min = i * block_size;
        int line_max = (line_min + block_size)-1;

        std::cout<<"linea minima,"<<line_min<< " hilo: "<<i<<std::endl;
        std::cout<<"linea maximo, "<<line_max<< " hilo: "<<i<<std::endl;

        v_threads.push_back(std::thread(read_file, filename, line_min, line_max));
    }

    std::for_each(v_threads.begin(), v_threads.end(), std::mem_fn(&std::thread::join)); 
 


}