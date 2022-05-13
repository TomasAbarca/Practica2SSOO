/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: OrderQueue.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: Class that implements her .h
         
*/

#include <iostream>

#include "OrderQueue.h"

/* The instances are going to be ordered by the id of the thread, 
*  then by the number of line and finally by the position of the
*  word in the line */
int OrderQueue::operator()(LineResult &a, LineResult &b){
    if(a.get_tr().get_id_thread() == b.get_tr().get_id_thread()){
        if(a.get_n_line() == b.get_n_line()){
            return a.get_pos_in_line() > b.get_pos_in_line();
        }else{
            return a.get_n_line() > b.get_n_line();
        }
    }
    return a.get_tr().get_id_thread() > b.get_tr().get_id_thread();
}