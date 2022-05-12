#include <iostream>

#include "ThreadResult.h"

ThreadResult::ThreadResult(int id_thread, int first_line, int last_line){
    this -> id_thread = id_thread;
    this -> first_line = first_line;
    this -> last_line = last_line;
}

int ThreadResult::get_id_thread(){
    return id_thread;
}

int ThreadResult::get_first_line(){
    return first_line;
}

int ThreadResult::get_last_line(){
    return last_line;
}

void ThreadResult::toString(){
    std::cout << "[Hilo " << id_thread << " inicio: " << first_line;
    std::cout << " -- final: " << last_line << std::endl;
}