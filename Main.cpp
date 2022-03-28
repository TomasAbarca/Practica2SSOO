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


void read_file(char const *filename)
{
    std::string linea;
    std::ifstream file(filename);
    while(getline(file, linea)){
        std::cout<<linea<<std::endl;
    }
}


int main(int argc, char const *argv[])
{
    std::vector <std::thread> v_threads;
    int block_size;
    char const *filename=argv[1];
    int threads, *n_threads;
    n_threads=&threads;
    *n_threads=std::stoi(argv[2]);
    
    std::cout<<"Numero de threads:"<<threads<<std::endl;

    for (unsigned i=0;i<threads;i++){
        int line_min = i * block_size;
        int line_max = (line_min + block_size)-1;

        v_threads.push_back(std::thread(read_file, filename));
    }
    std::for_each(v_threads.begin(), v_threads.end(), std::mem_fn(&std::thread::join)); 
    read_file(filename);


}