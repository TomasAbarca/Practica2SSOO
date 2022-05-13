/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: MediatorySearch.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: Class that implements her .h
         
*/

#include "MediatorySearch.h"

MediatorySearch::MediatorySearch(int id_client, std::vector <std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue>> pq_vector){
    this -> id_client = id_client;
    this -> pq_vector = pq_vector;
}

int MediatorySearch::get_id_client(){
    return id_client;
}