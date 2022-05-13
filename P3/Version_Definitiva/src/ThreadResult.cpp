/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: ThreadResult.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: Class that implements her .h
         
*/

#include <iostream>

#include "ThreadResult.h"

ThreadResult::ThreadResult(int id_thread, int first_line, int last_line){
    this -> id_thread = id_thread;
    this -> first_line = first_line;
    this -> last_line = last_line;
}

int ThreadResult::get_id_thread(){
    return this->id_thread;
}

int ThreadResult::get_first_line(){
    return this->first_line;
}

int ThreadResult::get_last_line(){
    return this->last_line;
}

void ThreadResult::toString(){
    std::cout << "[Hilo " << id_thread << " inicio: " << first_line;
    std::cout << " -- final: " << last_line << std::endl;
}