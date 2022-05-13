/*

Project: Práctica 3 de SSOO II - SSOOIIGLE II
Class Name: SearchRequest.cpp
Authors: Aarón Peces García, Tomás Abarca Cerro, Fernando González García
Date: 13/05/2022
Purpose: Class that implements her .h
         
*/

#include "SearchRequest.h"

SearchRequest::SearchRequest(int id_client, std::string word_to_search, int priority){
    this -> id_client = id_client;
    this -> word_to_search = word_to_search;
    this -> priority = priority;
}

int SearchRequest::get_id_client(){
    return id_client;
}

int SearchRequest::get_id_search(){
    return id_search;
}

std::string SearchRequest::get_word_to_search(){
    return word_to_search;
}

int SearchRequest::get_priority(){
    return priority;
}

void SearchRequest::set_id_request(){
    this -> id_search = g_id_request;
    g_id_request++;
}

void SearchRequest::toString(){
    std::cout << "Request (" << id_search << "): Client " << id_client << " searchs word ";
    std::cout << word_to_search << " with priority " << priority << std::endl;
}